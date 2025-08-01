// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include "tooldrawer.h"

ToolDrawer::ToolDrawer()
{
    m_toolDiameter = 3.0;
    m_toolLength = 30.0;
    m_toolPosition = QVector4D(0, 0, 0, 1.0);
    m_rotationAngle = 0;
    m_toolAngle = 15.0;
    m_endLength = m_toolAngle > 0 && m_toolAngle < 180 ? m_toolDiameter / 2 / tan(m_toolAngle / 180 * M_PI / 2) : 0;
    if (m_toolLength < m_endLength) m_toolLength = m_endLength;
}

ToolDrawer::~ToolDrawer()
{
}

bool ToolDrawer::updateData()
{
    const int arcs = 4;

    // Clear data
    m_lines.clear();
    m_points.clear();

    // Prepare vertex
    VertexData vertex;
    vertex.color = Util::colorToVector(m_color);//QVector3D(1.0, 0.6, 0.0);
    vertex.start = QVector4D(sNan, sNan, sNan, 1.0);

    // Draw lines
    for (int i = 0; i < arcs; i++) {
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);

        // Side lines
        vertex.position = QVector4D(x, y, m_toolPosition.z() + m_endLength, 1.0);
        m_lines.append(vertex);
        vertex.position = QVector4D(x, y, m_toolPosition.z() + m_toolLength, 1.0);
        m_lines.append(vertex);

        // Bottom lines
        vertex.position = QVector4D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z(), 1.0);
        m_lines.append(vertex);
        vertex.position = QVector4D(x, y, m_toolPosition.z() + m_endLength, 1.0);
        m_lines.append(vertex);

        // Top lines
        vertex.position = QVector4D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_toolLength, 1.0);
        m_lines.append(vertex);
        vertex.position = QVector4D(x, y, m_toolPosition.z() + m_toolLength, 1.0);
        m_lines.append(vertex);

        // Zero Z lines
        vertex.position = QVector4D(m_toolPosition.x(), m_toolPosition.y(), 0, 1.0);
        m_lines.append(vertex);
        vertex.position = QVector4D(x, y, 0, 1.0);
        m_lines.append(vertex);
    }

    // Draw circles
    // Bottom
    m_lines += createCircle(QVector4D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_endLength, 1.0),
                            m_toolDiameter / 2, 20, vertex.color);

    // Top
    m_lines += createCircle(QVector4D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_toolLength, 1.0),
                            m_toolDiameter / 2, 20, vertex.color);

    // Zero Z circle
    if (m_endLength == 0) {
        m_lines += createCircle(QVector4D(m_toolPosition.x(), m_toolPosition.y(), 0, 1.0),
                                m_toolDiameter / 2, 20, vertex.color);
    }

    return true;
}
QColor ToolDrawer::color() const
{
    return m_color;
}

void ToolDrawer::setColor(const QColor &color)
{
    m_color = color;
}


QVector<VertexData> ToolDrawer::createCircle(QVector4D center, double radius, int arcs, QVector3D color)
{
    // Vertices
    QVector<VertexData> circle;

    // Prepare vertex
    VertexData vertex;
    vertex.color = color;
    vertex.start = QVector4D(sNan, sNan, sNan, 1.0);

    // Create line loop
    for (int i = 0; i <= arcs; i++) {
        double angle = 2 * M_PI * i / arcs; //-V781
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);

        if (i > 1) {
           circle.append(circle.last());
        }

       if (i < arcs) {
             vertex.position = QVector4D(x, y, center.z(), 1.0);
             circle.append(vertex);
       }

       if (i == arcs) {
         circle.append(circle.first());
       }


    }

    return circle;
}

double ToolDrawer::toolDiameter() const
{
    return m_toolDiameter;
}

void ToolDrawer::setToolDiameter(double toolDiameter)
{
    if (m_toolDiameter != toolDiameter) {
        m_toolDiameter = toolDiameter;
        update();
    }
}
double ToolDrawer::toolLength() const
{
    return m_toolLength;
}

void ToolDrawer::setToolLength(double toolLength)
{
    if (m_toolLength != toolLength) {
        m_toolLength = toolLength;
        update();
    }
}
QVector4D ToolDrawer::toolPosition() const
{
    return m_toolPosition;
}

void ToolDrawer::setToolPosition(const QVector4D &toolPosition)
{
    if (m_toolPosition != toolPosition) {
        m_toolPosition = toolPosition;
        update();
    }
}
double ToolDrawer::rotationAngle() const
{
    return m_rotationAngle;
}

void ToolDrawer::setRotationAngle(double rotationAngle)
{
    if (m_rotationAngle != rotationAngle) {
        m_rotationAngle = rotationAngle;
        update();
    }
}

void ToolDrawer::rotate(double angle)
{
    setRotationAngle(normalizeAngle(m_rotationAngle + angle));
}

double ToolDrawer::toolAngle() const
{
    return m_toolAngle;
}

void ToolDrawer::setToolAngle(double toolAngle)
{
    if (m_toolAngle != toolAngle) {
        m_toolAngle = toolAngle;

        m_endLength = m_toolAngle > 0 && m_toolAngle < 180 ? m_toolDiameter / 2 / tan(m_toolAngle / 180 * M_PI / 2) : 0;
        if (m_toolLength < m_endLength) m_toolLength = m_endLength;

        update();
    }
}

double ToolDrawer::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
    
    return angle;
}
