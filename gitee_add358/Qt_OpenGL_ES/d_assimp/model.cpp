#include "model.h"

#include <QOpenGLTexture>

Model::Model(QOpenGLShaderProgram &shader,
             const QString &path, bool gamma) :
    m_shader(shader),
    m_gammaCorrection(gamma)
{
    loadModel(path);
}

Model::~Model()
{
}

void Model::draw()
{   
    for(int i = 0; i < m_meshes.size(); i++) {
        m_meshes[i]->draw();
    }
}

void Model::loadModel(const QString &path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toUtf8().data(), aiProcess_Triangulate
                                             | aiProcess_FlipUVs
                                             | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        qWarning() << "ERROR::ASSIMP:: " << importer.GetErrorString();
        return;
    }
    // retrieve the directory path of the filepath
    m_directory = path.mid(0, path.lastIndexOf('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }

}

MeshPointer Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        QVector3D vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

        // positions
        vertex.position.setX(mesh->mVertices[i].x);
        vertex.position.setY(mesh->mVertices[i].y);
        vertex.position.setZ(mesh->mVertices[i].z);

        // normals
        if (mesh->mNormals) {
            vertex.normal.setX(mesh->mNormals[i].x);
            vertex.normal.setY(mesh->mNormals[i].y);
            vertex.normal.setZ(mesh->mNormals[i].z);
        }

        // texture coordinates
        if(mesh->mTextureCoords[0]) {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vertex.texCoords.setX(mesh->mTextureCoords[0][i].x);
            vertex.texCoords.setY(mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texCoords = QVector2D(0.0f, 0.0f);
        }

        // tangent
        if (mesh->mTangents) {
            vector.setX(mesh->mTangents[i].x);
            vector.setY(mesh->mTangents[i].y);
            vector.setZ(mesh->mTangents[i].z);
            vertex.tangent = vector;
        }

        // bitangent
        if (mesh->mBitangents) {
            vector.setX(mesh->mBitangents[i].x);
            vector.setY(mesh->mBitangents[i].y);
            vector.setZ(mesh->mBitangents[i].z);
            vertex.bitangent = vector;
        }

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices QVector
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    QVector<Texture> textures;
    // 1. diffuse maps
    QVector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//    textures.append(diffuseMaps);
    textures += diffuseMaps;

    // 2. specular maps
    QVector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//    textures.append(specularMaps);
    textures += specularMaps;

    // 3. normal maps
    QVector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//    textures.append(normalMaps);
    textures += normalMaps;

    // 4. height maps
    QVector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//    textures.append(heightMaps);
    textures += heightMaps;

    // return a mesh object created from the extracted mesh data
    return MeshPointer(new Mesh(vertices, indices, textures, m_shader));
}

QVector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, QString typeName)
{
    QVector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(int j = 0; j < m_texturesLoaded.size(); j++) {
            if(m_texturesLoaded[j].path == str.C_Str()) {
                textures.push_back(m_texturesLoaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip) {   // if texture hasn't been loaded already, load it
            QOpenGLTexture *t = new QOpenGLTexture(QImage(m_directory+"/"+str.C_Str()).mirrored());
            t->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            t->setMagnificationFilter(QOpenGLTexture::Linear);
            t->setWrapMode(QOpenGLTexture::Repeat);

            Texture texture;
            texture.t = t;
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}
