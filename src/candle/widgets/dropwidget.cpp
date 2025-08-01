// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QtCore/QDebug>
#include <QtGui/QDragEnterEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <algorithm>
#include "dropwidget.h"
#include "widgetmimedata.h"

DropWidget::DropWidget(QWidget *parent) : QWidget(parent)
{
    m_layoutIndex = -2;
}

void DropWidget::restoreState(QObject* parent, QStringList panels)
{
    QVBoxLayout *lo = static_cast<QVBoxLayout*>(layout());
    int i = 0;

    foreach (QString s, panels) {
        QGroupBox *b = parent->findChild<QGroupBox*>(s);
        if (b) lo->insertWidget(i++, b);
    }
}

QStringList DropWidget::saveState()
{
    QStringList sl;
    QVBoxLayout *lo = static_cast<QVBoxLayout*>(layout());

    for (int i = 0; i < lo->count(); i++) {
        QString n = lo->itemAt(i)->widget()->objectName();
        if (n.startsWith("grp")) sl << n;
    }

    return sl;
}

void DropWidget::dragEnterEvent(QDragEnterEvent *dee)
{
    if (dee->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        m_layoutIndex = -2;
        dee->acceptProposedAction();

    }

    QWidget::dragEnterEvent(dee);
}

void DropWidget::dragLeaveEvent(QDragLeaveEvent *dle)
{
    QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);
    if (f) f->setVisible(false);
    // m_layoutIndex = -2;

    QWidget::dragLeaveEvent(dle);
}

void DropWidget::dragMoveEvent(QDragMoveEvent *dme)
{
    if (dme->mimeData()->hasFormat(WidgetMimeData::mimeType())) {

        /**
         * Алгоритм:
         *
         * 1. Найти прямой дочерний фрейм виджета.
         */
        QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);

        if (f) {

            /**
             * 2. Получить горизонтальную позицию из сообщения о перемещении.
             */
            int y = dme->position().toPoint().y();

            /**
             * Получить список прямых дочерних QGroupBox виджета.
             */
            QList<QGroupBox*> bl = findChildren<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);

            /**
             * 3. Составить сортированный список горизонтальных позиций дочерних QGroupBox виджета,
             * соответствующих индексам layout.
             */
            QList<int> yl;
            foreach (QGroupBox* b, bl) yl << b->pos().y();
            std::sort(yl.begin(), yl.end());

            /**
             * 4. Найти значение первого индекса, для которого горизонтальная позиция 
             * превышает горизонтальную позицию из сообщения о перемещении.
             */
            int i;
            for (i = 0; i < yl.count(); ++i) {
                if (yl.at(i) > y) break;
            }

            /**
             * 5. Если полученное значение индекса не соответствует индексу layout виджета,
             * вставить дочерний фрейм виджета с предыдущим индексом.
             */
            if (i != m_layoutIndex) {
                static_cast<QVBoxLayout*>(layout())->insertWidget(i - 1, f);
                if (!f->isVisible()) f->setVisible(true);
                f->update();
            }

            /**
             * 6. Присвоить индексу layout виджета полученное значение индекса.
             */
            m_layoutIndex = i;
        }
    }

    QWidget::dragMoveEvent(dme);
}

void DropWidget::dropEvent(QDropEvent *de)
{
    if (de->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);
        if (f) {
            const WidgetMimeData *md = static_cast<const WidgetMimeData*>(de->mimeData());
            f->setVisible(false);
            f->update();
            static_cast<QVBoxLayout*>(layout())->insertWidget(m_layoutIndex - 1, md->widget());
            md->widget()->update();
        }
    }
}
