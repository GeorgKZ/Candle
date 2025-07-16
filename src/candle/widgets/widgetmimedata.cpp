#include <QtCore/QMimeData>
#include <QtWidgets/QWidget>
#include "widgetmimedata.h"

WidgetMimeData::WidgetMimeData(): QMimeData()
{
    m_widget = nullptr;
}

WidgetMimeData::~WidgetMimeData()
{
}

QString WidgetMimeData::mimeType()
{
    return "application/widget";
}

void WidgetMimeData::setWidget(QWidget *widget)
{
    setData(WidgetMimeData::mimeType(), QByteArray());
    m_widget = widget;
}

QWidget *WidgetMimeData::widget() const
{
    return m_widget;
}
