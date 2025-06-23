#ifndef SLIDER_H
#define SLIDER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include "customwidgetsshared.h"

class CUSTOMWIDGETS_DLLSPEC Slider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue)
public:
    explicit Slider(QWidget *parent = nullptr);

    int currentValue() const;
    void setCurrentValue(int currentValue);

protected:
    void paintEvent(QPaintEvent *ev);

private:
    int m_currentValue;

};

#endif // SLIDER_H
