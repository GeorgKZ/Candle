#include "wrapper_QModelIndex.h"

wrapper_QModelIndex::wrapper_QModelIndex() :
  wrapper_common(new QModelIndex()) {
  qDebug() << "wrapper_QModelIndex::constructor()";
}

// int row() const
int wrapper_QModelIndex::row() const {
  return get_selfptr()->row();
}

// int column() const
int wrapper_QModelIndex::column() const {
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
Qt::ItemFlags wrapper_QModelIndex::flags() const {
  return get_selfptr()->flags();
}

// const QAbstractItemModel *model() const

// bool isValid() const
bool wrapper_QModelIndex::isValid() const {
  return get_selfptr()->isValid();
}

// bool operator==(const QModelIndex &other) const

// bool operator!=(const QModelIndex &other) const

// bool operator<(const QModelIndex &other) const

// Конструктор из объекта
wrapper_QModelIndex::wrapper_QModelIndex(void *self) : wrapper_common(self) {
  qDebug() << "wrapper_QModelIndex::constructor(self=" << get_selfvalue() << ")";
}

// Деструктор
wrapper_QModelIndex::~wrapper_QModelIndex() {
  qDebug() << "wrapper_QModelIndex::destructor(self=" << get_selfvalue() << ")";
}

// Получение константного указателя на объект
const QModelIndex* wrapper_QModelIndex::get_selfptr() const {
  return static_cast<const QModelIndex*>(wrapper_common::get_selfptr());
}

// Получение указателя на объект
QModelIndex* wrapper_QModelIndex::get_selfptr() {
  return static_cast<QModelIndex*>(wrapper_common::get_selfptr());
}
