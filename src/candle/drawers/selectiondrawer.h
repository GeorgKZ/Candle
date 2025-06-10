#ifndef SELECTIONDRAWER_H
#define SELECTIONDRAWER_H

#include "shaderdrawable.h"

class SelectionDrawer : public ShaderDrawable
{        
public:
    SelectionDrawer();

    QVector4D startPosition() const;
    void setStartPosition(const QVector4D &startPosition);

    QColor color() const;
    void setColor(const QColor &color);

    QVector4D endPosition() const;
    void setEndPosition(const QVector4D &endPosition);

protected:
    bool  updateData();

private:
    QVector4D m_startPosition;
    QVector4D m_endPosition;

    QColor m_color;
};

#endif // SELECTIONDRAWER_H
