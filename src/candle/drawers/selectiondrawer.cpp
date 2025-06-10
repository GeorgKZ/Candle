#include "selectiondrawer.h"

SelectionDrawer::SelectionDrawer()
{
    m_endPosition = QVector4D(sNan, sNan, sNan, 1.0);
    m_pointSize = 6.0;
}

bool SelectionDrawer::updateData()
{
    m_points.clear();

    VertexData vertex;
    vertex.color = Util::colorToVector(m_color);
    vertex.position = m_endPosition;
    vertex.start = QVector4D(sNan, sNan, m_pointSize, 1.0);
    m_points.append(vertex);

    return true;
}

QVector4D SelectionDrawer::endPosition() const
{
    return m_endPosition;
}

void SelectionDrawer::setEndPosition(const QVector4D &endPosition)
{
    m_endPosition = endPosition;
}

QColor SelectionDrawer::color() const
{
    return m_color;
}

void SelectionDrawer::setColor(const QColor &color)
{
    m_color = color;
}

QVector4D SelectionDrawer::startPosition() const
{
    return m_startPosition;
}

void SelectionDrawer::setStartPosition(const QVector4D &startPosition)
{
    m_startPosition = startPosition;
}
