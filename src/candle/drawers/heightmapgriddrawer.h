// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef HEIGHTMAPGRIDDRAWER_H
#define HEIGHTMAPGRIDDRAWER_H

#include <QtCore/QObject>
#include <QtCore/QAbstractTableModel>
#include "shaderdrawable.h"

class HeightMapGridDrawer : public ShaderDrawable
{
public:

    HeightMapGridDrawer();
    virtual ~HeightMapGridDrawer() override;

    QPointF gridSize() const;
    void setGridSize(const QPointF &gridSize);

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

    double zTop() const;
    void setZTop(double zTop);

    double zBottom() const;
    void setZBottom(double zBottom);

    QAbstractTableModel *model() const;
    void setModel(QAbstractTableModel *model);

protected:

    virtual bool updateData() override;

private:

    QPointF m_gridSize;
    QRectF m_borderRect;
    double m_zTop;
    double m_zBottom;
    QAbstractTableModel *m_model;
};

#endif // HEIGHTMAPGRIDDRAWER_H
