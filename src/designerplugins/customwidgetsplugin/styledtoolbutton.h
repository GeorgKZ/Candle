// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef STYLEDTOOLBUTTON_H
#define STYLEDTOOLBUTTON_H

#include <QtGui/QPainter>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionFrame>
#include <QtWidgets/QToolButton>
#include "customwidgetsshared.h"

class CUSTOMWIDGETS_DLLSPEC StyledToolButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backColor WRITE setBackColor)
    Q_PROPERTY(QColor foregroundColor READ foreColor WRITE setForeColor)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor)
    
public:

    explicit StyledToolButton(QWidget *parent = nullptr);

    bool isHover();

    QColor backColor() const;
    void setBackColor(const QColor &backColor);

    QColor foreColor() const;
    void setForeColor(const QColor &foreColor);

    QColor highlightColor() const;
    void setHighlightColor(const QColor &highlightColor);

protected:

    virtual void enterEvent(QEnterEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;

private:

    Q_DISABLE_COPY(StyledToolButton)

    virtual void paintEvent(QPaintEvent *e) override;

    bool m_hovered;
    QColor m_backColor;
    QColor m_foreColor;
    QColor m_highlightColor;
};

#endif // STYLEDTOOLBUTTON_H
