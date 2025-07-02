// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef HEIGHTMAPINTERPOLATIONDRAWER_H
#define HEIGHTMAPINTERPOLATIONDRAWER_H

#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtGui/QVector4D>
#include <QtGui/QColor>
#include "shaderdrawable.h"
#include "utils/util.h"

class HeightMapInterpolationDrawer : public ShaderDrawable
{
public:
    explicit HeightMapInterpolationDrawer();
    virtual ~HeightMapInterpolationDrawer();

    QVector<QVector<double> > *data() const;
    void setData(QVector<QVector<double> > *data);

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

protected:
    bool updateData();

private:
    QRectF m_borderRect;
    double m_gridSize;
    QVector<QVector<double>> *m_data;
    double Min(double v1, double v2);
    double Max(double v1, double v2);
};

#endif // HEIGHTMAPINTERPOLATIONDRAWER_H
