#ifndef WRAPPER_QMODELINDEX_H
#define WRAPPER_QMODELINDEX_H

#include <QtCore/QObject>
#include <QtCore/QModelIndex>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QModelIndex : public wrapper_common {

  // Из файла qabstractitemmodel.h

public:

  wrapper_QModelIndex() :
    wrapper_common(new QModelIndex()) {
    qDebug() << "wrapper_QModelIndex::constructor()";
  }

  // int row() const
  Q_INVOKABLE int row() const {
    return get_selfptr()->row();
  }

  // int column() const
  Q_INVOKABLE int column() const {
    return get_selfptr()->column();
  }

  // quintptr internalId() const

  // void *internalPointer() const

  // const void *constInternalPointer() const

  // QModelIndex parent() const;

  // QModelIndex sibling(int row, int column) const;

  // QModelIndex siblingAtColumn(int column) const;

  // QModelIndex siblingAtRow(int row) const;

  // QVariant data(int role = Qt::DisplayRole) const;

  // void multiData(QModelRoleDataSpan roleDataSpan) const;

  // Qt::ItemFlags flags() const;
  Q_INVOKABLE Qt::ItemFlags flags() const {
    return get_selfptr()->flags();
  }

  // const QAbstractItemModel *model() const

  // bool isValid() const
  bool isValid() const {
    return get_selfptr()->isValid();
  }

  // bool operator==(const QModelIndex &other) const

  // bool operator!=(const QModelIndex &other) const

  // bool operator<(const QModelIndex &other) const

public:

  // Конструктор из объекта
  wrapper_QModelIndex(void *self) : wrapper_common(self) {
    qDebug() << "wrapper_QModelIndex::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QModelIndex() override {
    qDebug() << "wrapper_QModelIndex::destructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QModelIndex* get_selfptr() const {
    return static_cast<const QModelIndex*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QModelIndex* get_selfptr() {
    return static_cast<QModelIndex*>(wrapper_common::get_selfptr());
  }
};

#endif // WRAPPER_QMODELINDEX_H
