#include "mesh.h"

Mesh::Mesh(const QVector<Vertex> &vertices,
           const QVector<unsigned int> &indices,
           const QVector<Texture> &textures, QOpenGLShaderProgram &shader) :
    m_shader(shader),
    m_vertices(vertices),
    m_indices(indices),
    m_textures(textures),
    m_ebo(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    m_vao.create();
    m_vbo.create();
    m_ebo.create();

    setup();
}

Mesh::~Mesh()
{
    m_ebo.destroy();
    m_vbo.destroy();
    m_vao.destroy();
}

void Mesh::draw()
{
    int diffuseNr  = 1;
    int specularNr = 1;
    int normalNr   = 1;
    int heightNr   = 1;
    for(int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        QString name = m_textures[i].type;
        if (name == "texture_diffuse") {
            name += QString::number(diffuseNr++);
        } else if(name == "texture_specular") {
            name += QString::number(specularNr++); // transfer unsigned int to stream
        } else if(name == "texture_normal") {
            name += QString::number(normalNr++); // transfer unsigned int to stream
         } else if(name == "texture_height") {
            name += QString::number(heightNr++); // transfer unsigned int to stream
        }

        // now set the sampler to the correct texture unit
        m_shader.setUniformValue(name.toUtf8().data(), i);
        m_textures[i].t->bind(i);
    }

    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);


    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setup()
{
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);

    m_vbo.bind();
    m_vbo.allocate(m_vertices.data(), m_vertices.size()*sizeof(Vertex));

    m_ebo.bind();
    m_ebo.allocate(m_indices.data(), m_indices.size()*sizeof(unsigned int));

    int pos = m_shader.attributeLocation("aPosition");
    m_shader.setAttributeBuffer(pos, GL_FLOAT, 0, 3, sizeof(Vertex));
    m_shader.enableAttributeArray(pos);

    pos = m_shader.attributeLocation("aNormal");
    m_shader.setAttributeBuffer(pos, GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));
    m_shader.enableAttributeArray(pos);

    pos = m_shader.attributeLocation("aTexcoords");
    m_shader.setAttributeBuffer(pos, GL_FLOAT, offsetof(Vertex, texCoords), 2, sizeof(Vertex));
    m_shader.enableAttributeArray(pos);

//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

//    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
}
