#ifndef WRAPPER_QABSTRACTITEMDELEGATE_H
#define WRAPPER_QABSTRACTITEMDELEGATE_H

#include <QtCore/QObject>
#include <QtWidgets/QAbstractItemDelegate>
#include "wrapper_QObject.h"
#include "wrapper_QWidget.h"
#include "wrapper_QModelIndex.h"
#include "wrapper_QPainter.h"

// Виртуальный класс
class wrapper_QAbstractItemDelegate : public wrapper_QObject {

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

    QPainter *p = (QPainter*)jsvalueToObject_ptr("QPainter", painter);
//    QStyleOptionViewItem *o = jsvalueToObject_ptr("QStyleOptionViewItem", option);
QStyleOptionViewItem o;
    QModelIndex *i = (QModelIndex*)jsvalueToObject_ptr("QModelIndex", index);

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

    QWidget *p = (QWidget*)jsvalueToObject_ptr("QWidget", parent);
//    QStyleOptionViewItem *o = jsvalueToObject_ptr("", option);
QStyleOptionViewItem o;

    QModelIndex *i = (QModelIndex*)jsvalueToObject_ptr("QModelIndex", index);
    return wrapperFactory("QWidget", get_selfptr()->createEditor(p, o, *i));
  }

  //!!! void destroyEditor(QWidget *editor, const QModelIndex &index) const
  Q_INVOKABLE void destroyEditor(QWidget *editor, const QModelIndex &index) const { get_selfptr()->destroyEditor(editor, index); }

  // void setEditorData(QWidget *editor, const QModelIndex &index) const
  Q_INVOKABLE void setEditorData(const QJSValue &editor, const QJSValue &index) const {

    qDebug() << "QAbsractItemDelegate::setEditorData(...)";

    QWidget *e = (QWidget*)jsvalueToObject_ptr("QWidget", editor);
    QModelIndex *i = (QModelIndex*)jsvalueToObject_ptr("QModelIndex", index);
    get_selfptr()->setEditorData(e, *i);
  }

  // void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
  Q_INVOKABLE void setModelData(const QJSValue &editor, const QJSValue &model, const QJSValue &index) const {
Q_UNUSED(model)
    qDebug() << "QAbsractItemDelegate::setModelData(...)";

    QWidget *e = (QWidget*)jsvalueToObject_ptr("QWidget", editor);
    QAbstractItemModel *m = nullptr;
    QModelIndex *i = (QModelIndex*)jsvalueToObject_ptr("QModelIndex", index);
    get_selfptr()->setModelData(e, m, *i);
  }

  // void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
  Q_INVOKABLE void updateEditorGeometry(const QJSValue &editor, const QJSValue &option, const QJSValue &index) const {
Q_UNUSED(option)
    qDebug() << "QAbsractItemDelegate::updateEditorGeometry(...)";

    QWidget *e = (QWidget*)jsvalueToObject_ptr("QWidget", editor);
QStyleOptionViewItem o;
    QModelIndex *i = (QModelIndex*)jsvalueToObject_ptr("QModelIndex", index);

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
  wrapper_QAbstractItemDelegate(QAbstractItemDelegate* self) :
    wrapper_QObject(self) {
    qDebug() << "wrapper_QAbstractItemDelegate::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QAbstractItemDelegate() {
    delete static_cast<QAbstractItemDelegate*>(wrapper_QObject::get_selfptr());
  }

  // Получение константного указателя на объект
  const QAbstractItemDelegate* get_selfptr() const {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAbsractItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<const QAbstractItemDelegate*>(wrapper_QObject::get_selfptr());
  }

  // Получение указателя на объект
  QAbstractItemDelegate* get_selfptr() {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAbsractItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<QAbstractItemDelegate*>(wrapper_QObject::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QAbstractItemDelegate);

#endif // WRAPPER_QABSTRACTITEMDELEGATE_H
