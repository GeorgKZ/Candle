#ifndef WRAPPER_QABSTRACTITEMDELEGATE_H
#define WRAPPER_QABSTRACTITEMDELEGATE_H

#include <QObject>
#include <QAbstractItemDelegate>
#include "wrapper_QObject.h"
#include "wrapper_QWidget.h"
#include "wrapper_QModelIndex.h"
#include "wrapper_QPainter.h"

// Виртуальный класс
class WRAPPER_DLL_EXPORT wrapper_QAbstractItemDelegate : public wrapper_QObject {

  Q_OBJECT

public:

  // Из файла qabstractitemdelegate.h

  Q_INVOKABLE explicit wrapper_QAbstractItemDelegate(wrapper_QObject *parent = nullptr) :
    wrapper_QObject(new QObject(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QAbstractItemDelegate::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // painting
  // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
  Q_INVOKABLE void paint(const QJSValue &painter, const QJSValue &option, const QJSValue &index) const {
Q_UNUSED(option)
    qDebug() << "QAbsractItemDelegate::paint(...)";

    QPainter *p = jsvalueToPointer(QPainter, painter);
//!!!TODO!!!    QStyleOptionViewItem *o = jsvalueToPointer(QStyleOptionViewItem, option);
QStyleOptionViewItem o;
    QModelIndex *i = jsvalueToPointer(QModelIndex, index);

    get_selfptr()->paint(p, o, *i);
  }

  //!!! QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
  Q_INVOKABLE QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return get_selfptr()->sizeHint(option, index);
  }

  // editing
  // QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
  Q_INVOKABLE QJSValue createEditor(const QJSValue &parent, const QJSValue &option, const QJSValue &index) const {
Q_UNUSED(option)
    qDebug() << "QAbsractItemDelegate::createEditor(...)";

    QWidget *p = jsvalueToPointer(QWidget, parent);
//!!!TODO!!!    QStyleOptionViewItem *o = jsvalueToPointer(QStyleOptionViewItem, option);
QStyleOptionViewItem o;

    QModelIndex *i = jsvalueToPointer(QModelIndex, index);
    return PointerToJsvalue(QWidget, get_selfptr()->createEditor(p, o, *i));
  }

  //!!! void destroyEditor(QWidget *editor, const QModelIndex &index) const
  Q_INVOKABLE void destroyEditor(QWidget *editor, const QModelIndex &index) const { get_selfptr()->destroyEditor(editor, index); }

  // void setEditorData(QWidget *editor, const QModelIndex &index) const
  Q_INVOKABLE void setEditorData(const QJSValue &editor, const QJSValue &index) const {

    qDebug() << "QAbsractItemDelegate::setEditorData(...)";

    QWidget *e = jsvalueToPointer(QWidget, editor);
    QModelIndex *i = jsvalueToPointer(QModelIndex, index);
    get_selfptr()->setEditorData(e, *i);
  }

  // void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
  Q_INVOKABLE void setModelData(const QJSValue &editor, const QJSValue &model, const QJSValue &index) const {
Q_UNUSED(model)
    qDebug() << "QAbsractItemDelegate::setModelData(...)";

    QWidget *e = jsvalueToPointer(QWidget, editor);
    //!!!TODO!!! использовать аргумент
    QAbstractItemModel *m = nullptr;
    QModelIndex *i = jsvalueToPointer(QModelIndex, index);
    get_selfptr()->setModelData(e, m, *i);
  }

  // void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
  Q_INVOKABLE void updateEditorGeometry(const QJSValue &editor, const QJSValue &option, const QJSValue &index) const {
Q_UNUSED(option)
    qDebug() << "QAbsractItemDelegate::updateEditorGeometry(...)";

    QWidget *e = jsvalueToPointer(QWidget, editor);
//!!!TODO!!! Использовать аргумент
QStyleOptionViewItem o;
    QModelIndex *i = jsvalueToPointer(QModelIndex, index);

    get_selfptr()->updateEditorGeometry(e, o, *i);
  }

  // for non-widget editors
  Q_INVOKABLE virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) { return get_selfptr()->editorEvent(event, model, option, index); }
  Q_INVOKABLE virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) { return get_selfptr()->helpEvent(event, view, option, index); }
  Q_INVOKABLE virtual QList<int> paintingRoles() const { return get_selfptr()->paintingRoles(); }

Q_SIGNALS:

  void commitData(QWidget *editor);
  void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);
  void sizeHintChanged(const QModelIndex &);

public:

  // Конструктор из объекта
  wrapper_QAbstractItemDelegate(void *self) : wrapper_QObject(self) {
    qDebug() << "wrapper_QAbstractItemDelegate::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QAbstractItemDelegate() override {
    qDebug() << "wrapper_QAbstractItemDelegate::destructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QAbstractItemDelegate* get_selfptr() const {
    return static_cast<const QAbstractItemDelegate*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QAbstractItemDelegate* get_selfptr() {
    return static_cast<QAbstractItemDelegate*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QAbstractItemDelegate)

#endif // WRAPPER_QABSTRACTITEMDELEGATE_H
