#ifndef WRAPPER_QMODELINDEX_H
#define WRAPPER_QMODELINDEX_H

#include <QObject>
#include <QModelIndex>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QModelIndex : public wrapper_common {

  // Из файла qabstractitemmodel.h

public:

  wrapper_QModelIndex();

  // int row() const
  Q_INVOKABLE int row() const;

  // int column() const
  Q_INVOKABLE int column() const;

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
  Q_INVOKABLE Qt::ItemFlags flags() const;

  // const QAbstractItemModel *model() const

  // bool isValid() const
  bool isValid() const;

  // bool operator==(const QModelIndex &other) const

  // bool operator!=(const QModelIndex &other) const

  // bool operator<(const QModelIndex &other) const

public:

  // Конструктор из объекта
  wrapper_QModelIndex(void *self);

  // Деструктор
  virtual ~wrapper_QModelIndex() override;

  // Получение константного указателя на объект
  const QModelIndex* get_selfptr() const;

  // Получение указателя на объект
  QModelIndex* get_selfptr();
};

Q_DECLARE_METATYPE(wrapper_QModelIndex)

#endif // WRAPPER_QMODELINDEX_H
