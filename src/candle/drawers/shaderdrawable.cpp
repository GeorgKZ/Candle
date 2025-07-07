//#define sNan qQNaN();

#include "shaderdrawable.h"

ShaderDrawable::ShaderDrawable()
{
    m_needsUpdateGeometry = true;
    m_visible = true;
    m_lineWidth = 1.0;
    m_pointSize = 1.0;
    m_texture = nullptr;
}

ShaderDrawable::~ShaderDrawable()
{
    if (!m_vao.isCreated()) m_vao.destroy();
    if (!m_vbo.isCreated()) m_vbo.destroy();
}

void ShaderDrawable::init()
{
    // Init openGL functions
    initializeOpenGLFunctions();

    // Create buffers
    m_vao.create();
    m_vbo.create();
}

void ShaderDrawable::update()
{
    m_needsUpdateGeometry = true;
}

void ShaderDrawable::updateGeometry(QOpenGLShaderProgram *shaderProgram)
{
    // Init in context
    if (!m_vbo.isCreated()) init();

    if (m_vao.isCreated()) {
        // Prepare vao
        m_vao.bind();
    }

    // Prepare vbo
    m_vbo.bind();

    // Update vertex buffer
    if (updateData()) {
        // Fill vertices buffer
        QVector<VertexData> vertexData(m_triangles);
        vertexData += m_lines;
        vertexData += m_points;
        m_vbo.allocate(vertexData.constData(), vertexData.count() * sizeof(VertexData));
    } else {
        m_vbo.release();        
        if (m_vao.isCreated()) m_vao.release();
        m_needsUpdateGeometry = false;
        return;
    }

    if (m_vao.isCreated()) {
        // Offset for position
        quintptr offset = 0;

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = shaderProgram->attributeLocation("a_position");
        shaderProgram->enableAttributeArray(vertexLocation);
        shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

        // Offset for color
        offset = sizeof(QVector4D);

        // Tell OpenGL programmable pipeline how to locate vertex color data
        int color = shaderProgram->attributeLocation("a_color");
        shaderProgram->enableAttributeArray(color);
        shaderProgram->setAttributeBuffer(color, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for line start point
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex line start point
        int start = shaderProgram->attributeLocation("a_start");
        shaderProgram->enableAttributeArray(start);
        shaderProgram->setAttributeBuffer(start, GL_FLOAT, offset, 4, sizeof(VertexData));

        m_vao.release();
    }

    m_vbo.release();

    m_needsUpdateGeometry = false;
}

bool ShaderDrawable::updateData()
{
    // Test data
    m_lines = QVector<VertexData>()
        << VertexData(QVector4D(0,  0,  0, 1.0), QVector3D(1, 0, 0), QVector4D(sNan, 0, 0, 1.0))
        << VertexData(QVector4D(10, 0,  0, 1.0), QVector3D(1, 0, 0), QVector4D(sNan, 0, 0, 1.0))
        << VertexData(QVector4D(0,  0,  0, 1.0), QVector3D(0, 1, 0), QVector4D(sNan, 0, 0, 1.0))
        << VertexData(QVector4D(0, 10,  0, 1.0), QVector3D(0, 1, 0), QVector4D(sNan, 0, 0, 1.0))
        << VertexData(QVector4D(0,  0,  0, 1.0), QVector3D(0, 0, 1), QVector4D(sNan, 0, 0, 1.0))
        << VertexData(QVector4D(0,  0, 10, 1.0), QVector3D(0, 0, 1), QVector4D(sNan, 0, 0, 1.0));



    return true;
}

bool ShaderDrawable::needsUpdateGeometry() const
{
    return m_needsUpdateGeometry;
}

void ShaderDrawable::draw(QOpenGLShaderProgram *shaderProgram)
{
    if (!m_visible) return;

    if (m_vao.isCreated()) {
        // Prepare vao
        m_vao.bind();
    } else {
        // Prepare vbo
        m_vbo.bind();

        // Offset for position
        quintptr offset = 0;
//!!! Проверить 
        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = shaderProgram->attributeLocation("a_position");
        shaderProgram->enableAttributeArray(vertexLocation);
//!!!   shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4);

        // Offset for color
        offset = sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex color data
        int color = shaderProgram->attributeLocation("a_color");
        shaderProgram->enableAttributeArray(color);
//!!!   shaderProgram->setAttributeBuffer(color, GL_FLOAT, offset, 3, sizeof(VertexData));
        shaderProgram->setAttributeBuffer(color, GL_FLOAT, offset, 3);

        // Offset for line start point
//!!!        offset += sizeof(QVector3D);
        offset += sizeof(QVector4D);

        // Tell OpenGL programmable pipeline how to locate vertex line start point
        int start = shaderProgram->attributeLocation("a_start");
        shaderProgram->enableAttributeArray(start);
//!!!   shaderProgram->setAttributeBuffer(start, GL_FLOAT, offset, 3, sizeof(VertexData));
        shaderProgram->setAttributeBuffer(start, GL_FLOAT, offset, 4);
    }

    if (!m_triangles.isEmpty()) {
        if (m_texture) {
            m_texture->bind();
            shaderProgram->setUniformValue("texture", 0);
        }
        glDrawArrays(GL_TRIANGLES, 0, m_triangles.count());
    }

    if (!m_lines.isEmpty()) {
        glLineWidth(m_lineWidth);
        glDrawArrays(GL_LINES, m_triangles.count(), m_lines.count());
    }

    if (!m_points.isEmpty()) {
        glDrawArrays(GL_POINTS, m_triangles.count() + m_lines.count(), m_points.count());
    }

    if (m_vao.isCreated()) m_vao.release(); else m_vbo.release();
}

QVector4D ShaderDrawable::getSizes()
{
    return QVector4D(0, 0, 0, 1.0);
}

QVector4D ShaderDrawable::getMinimumExtremes()
{
    return QVector4D(0, 0, 0, 1.0);
}

QVector4D ShaderDrawable::getMaximumExtremes()
{
    return QVector4D(0, 0, 0, 1.0);
}

int ShaderDrawable::getVertexCount()
{
    return m_lines.count() + m_points.count() + m_triangles.count();
}

double ShaderDrawable::lineWidth() const
{
    return m_lineWidth;
}

void ShaderDrawable::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}

bool ShaderDrawable::visible() const
{
    return m_visible;
}

void ShaderDrawable::setVisible(bool visible)
{
    m_visible = visible;
}

double ShaderDrawable::pointSize() const
{
    return m_pointSize;
}

void ShaderDrawable::setPointSize(double pointSize)
{
    m_pointSize = pointSize;
}
