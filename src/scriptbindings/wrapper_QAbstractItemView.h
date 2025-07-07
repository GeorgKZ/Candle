#ifndef WRAPPER_QABSTRACTITEMVIEW_H
#define WRAPPER_QABSTRACTITEMVIEW_H

#include <QtCore/QObject>
#include <QtQml/QJSValue>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QStyledItemDelegate>
#include "wrapper_QWidget.h"
#include "wrapper_QSize.h"
#include "wrapper_QAbstractItemDelegate.h"

class WRAPPER_DLL_EXPORT wrapper_QAbstractItemView : public wrapper_QWidget { // wrapper_QAbstractScrollArea -> wrapper_QFrame -> wrapper_QWidget

  Q_OBJECT

  // Из файла qabstractitemview.h

  Q_PROPERTY(bool                                 autoScroll            READ hasAutoScroll         WRITE setAutoScroll)
  Q_PROPERTY(int                                  autoScrollMargin      READ autoScrollMargin      WRITE setAutoScrollMargin)
  Q_PROPERTY(QAbstractItemView::EditTriggers      editTriggers          READ editTriggers          WRITE setEditTriggers)
  Q_PROPERTY(bool                                 tabKeyNavigation      READ tabKeyNavigation      WRITE setTabKeyNavigation)
#if QT_CONFIG(draganddrop)
  Q_PROPERTY(bool                                 showDropIndicator     READ showDropIndicator     WRITE setDropIndicatorShown)
  Q_PROPERTY(bool                                 dragEnabled           READ dragEnabled           WRITE setDragEnabled)
  Q_PROPERTY(bool                                 dragDropOverwriteMode READ dragDropOverwriteMode WRITE setDragDropOverwriteMode)
  Q_PROPERTY(QAbstractItemView::DragDropMode      dragDropMode          READ dragDropMode          WRITE setDragDropMode)
  Q_PROPERTY(Qt::DropAction                       defaultDropAction     READ defaultDropAction     WRITE setDefaultDropAction)
#endif
  Q_PROPERTY(bool                                 alternatingRowColors  READ alternatingRowColors  WRITE setAlternatingRowColors)
  Q_PROPERTY(QAbstractItemView::SelectionMode     selectionMode         READ selectionMode         WRITE setSelectionMode)
  Q_PROPERTY(QAbstractItemView::SelectionBehavior selectionBehavior     READ selectionBehavior     WRITE setSelectionBehavior)
  Q_PROPERTY(QJSValue                             iconSize              READ iconSize              WRITE setIconSize NOTIFY iconSizeChanged)
  Q_PROPERTY(Qt::TextElideMode                    textElideMode         READ textElideMode         WRITE setTextElideMode)
  Q_PROPERTY(QAbstractItemView::ScrollMode        verticalScrollMode    READ verticalScrollMode    WRITE setVerticalScrollMode RESET resetVerticalScrollMode)
  Q_PROPERTY(QAbstractItemView::ScrollMode        horizontalScrollMode  READ horizontalScrollMode  WRITE setHorizontalScrollMode RESET resetHorizontalScrollMode)

public:
#if 0
  enum SelectionMode {
      NoSelection,
      SingleSelection,
      MultiSelection,
      ExtendedSelection,
      ContiguousSelection
  };
  Q_ENUM(SelectionMode)

  enum SelectionBehavior {
      SelectItems,
      SelectRows,
      SelectColumns
  };
  Q_ENUM(SelectionBehavior)

  enum ScrollHint {
      EnsureVisible,
      PositionAtTop,
      PositionAtBottom,
      PositionAtCenter
  };
  Q_ENUM(ScrollHint)

  enum EditTrigger {
      NoEditTriggers = 0,
      CurrentChanged = 1,
      DoubleClicked = 2,
      SelectedClicked = 4,
      EditKeyPressed = 8,
      AnyKeyPressed = 16,
      AllEditTriggers = 31
  };
  Q_DECLARE_FLAGS(EditTriggers, EditTrigger)
  Q_FLAG(EditTriggers)

  enum ScrollMode {
      ScrollPerItem,
      ScrollPerPixel
  };
  Q_ENUM(ScrollMode)
#endif

  Q_INVOKABLE explicit wrapper_QAbstractItemView(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(parent) {
    qDebug() << "wrapper_QAbstractItemView::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
 }

//  Q_INVOKABLE virtual void setModel(QAbstractItemModel *model);
//  Q_INVOKABLE QAbstractItemModel *model() const;

//  Q_INVOKABLE virtual void setSelectionModel(QItemSelectionModel *selectionModel);
//  Q_INVOKABLE QItemSelectionModel *selectionModel() const;

//  Q_INVOKABLE void setItemDelegate(QAbstractItemDelegate *delegate);
//  Q_INVOKABLE QAbstractItemDelegate *itemDelegate() const;

  Q_INVOKABLE void setSelectionMode(QAbstractItemView::SelectionMode mode) { get_selfptr()->setSelectionMode(mode); }
  Q_INVOKABLE QAbstractItemView::SelectionMode selectionMode() const { return get_selfptr()->selectionMode(); }

  Q_INVOKABLE void setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior) { get_selfptr()->setSelectionBehavior(behavior); }
  Q_INVOKABLE QAbstractItemView::SelectionBehavior selectionBehavior() const { return get_selfptr()->selectionBehavior(); }

  Q_INVOKABLE QModelIndex currentIndex() const { return get_selfptr()->currentIndex(); }
  Q_INVOKABLE QModelIndex rootIndex() const { return get_selfptr()->rootIndex(); }

  Q_INVOKABLE void setEditTriggers(QAbstractItemView::EditTriggers triggers) { get_selfptr()->setEditTriggers(triggers); }
  Q_INVOKABLE QAbstractItemView::EditTriggers editTriggers() const { return get_selfptr()->editTriggers(); }

  Q_INVOKABLE void setVerticalScrollMode(QAbstractItemView::ScrollMode mode) { get_selfptr()->setVerticalScrollMode(mode); }
  Q_INVOKABLE QAbstractItemView::ScrollMode verticalScrollMode() const { return get_selfptr()->verticalScrollMode(); }
  Q_INVOKABLE void resetVerticalScrollMode() { get_selfptr()->resetVerticalScrollMode(); }

  Q_INVOKABLE void setHorizontalScrollMode(QAbstractItemView::ScrollMode mode) { get_selfptr()->setHorizontalScrollMode(mode); }
  Q_INVOKABLE QAbstractItemView::ScrollMode horizontalScrollMode() const { return get_selfptr()->horizontalScrollMode(); }
  Q_INVOKABLE void resetHorizontalScrollMode() { get_selfptr()->resetHorizontalScrollMode(); }

  Q_INVOKABLE void setAutoScroll(bool enable) { get_selfptr()->setAutoScroll(enable); }
  Q_INVOKABLE bool hasAutoScroll() const { return get_selfptr()->hasAutoScroll(); }

  Q_INVOKABLE void setAutoScrollMargin(int margin) { get_selfptr()->setAutoScrollMargin(margin); }
  Q_INVOKABLE int autoScrollMargin() const { return get_selfptr()->autoScrollMargin(); }

  Q_INVOKABLE void setTabKeyNavigation(bool enable) { get_selfptr()->setTabKeyNavigation(enable); }
  Q_INVOKABLE bool tabKeyNavigation() const { return get_selfptr()->tabKeyNavigation(); }

#if QT_CONFIG(draganddrop)
  Q_INVOKABLE void setDropIndicatorShown(bool enable) { get_selfptr()->setDropIndicatorShown(enable); }
  Q_INVOKABLE bool showDropIndicator() const { return get_selfptr()->showDropIndicator(); }

  Q_INVOKABLE void setDragEnabled(bool enable) { get_selfptr()->setDragEnabled(enable); }
  Q_INVOKABLE bool dragEnabled() const { return get_selfptr()->dragEnabled(); }

  Q_INVOKABLE void setDragDropOverwriteMode(bool overwrite) { get_selfptr()->setDragDropOverwriteMode(overwrite); }
  Q_INVOKABLE bool dragDropOverwriteMode() const { return get_selfptr()->dragDropOverwriteMode(); }
#if 0
  enum DragDropMode {
    NoDragDrop,
    DragOnly,
    DropOnly,
    DragDrop,
    InternalMove
  };
  Q_ENUM(DragDropMode)
#endif
  Q_INVOKABLE void setDragDropMode(QAbstractItemView::DragDropMode behavior) { get_selfptr()->setDragDropMode(behavior); }
  Q_INVOKABLE QAbstractItemView::DragDropMode dragDropMode() const { return get_selfptr()->dragDropMode(); }

  Q_INVOKABLE void setDefaultDropAction(Qt::DropAction dropAction) { return get_selfptr()->setDefaultDropAction(dropAction); }
  Q_INVOKABLE Qt::DropAction defaultDropAction() const { return get_selfptr()->defaultDropAction(); }
#endif

  Q_INVOKABLE void setAlternatingRowColors(bool enable) { get_selfptr()->setAlternatingRowColors(enable); }
  Q_INVOKABLE bool alternatingRowColors() const { return get_selfptr()->alternatingRowColors(); }

  // void setIconSize(const QSize &size)
  Q_INVOKABLE void setIconSize(const QJSValue &size) {
    QSize *s = jsvalueToPointer(QSize, size);
    get_selfptr()->setIconSize(*s);
  }

  // QSize iconSize() const;
  Q_INVOKABLE QJSValue iconSize() const {
    QSize* size = new QSize(get_selfptr()->iconSize());
    return wrapperFactory("QSize", size);
  }

  Q_INVOKABLE void setTextElideMode(Qt::TextElideMode mode) { get_selfptr()->setTextElideMode(mode); }
  Q_INVOKABLE Qt::TextElideMode textElideMode() const { return get_selfptr()->textElideMode(); }

//  Q_INVOKABLE virtual void keyboardSearch(const QString &search);

//  Q_INVOKABLE virtual QRect visualRect(const QModelIndex &index) const = 0;
//  Q_INVOKABLE virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;
//  Q_INVOKABLE virtual QModelIndex indexAt(const QPoint &point) const = 0;

//  Q_INVOKABLE QSize sizeHintForIndex(const QModelIndex &index) const;
//  Q_INVOKABLE virtual int sizeHintForRow(int row) const;
//  Q_INVOKABLE virtual int sizeHintForColumn(int column) const;

//  Q_INVOKABLE void openPersistentEditor(const QModelIndex &index);
//  Q_INVOKABLE void closePersistentEditor(const QModelIndex &index);
//  Q_INVOKABLE bool isPersistentEditorOpen(const QModelIndex &index) const;

//  Q_INVOKABLE void setIndexWidget(const QModelIndex &index, QWidget *widget);
//  Q_INVOKABLE QWidget *indexWidget(const QModelIndex &index) const;

//  Q_INVOKABLE void setItemDelegateForRow(int row, QAbstractItemDelegate *delegate);
//  Q_INVOKABLE QAbstractItemDelegate *itemDelegateForRow(int row) const;

  // void setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate);
  Q_INVOKABLE void setItemDelegateForColumn(int column, const QJSValue &delegate) {

    QAbstractItemDelegate* val = jsvalueToPointer(QAbstractItemDelegate, delegate);
    if (val != nullptr) {
      qDebug() << "wrapper_QAbstractItemView::setItemDelegateForColumn(" << column << ", ...)";
      get_selfptr()->setItemDelegateForColumn(column, val);
    } else {
      qCritical() << "wrapper_QAbstractItemView::setItemDelegateForColumn(" << column << ", nullptr)";
    }

//    if (strcmp(delegate.toQObject()->metaObject()->className(), "wrapper_QStyledItemDelegate") == 0) {
//      get_selfptr()->setItemDelegateForColumn(column, (QStyledItemDelegate*)delegate.toQObject());
//    }
  }

  // QAbstractItemDelegate *itemDelegateForColumn(int column) const
  Q_INVOKABLE QJSValue itemDelegateForColumn(int column) const {
    qDebug() << "wrapper_QAbstractItemDelegate::itemDelegateForColumn(" << column << ")";
    QAbstractItemDelegate* val = get_selfptr()->itemDelegateForColumn(column);
    return wrapperFactory(val->metaObject()->className(), val);
  }

#if QT_DEPRECATED_SINCE(6, 0)
//  Q_INVOKABLE QT_DEPRECATED_VERSION_X_6_0("Use itemDelegateForIndex instead")
//  Q_INVOKABLE QAbstractItemDelegate *itemDelegate(const QModelIndex &index) const
#endif

//  Q_INVOKABLE virtual QAbstractItemDelegate *itemDelegateForIndex(const QModelIndex &index) const;

//  Q_INVOKABLE virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;

//!!! using QAbstractScrollArea::update;

public Q_SLOTS:

    void reset() { get_selfptr()->reset(); }

    void setRootIndex(const QModelIndex &index) { get_selfptr()->setRootIndex(index); }

    void doItemsLayout() { get_selfptr()->doItemsLayout(); }

    void selectAll() { get_selfptr()->selectAll(); }

    void edit(const QModelIndex &index) { get_selfptr()->edit(index); }

    void clearSelection() { get_selfptr()->clearSelection(); }

    void setCurrentIndex(const QModelIndex &index) { get_selfptr()->setCurrentIndex(index); }

    void scrollToTop() { get_selfptr()->scrollToTop(); }

    void scrollToBottom() { get_selfptr()->scrollToBottom(); }

    void update(const QModelIndex &index) { get_selfptr()->update(index); }

Q_SIGNALS:

  void pressed(const QJSValue &index);
  void clicked(const QJSValue &index);
  void doubleClicked(const QJSValue &index);

  void activated(const QJSValue &index);
  void entered(const QJSValue &index);
  void viewportEntered();
  void iconSizeChanged(const QJSValue &size);

public:

//!!! wrapper_QWidget // wrapper_QAbstractScrollArea -> QFrame -> QWidget

  // Конструктор из объекта
  wrapper_QAbstractItemView(QAbstractItemView *self) :
    wrapper_QWidget(static_cast<QWidget*>(self)) {
    qDebug() << "wrapper_QAbstractItemView::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QAbstractItemView* get_selfptr() const {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAbsractItemView::get_selfptr - got nullptr";
    }
    return static_cast<const QAbstractItemView*>(wrapper_QWidget::get_selfptr());
  }

  // Получение указателя на объект
  QAbstractItemView* get_selfptr() {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAbsractItemView::get_selfptr - got nullptr";
    }
    return static_cast<QAbstractItemView*>(wrapper_QWidget::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QAbstractItemView() override { }
};

Q_DECLARE_METATYPE(wrapper_QAbstractItemView)

#endif // WRAPPER_QABSTRACTITEMVIEW_H
