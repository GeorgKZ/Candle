#ifndef SHORTCUTDELEGATE_H
#define SHORTCUTDELEGATE_H

#include <QtWidgets/QStyledItemDelegate>

class ShortcutDelegate: public QStyledItemDelegate {

public:

    ShortcutDelegate();

    virtual ~ShortcutDelegate() override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // SHORTCUTDELEGATE_H
