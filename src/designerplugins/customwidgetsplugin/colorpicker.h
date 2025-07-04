#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QColorDialog>
#include <customwidgetsshared.h>

class CUSTOMWIDGETS_DLLSPEC ColorPicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int colorInt READ colorInt WRITE setColorInt)

public:
    explicit ColorPicker(QWidget *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    int colorInt() const;
    void setColorInt(int color);

signals:
    void colorSelected(QColor color);

public slots:

private slots:
    void onButtonClicked();

private:
    QHBoxLayout *m_layout;
    QFrame *m_frame;
    QToolButton *m_button;
    QColor m_color;
};

#endif // COLORPICKER_H
