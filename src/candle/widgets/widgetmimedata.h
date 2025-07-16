#ifndef WIDGETMIMEDATA_H
#define WIDGETMIMEDATA_H

#include <QtCore/QMimeData>
#include <QtWidgets/QWidget>

class WidgetMimeData: public QMimeData
{

public:

    WidgetMimeData();

    virtual ~WidgetMimeData() override;

    static QString mimeType();

    void setWidget(QWidget *widget);

    QWidget *widget() const;

private:

    QWidget* m_widget;
};

#endif // WIDGETMIMEDATA_H
