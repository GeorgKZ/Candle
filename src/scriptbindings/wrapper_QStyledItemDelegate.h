#ifndef WRAPPER_QSTYLEDITEMDELEGATE_H
#define WRAPPER_QSTYLEDITEMDELEGATE_H

#include <QtCore/QObject>
#include <QtWidgets/QStyledItemDelegate>
#include "wrapper_QAbstractItemDelegate.h"

//!!! Использовать врапперы! QPainter, QStyleOptionViewItem, QModelIndex

class WRAPPER_DLL_EXPORT wrapper_QStyledItemDelegate : public wrapper_QAbstractItemDelegate {

  Q_OBJECT

  // из файла qstyleditemdelegate.h

public:

  // explicit QStyledItemDelegate(QObject *parent = nullptr);
  Q_INVOKABLE wrapper_QStyledItemDelegate(const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QAbstractItemDelegate(new QStyledItemDelegate(jsvalueToPointer(QObject, parent))) {
     qDebug() << "wrapper_QStyledItemDelegate::constructor(parent=" <<
       reinterpret_cast<unsigned long long>(jsvalueToPointer(QObject, parent)) << ")";
  }

  // painting
  // void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  // Реализовано в базовом прокси-класса

  // QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
  // Реализовано в базовом прокси-класса

  // editing
  // QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
  // Реализовано в базовом прокси-класса

  // void setEditorData(QWidget *editor, const QModelIndex &index) const
  // Реализовано в базовом прокси-класса

  // void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
  // Реализовано в базовом прокси-класса

  // void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
  // Реализовано в базовом прокси-класса

  // editor factory
  Q_INVOKABLE QItemEditorFactory *itemEditorFactory() const {
    return get_selfptr()->itemEditorFactory();
  }

  Q_INVOKABLE void setItemEditorFactory(QItemEditorFactory *factory) {
    get_selfptr()->setItemEditorFactory(factory);
  }

  //!!! QString displayText(const QVariant &value, const QLocale &locale) const
  Q_INVOKABLE QString displayText(const QVariant &value, const QLocale &locale) const {
    return get_selfptr()->displayText(value, locale);
  }

public:

  // Конструктор из объекта
  wrapper_QStyledItemDelegate(QStyledItemDelegate *self) :
    wrapper_QAbstractItemDelegate(self) {
    qDebug() << "wrapper_QStyledItemDelegate::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QStyledItemDelegate* get_selfptr() const {
    if (wrapper_QAbstractItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<const QStyledItemDelegate*>(wrapper_QAbstractItemDelegate::get_selfptr());
  }

  // Получение указателя на объект
  QStyledItemDelegate* get_selfptr() {
    if (wrapper_QAbstractItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<QStyledItemDelegate*>(wrapper_QAbstractItemDelegate::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QStyledItemDelegate() override { }
};

Q_DECLARE_METATYPE(wrapper_QStyledItemDelegate)


#endif // WRAPPER_QSTYLEDITEMDELEGATE_H
