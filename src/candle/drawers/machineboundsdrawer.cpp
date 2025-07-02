// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include "machineboundsdrawer.h"

MachineBoundsDrawer::MachineBoundsDrawer()
{
    m_pointSize = 4;
    m_gridSize = QSizeF(10, 10);
    m_borderRect = QRectF(0, 0, 1, 1);
}

MachineBoundsDrawer::~MachineBoundsDrawer()
{
}

bool MachineBoundsDrawer::updateData()
{
    // Clear data
    m_lines.clear();

    // Border
    QRectF r = m_borderRect.translated(-m_offset);

    // Color
    QVector3D c(0.8, 0.8, 0.8);

    // Vertices
    m_lines
        << VertexData(QVector4D(r.x(),             r.y(),              0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x(),             r.y() + r.height(), 0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x(),             r.y() + r.height(), 0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x() + r.width(), r.y() + r.height(), 0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x() + r.width(), r.y() + r.height(), 0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x() + r.width(), r.y(),              0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x() + r.width(), r.y(),              0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(r.x(),             r.y(),              0, 1.0), c, QVector4D(sNan, sNan, sNan, 1.0));

    return true;
}

QSizeF MachineBoundsDrawer::gridSize() const
{
    return m_gridSize;
}

void MachineBoundsDrawer::setGridSize(const QSizeF &gridSize)
{
    m_gridSize = gridSize;
    update();
}
QRectF MachineBoundsDrawer::borderRect() const
{
    return m_borderRect;
}

void MachineBoundsDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
    update();
}

QPointF MachineBoundsDrawer::offset() const
{
    return m_offset;
}

void MachineBoundsDrawer::setOffset(const QPointF &offset)
{
    m_offset = offset;
    update();
}

QVector4D MachineBoundsDrawer::getMinimumExtremes()
{
    return QVector4D();
}

QVector4D MachineBoundsDrawer::getMaximumExtremes()
{
    return QVector4D(m_borderRect.width(), m_borderRect.height(), 0, 1.0);
}
