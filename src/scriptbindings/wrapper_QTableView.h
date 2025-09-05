#ifndef WRAPPER_QTABLEVIEW_H
#define WRAPPER_QTABLEVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QHeaderView>
#include "wrapper_QAbstractItemView.h"
#include "wrapper_QHeaderView.h"

class WRAPPER_DLL_EXPORT wrapper_QTableView : public wrapper_QAbstractItemView {

  Q_OBJECT

    Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid)
//!!!    Q_PROPERTY(Qt::PenStyle gridStyle READ gridStyle WRITE setGridStyle)
    Q_PROPERTY(bool sortingEnabled READ isSortingEnabled WRITE setSortingEnabled)
    Q_PROPERTY(bool wordWrap READ wordWrap WRITE setWordWrap)

public:
#if 0
  // qabstractitemview
  enum ScrollHint {
      EnsureVisible,
      PositionAtTop,
      PositionAtBottom,
      PositionAtCenter
  };
  Q_ENUM(ScrollHint)
#endif

  // Из файла qtableview.h

  Q_INVOKABLE explicit wrapper_QTableView(wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractItemView(static_cast<QAbstractItemView*>
      (new QTableView(parent == nullptr ? nullptr : parent->get_selfptr()))) {
     qDebug() << "wrapper_QTableView::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  Q_INVOKABLE void setModel(QAbstractItemModel *model) { get_selfptr()->setModel(model); }
  Q_INVOKABLE void setRootIndex(const QModelIndex &index) { get_selfptr()->setRootIndex(index); }
  Q_INVOKABLE void setSelectionModel(QItemSelectionModel *selectionModel) { get_selfptr()->setSelectionModel(selectionModel); }
  Q_INVOKABLE void doItemsLayout() { get_selfptr()->doItemsLayout(); }

  // QHeaderView *horizontalHeader() const
  Q_INVOKABLE QJSValue horizontalHeader() const {
      return PointerToJsvalue(QHeaderView, get_selfptr()->horizontalHeader());
  }

  // QHeaderView *verticalHeader() const
  Q_INVOKABLE QJSValue verticalHeader() const {
      return PointerToJsvalue(QHeaderView, get_selfptr()->verticalHeader());
  }

  // void setHorizontalHeader(QHeaderView *header)
  Q_INVOKABLE void setHorizontalHeader(const QJSValue &header)
  {
      get_selfptr()->setHorizontalHeader(jsvalueToPointer(QHeaderView, header));
  }

  // void setVerticalHeader(QHeaderView *header)
  Q_INVOKABLE void setVerticalHeader(const QJSValue &header)
  {
      get_selfptr()->setVerticalHeader(jsvalueToPointer(QHeaderView, header));
  }

  Q_INVOKABLE int rowViewportPosition(int row) { return get_selfptr()->rowViewportPosition(row); }
  Q_INVOKABLE int rowAt(int y) const { return get_selfptr()->rowAt(y); }

  Q_INVOKABLE void setRowHeight(int row, int height) { get_selfptr()->setRowHeight(row, height); }
  Q_INVOKABLE int rowHeight(int row) const { return get_selfptr()->rowHeight(row); }

  Q_INVOKABLE int columnViewportPosition(int column) const { return get_selfptr()->columnViewportPosition(column); }
  Q_INVOKABLE int columnAt(int x) const { return get_selfptr()->columnAt(x); }

  Q_INVOKABLE void setColumnWidth(int column, int width){ get_selfptr()->setColumnWidth(column, width); }
  Q_INVOKABLE int columnWidth(int column) const { return get_selfptr()->columnWidth(column); }

  Q_INVOKABLE bool isRowHidden(int row) const { return get_selfptr()->isRowHidden(row); }
  Q_INVOKABLE void setRowHidden(int row, bool hide) { get_selfptr()->setRowHidden(row, hide); }

  Q_INVOKABLE bool isColumnHidden(int column) const { return get_selfptr()->isColumnHidden(column); }
  Q_INVOKABLE void setColumnHidden(int column, bool hide) { get_selfptr()->setColumnHidden(column, hide); }

  Q_INVOKABLE void setSortingEnabled(bool enable) { get_selfptr()->setSortingEnabled(enable); }
  Q_INVOKABLE bool isSortingEnabled() const { return get_selfptr()->isSortingEnabled(); }

  Q_INVOKABLE bool showGrid() const { return get_selfptr()->showGrid(); }

  Q_INVOKABLE Qt::PenStyle gridStyle() const { return get_selfptr()->gridStyle(); }
  Q_INVOKABLE void setGridStyle(Qt::PenStyle style) { get_selfptr()->setGridStyle(style); }

  Q_INVOKABLE void setWordWrap(bool on) { get_selfptr()->setWordWrap(on); }
  Q_INVOKABLE bool wordWrap() const { return get_selfptr()->wordWrap(); }

  Q_INVOKABLE QRect visualRect(const QModelIndex &index) const { return get_selfptr()->visualRect(index); }
  Q_INVOKABLE void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible) { get_selfptr()->scrollTo(index, hint); }
  Q_INVOKABLE QModelIndex indexAt(const QPoint &p) const { return get_selfptr()->indexAt(p); }

  Q_INVOKABLE void setSpan(int row, int column, int rowSpan, int columnSpan) { return get_selfptr()->setSpan(row, column, rowSpan, columnSpan); }
  Q_INVOKABLE int rowSpan(int row, int column) const { return get_selfptr()->rowSpan(row, column); }
  Q_INVOKABLE int columnSpan(int row, int column) const { return get_selfptr()->columnSpan(row, column); }
  Q_INVOKABLE void clearSpans() { get_selfptr()->clearSpans(); }

public Q_SLOTS:

  Q_INVOKABLE void selectRow(int row) { get_selfptr()->selectRow(row); }
  Q_INVOKABLE void selectColumn(int column) { get_selfptr()->selectColumn(column); }
  Q_INVOKABLE void hideRow(int row) { get_selfptr()->hideRow(row); }
  Q_INVOKABLE void hideColumn(int column) { get_selfptr()->hideColumn(column); }
  Q_INVOKABLE void showRow(int row) { get_selfptr()->showRow(row); }
  Q_INVOKABLE void showColumn(int column) { get_selfptr()->showColumn(column); }
  Q_INVOKABLE void resizeRowToContents(int row) { get_selfptr()->resizeRowToContents(row); }
  Q_INVOKABLE void resizeRowsToContents() { get_selfptr()->resizeRowsToContents(); }
  Q_INVOKABLE void resizeColumnToContents(int column) { get_selfptr()->resizeColumnToContents(column); }
  Q_INVOKABLE void resizeColumnsToContents() { get_selfptr()->resizeColumnsToContents(); }
  Q_INVOKABLE void sortByColumn(int column, Qt::SortOrder order) { get_selfptr()->sortByColumn(column, order); }
  Q_INVOKABLE void setShowGrid(bool show) { get_selfptr()->setShowGrid(show); }

public:

  // Конструктор из объекта
  wrapper_QTableView(void *self) : wrapper_QAbstractItemView(self) {
    qDebug() << "wrapper_QTableView::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QTableView* get_selfptr() const {
    return static_cast<const QTableView*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QTableView* get_selfptr() {
    return static_cast<QTableView*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QTableView() override {
    qDebug() << "wrapper_QTableView::destructor(self=" << get_selfvalue() << ")";
  }
};

Q_DECLARE_METATYPE(wrapper_QTableView)

#endif // WRAPPER_QTABLEVIEW_H
