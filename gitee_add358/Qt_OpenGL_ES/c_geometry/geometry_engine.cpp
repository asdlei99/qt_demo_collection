#include "geometry_engine.h"

GeometryEngine::GeometryEngine(QOpenGLShaderProgram &program) :
    m_program(program)
{
    initializeOpenGLFunctions();
    m_vbo.create();
    m_vao.create();
}

GeometryEngine::~GeometryEngine()
{
    m_vbo.destroy();
    m_vao.destroy();
}
