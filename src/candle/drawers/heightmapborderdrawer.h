// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef HEIGHTMAPBORDERDRAWER_H
#define HEIGHTMAPBORDERDRAWER_H

#include <QtCore/QObject>
#include "shaderdrawable.h"

class HeightMapBorderDrawer : public ShaderDrawable
{
public:

    HeightMapBorderDrawer();
    virtual ~HeightMapBorderDrawer() override;

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

protected:

    virtual bool updateData() override;

private:

    QRectF m_borderRect;
};

#endif // HEIGHTMAPBORDERDRAWER_H
