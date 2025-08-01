﻿#ifndef SHADERDRAWABLE_H
#define SHADERDRAWABLE_H

#include <QtCore/QObject>
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLTexture>
#include "utils/util.h"

struct VertexData
{
    VertexData() {}
    VertexData(QVector4D pos, QVector3D col, QVector4D sta) {
        position = pos;
        color = col;
        start = sta;
    }

    QVector4D position;
    QVector3D color;
    QVector4D start;
};

class ShaderDrawable : protected QOpenGLFunctions
{
public:
    explicit ShaderDrawable();
    virtual ~ShaderDrawable();
    void update();
    void draw(QOpenGLShaderProgram *shaderProgram);

    bool needsUpdateGeometry() const;
    void updateGeometry(QOpenGLShaderProgram *shaderProgram = nullptr);

    virtual QVector4D getSizes();
    virtual QVector4D getMinimumExtremes();
    virtual QVector4D getMaximumExtremes();
    virtual int getVertexCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    bool visible() const;
    void setVisible(bool visible);

    double pointSize() const;
    void setPointSize(double pointSize);

signals:

public slots:

protected:

    double m_lineWidth;
    double m_pointSize;
    bool m_visible;
    QVector<VertexData> m_lines;
    QVector<VertexData> m_points;
    QVector<VertexData> m_triangles;
    QOpenGLTexture *m_texture;

    QOpenGLBuffer m_vbo; // Protected for direct vbo access

    virtual bool updateData();

    void init();

private:

    QOpenGLVertexArrayObject m_vao;

    bool m_needsUpdateGeometry;
};

#endif // SHADERDRAWABLE_H
