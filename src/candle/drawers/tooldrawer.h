// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef TOOLDRAWER_H
#define TOOLDRAWER_H

#include <QtCore/QTimer>
#include <QtGui/QVector4D>
#include <QtGui/QColor>
#include <cmath>
#include "shaderdrawable.h"

class ToolDrawer : public ShaderDrawable
{
public:
    explicit ToolDrawer();

    double toolDiameter() const;
    void setToolDiameter(double toolDiameter);

    double toolLength() const;
    void setToolLength(double toolLength);

    QVector4D toolPosition() const;
    void setToolPosition(const QVector4D &toolPosition);

    double rotationAngle() const;
    void setRotationAngle(double rotationAngle);
    void rotate(double angle);

    double toolAngle() const;
    void setToolAngle(double toolAngle);

    QColor color() const;
    void setColor(const QColor &color);

signals:

public slots:

protected:
    bool updateData();

private:
    double m_toolDiameter;
    double m_toolLength;
    double m_endLength;
    QVector4D m_toolPosition;
    double m_rotationAngle;
    double m_toolAngle;
    QColor m_color;

    double normalizeAngle(double angle);
    QVector<VertexData> createCircle(QVector4D center, double radius, int arcs, QVector3D color);
};

#endif // TOOLDRAWER_H
