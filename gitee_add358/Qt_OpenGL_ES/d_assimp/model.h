

#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QOpenGLShaderProgram>

class Model
{
public:
    // constructor, expects a filepath to a 3D model.
    Model(QOpenGLShaderProgram &shader,
          QString const &path,
          bool gamma = false);
    ~Model();

    // draws the model, and thus all its meshes
    void draw();

protected:
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes QVector.
    void loadModel(QString const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    MeshPointer processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    QVector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, QString typeName);

private:
    /*  Model Data */
    QOpenGLShaderProgram &m_shader;
    QVector<Texture> m_texturesLoaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    QVector<MeshPointer> m_meshes;
    QString m_directory;
    bool m_gammaCorrection;
};

#endif

