// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef MACHINEBOUNDSDRAWER_H
#define MACHINEBOUNDSDRAWER_H

#include <QtCore/QObject>
#include <QtCore/QAbstractTableModel>
#include "shaderdrawable.h"

class MachineBoundsDrawer : public ShaderDrawable
{
public:

    MachineBoundsDrawer();
    virtual ~MachineBoundsDrawer() override;

    QSizeF gridSize() const;
    void setGridSize(const QSizeF &gridSize);

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

    QPointF offset() const;
    void setOffset(const QPointF &offset);

    virtual QVector4D getMaximumExtremes() override;
    virtual QVector4D getMinimumExtremes() override;

protected:

    virtual bool updateData() override;

private:

    QSizeF m_gridSize;
    QRectF m_borderRect;
    QPointF m_offset;
};

#endif // MACHINEBOUNDSDRAWER_H
