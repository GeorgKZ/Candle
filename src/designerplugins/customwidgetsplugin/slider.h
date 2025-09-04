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
#if !defined(__DOXYGEN__)
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue)
#endif

public:

    explicit Slider(QWidget *parent = nullptr);

    int currentValue() const;
    void setCurrentValue(int currentValue);

protected:

    virtual void paintEvent(QPaintEvent *ev) override;

private:

    int m_currentValue;

};

Q_DECLARE_METATYPE(Slider)

#endif // SLIDER_H
