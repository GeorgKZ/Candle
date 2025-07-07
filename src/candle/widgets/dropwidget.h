// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QtWidgets/QWidget>

class DropWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DropWidget(QWidget *parent = nullptr);
    
    void restoreState(QObject* parent, QStringList panels);
    QStringList saveState();

protected:

    virtual void dragEnterEvent(QDragEnterEvent *dee) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *dle) override;
    virtual void dragMoveEvent(QDragMoveEvent *dme) override;
    virtual void dropEvent(QDropEvent *de) override;

private:
    int m_layoutIndex;
};

#endif // WIDGET_H
