#ifndef WRAPPER_QTABLEWIDGET_H
#define WRAPPER_QTABLEWIDGET_H

#include <QtCore/QObject>
#include <QtWidgets/QTableWidget>
#include "wrapper_QTableView.h"
#include "wrapper_QTableWidgetItem.h"

class WRAPPER_DLL_EXPORT wrapper_QTableWidget : public wrapper_QTableView {

  Q_OBJECT

  // Из файла qtablewidget.h

  Q_PROPERTY(int rowCount
      READ rowCount
      WRITE setRowCount)
  Q_PROPERTY(int columnCount
      READ columnCount
      WRITE setColumnCount)

public:

  Q_INVOKABLE explicit wrapper_QTableWidget(const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QTableView(new QTableWidget(jsvalueToPointer(QWidget, parent)))  {
      qDebug() << "wrapper_QTableWidget::constructor(parent=" << reinterpret_cast<unsigned long long>(jsvalueToPointer(QWidget, parent)) << ")";
  }

  Q_INVOKABLE explicit wrapper_QTableWidget(int rows, int columns, wrapper_QWidget *parent = nullptr) :
    wrapper_QTableView(new QTableWidget(rows, columns, parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QTableWidget::constructor(" << rows << "," << columns << "," << parent << ")";
  }

  Q_INVOKABLE void setRowCount(int rows) { get_selfptr()->setRowCount(rows); }
  Q_INVOKABLE int rowCount() const { return get_selfptr()->rowCount(); }

  Q_INVOKABLE void setColumnCount(int columns) { get_selfptr()->setColumnCount(columns); }
  Q_INVOKABLE int columnCount() const { return get_selfptr()->columnCount(); }
//!!!! wrapper?
  Q_INVOKABLE int row(const QTableWidgetItem *item) const { return get_selfptr()->row(item); }
  Q_INVOKABLE int column(const QTableWidgetItem *item) const { return get_selfptr()->column(item); }

  // QTableWidgetItem* item(int row, int column)
  Q_INVOKABLE QObject *item(int row, int column) const { return new wrapper_QTableWidgetItem(get_selfptr()->item(row, column)); }
  Q_INVOKABLE void setItem(int row, int column, wrapper_QTableWidgetItem *item) { get_selfptr()->setItem(row, column, item->get_selfptr()); }
  // QTableWidgetItem *takeItem(int row, int column)
  Q_INVOKABLE QObject *takeItem(int row, int column) { return new wrapper_QTableWidgetItem(get_selfptr()->takeItem(row, column)); }
//  Q_INVOKABLE QList<QTableWidgetItem*> items(const QMimeData *data) const;
//  Q_INVOKABLE QModelIndex indexFromItem(const QTableWidgetItem *item) const;
//  Q_INVOKABLE QTableWidgetItem *itemFromIndex(const QModelIndex &index) const;

  // QTableWidgetItem* verticalHeaderItem(int row)
  Q_INVOKABLE QObject *verticalHeaderItem(int row) const { return new wrapper_QTableWidgetItem(get_selfptr()->verticalHeaderItem(row)); }
//  Q_INVOKABLE void setVerticalHeaderItem(int row, QTableWidgetItem *item);
//  Q_INVOKABLE QTableWidgetItem *takeVerticalHeaderItem(int row);

//  Q_INVOKABLE QTableWidgetItem *horizontalHeaderItem(int column) const;
//  Q_INVOKABLE void setHorizontalHeaderItem(int column, QTableWidgetItem *item);
//  Q_INVOKABLE QTableWidgetItem *takeHorizontalHeaderItem(int column);
//  Q_INVOKABLE void setVerticalHeaderLabels(const QStringList &labels);
//  Q_INVOKABLE void setHorizontalHeaderLabels(const QStringList &labels);

  Q_INVOKABLE int currentRow() const { return get_selfptr()->currentRow(); }
  Q_INVOKABLE int currentColumn() const { return get_selfptr()->currentColumn(); }
//  Q_INVOKABLE QTableWidgetItem *currentItem() const;
//  Q_INVOKABLE void setCurrentItem(QTableWidgetItem *item);
//  Q_INVOKABLE void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlags command);
  Q_INVOKABLE void setCurrentCell(int row, int column) { get_selfptr()->setCurrentCell(row, column); }
//  Q_INVOKABLE void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command);

//  Q_INVOKABLE void sortItems(int column, Qt::SortOrder order = Qt::AscendingOrder);
  Q_INVOKABLE void setSortingEnabled(bool enable) { get_selfptr()->setSortingEnabled(enable); }
  Q_INVOKABLE bool isSortingEnabled() const { return get_selfptr()->isSortingEnabled(); }

//  Q_INVOKABLE void editItem(QTableWidgetItem *item);
//  Q_INVOKABLE void openPersistentEditor(QTableWidgetItem *item);
//  Q_INVOKABLE void closePersistentEditor(QTableWidgetItem *item);
//  using QAbstractItemView::isPersistentEditorOpen;
//  Q_INVOKABLE bool isPersistentEditorOpen(QTableWidgetItem *item) const;

//  Q_INVOKABLE QWidget *cellWidget(int row, int column) const;
//  Q_INVOKABLE void setCellWidget(int row, int column, QWidget *widget);
  Q_INVOKABLE void removeCellWidget(int row, int column) { get_selfptr()->removeCellWidget(row, column); }

//  Q_INVOKABLE void setRangeSelected(const QTableWidgetSelectionRange &range, bool select);

//  Q_INVOKABLE QList<QTableWidgetSelectionRange> selectedRanges() const;
//  Q_INVOKABLE QList<QTableWidgetItem*> selectedItems() const;
//  Q_INVOKABLE QList<QTableWidgetItem*> findItems(const QString &text, Qt::MatchFlags flags) const;

  Q_INVOKABLE int visualRow(int logicalRow) const { return get_selfptr()->visualRow(logicalRow); }
  Q_INVOKABLE int visualColumn(int logicalColumn) const { return get_selfptr()->visualColumn(logicalColumn); }

//  Q_INVOKABLE QTableWidgetItem *itemAt(const QPoint &p) const;
//  Q_INVOKABLE QTableWidgetItem *itemAt(int x, int y) const;
//  Q_INVOKABLE QRect visualItemRect(const QTableWidgetItem *item) const;

//  Q_INVOKABLE const QTableWidgetItem *itemPrototype() const;
//  Q_INVOKABLE void setItemPrototype(const QTableWidgetItem *item);

public Q_SLOTS:

//  Q_INVOKABLE void scrollToItem(const QTableWidgetItem *item, QAbstractItemView::ScrollHint hint = EnsureVisible);
  Q_INVOKABLE void insertRow(int row) { get_selfptr()->insertRow(row); }
  Q_INVOKABLE void insertColumn(int column) { get_selfptr()->insertColumn(column); }
  Q_INVOKABLE void removeRow(int row) { get_selfptr()->removeRow(row); }
  Q_INVOKABLE void removeColumn(int column) { get_selfptr()->removeColumn(column); }
  Q_INVOKABLE void clear() { get_selfptr()->clear(); }
  Q_INVOKABLE void clearContents() { get_selfptr()->clearContents(); }

Q_SIGNALS:

    void itemPressed(QTableWidgetItem *item);
    void itemClicked(QTableWidgetItem *item);
    void itemDoubleClicked(QTableWidgetItem *item);

    void itemActivated(QTableWidgetItem *item);
    void itemEntered(QTableWidgetItem *item);
    void itemChanged(QTableWidgetItem *item);

    void currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void itemSelectionChanged();

    void cellPressed(int row, int column);
    void cellClicked(int row, int column);
    void cellDoubleClicked(int row, int column);

    void cellActivated(int row, int column);
    void cellEntered(int row, int column);
    void cellChanged(int row, int column);

    void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

public:

  // Конструктор из объекта
  explicit wrapper_QTableWidget(void *self) : wrapper_QTableView(self) {
    qDebug() << "QTableWidget::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QTableWidget() override {
    qDebug() << "QTableWidget::destructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QTableWidget* get_selfptr() const {
    return static_cast<const QTableWidget*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QTableWidget* get_selfptr() {
    return static_cast<QTableWidget*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QTableWidget)

#endif // WRAPPER_QTABLEWIDGET_H
