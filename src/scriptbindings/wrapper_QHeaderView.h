#ifndef WRAPPER_QHEADERVIEW_H
#define WRAPPER_QHEADERVIEW_H

#include <QtCore/QObject>
#include <QtWidgets/QHeaderView>
#include "wrapper_QAbstractItemView.h"
#include "wrapper_QSize.h"

class WRAPPER_DLL_EXPORT wrapper_QHeaderView : public wrapper_QAbstractItemView {

  Q_OBJECT

  // Из файла qheaderview.h

  Q_PROPERTY(bool          firstSectionMovable      READ isFirstSectionMovable      WRITE setFirstSectionMovable)
//!!!
#if 0
  Q_PROPERTY(bool          showSortIndicator        READ isSortIndicatorShown       WRITE setSortIndicatorShown)
  Q_PROPERTY(bool          highlightSections        READ highlightSections          WRITE setHighlightSections)
  Q_PROPERTY(bool          stretchLastSection       READ stretchLastSection         WRITE setStretchLastSection)
  Q_PROPERTY(bool          cascadingSectionResizes  READ cascadingSectionResizes    WRITE setCascadingSectionResizes)
  Q_PROPERTY(int           defaultSectionSize       READ defaultSectionSize         WRITE setDefaultSectionSize       RESET resetDefaultSectionSize)
  Q_PROPERTY(int           minimumSectionSize       READ minimumSectionSize         WRITE setMinimumSectionSize)
  Q_PROPERTY(int           maximumSectionSize       READ maximumSectionSize         WRITE setMaximumSectionSize)
  Q_PROPERTY(Qt::Alignment defaultAlignment         READ defaultAlignment           WRITE setDefaultAlignment)
  Q_PROPERTY(bool          sortIndicatorClearable   READ isSortIndicatorClearable   WRITE setSortIndicatorClearable   NOTIFY sortIndicatorClearableChanged)
#endif

public:

  Q_INVOKABLE explicit wrapper_QHeaderView(Qt::Orientation orientation, wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractItemView(static_cast<QAbstractItemView*>
      (new QHeaderView(orientation, parent == nullptr ? nullptr : parent->get_selfptr()))) {
     qDebug() << "wrapper_QHeaderView::constructor(parent=" << (parent == nullptr ? 0 : parent->get_selfvalue()) << ")";
 }

//  Q_INVOKABLE void setModel(QAbstractItemModel *model) { get_selfptr()->setModel(model); }

  Q_INVOKABLE Qt::Orientation orientation() const { return get_selfptr()->orientation(); }
  Q_INVOKABLE int offset() const { return get_selfptr()->offset(); }
  Q_INVOKABLE int length() const { return get_selfptr()->length(); }

  // QSize sizeHint() const
  Q_INVOKABLE virtual QJSValue sizeHint() const override {
//  return wrapperFactory("QSize", new QSize(get_selfptr()->sizeHint()));
    return PointerToJsvalue(QSize, new QSize(get_selfptr()->sizeHint()));
  }

  Q_INVOKABLE void setVisible(bool v) { get_selfptr()->setVisible(v); }

  Q_INVOKABLE int sectionSizeHint(int logicalIndex) const { return get_selfptr()->sectionSizeHint(logicalIndex); }

//!!!
#if 0
 int visualIndexAt(int position) const;
 int logicalIndexAt(int position) const;

 inline int logicalIndexAt(int x, int y) const;
 inline int logicalIndexAt(const QPoint &pos) const;

 int sectionSize(int logicalIndex) const;
 int sectionPosition(int logicalIndex) const;
 int sectionViewportPosition(int logicalIndex) const;

 void moveSection(int from, int to);
 void swapSections(int first, int second);
 void resizeSection(int logicalIndex, int size);
 void resizeSections(QHeaderView::ResizeMode mode);

 bool isSectionHidden(int logicalIndex) const;
 void setSectionHidden(int logicalIndex, bool hide);
 int hiddenSectionCount() const;

 inline void hideSection(int logicalIndex);
 inline void showSection(int logicalIndex);

 int count() const;
 int visualIndex(int logicalIndex) const;
 int logicalIndex(int visualIndex) const;
#endif

 void setSectionsMovable(bool movable) { get_selfptr()->setSectionsMovable(movable); }
 bool sectionsMovable() const { return get_selfptr()->sectionsMovable(); }
 void setFirstSectionMovable(bool movable) { get_selfptr()->setFirstSectionMovable(movable); }
 bool isFirstSectionMovable() const { return get_selfptr()->isFirstSectionMovable(); }

//!!!
#if 0
 void setSectionsClickable(bool clickable);
 bool sectionsClickable() const;

 void setHighlightSections(bool highlight);
 bool highlightSections() const;

 ResizeMode sectionResizeMode(int logicalIndex) const;
 void setSectionResizeMode(ResizeMode mode);
 void setSectionResizeMode(int logicalIndex, ResizeMode mode);

 void setResizeContentsPrecision(int precision);
 int  resizeContentsPrecision() const;

 int stretchSectionCount() const;

 void setSortIndicatorShown(bool show);
 bool isSortIndicatorShown() const;

 void setSortIndicator(int logicalIndex, Qt::SortOrder order);
 int sortIndicatorSection() const;
 Qt::SortOrder sortIndicatorOrder() const;

 void setSortIndicatorClearable(bool clearable);
 bool isSortIndicatorClearable() const;

 bool stretchLastSection() const;
 void setStretchLastSection(bool stretch);

 bool cascadingSectionResizes() const;
 void setCascadingSectionResizes(bool enable);

 int defaultSectionSize() const;
 void setDefaultSectionSize(int size);
 void resetDefaultSectionSize();

 int minimumSectionSize() const;
 void setMinimumSectionSize(int size);
 int maximumSectionSize() const;
 void setMaximumSectionSize(int size);

 Qt::Alignment defaultAlignment() const;
 void setDefaultAlignment(Qt::Alignment alignment);

 void doItemsLayout();
 bool sectionsMoved() const;
 bool sectionsHidden() const;

#ifndef QT_NO_DATASTREAM
 QByteArray saveState() const;
 bool restoreState(const QByteArray &state);
#endif

#endif

  Q_INVOKABLE void reset() { get_selfptr()->reset(); }

public Q_SLOTS:
  Q_INVOKABLE void setOffset(int offset) { get_selfptr()->setOffset(offset); }
  Q_INVOKABLE void setOffsetToSectionPosition(int visualIndex) { get_selfptr()->setOffsetToSectionPosition(visualIndex); }
  Q_INVOKABLE void setOffsetToLastSection() { get_selfptr()->setOffsetToLastSection(); }
  Q_INVOKABLE void headerDataChanged(Qt::Orientation orientation, int logicalFirst, int logicalLast) { get_selfptr()->headerDataChanged(orientation, logicalFirst, logicalLast); }

Q_SIGNALS:

    void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex);
    void sectionResized(int logicalIndex, int oldSize, int newSize);
    void sectionPressed(int logicalIndex);
    void sectionClicked(int logicalIndex);
    void sectionEntered(int logicalIndex);
    void sectionDoubleClicked(int logicalIndex);
    void sectionCountChanged(int oldCount, int newCount);
    void sectionHandleDoubleClicked(int logicalIndex);
    void geometriesChanged();
    void sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void sortIndicatorClearableChanged(bool clearable);

public:

  // Конструктор из объекта
  wrapper_QHeaderView(void *self) : wrapper_QAbstractItemView(self) {
    qDebug() << "wrapper_QHeaderView::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QHeaderView* get_selfptr() const {
    return static_cast<const QHeaderView*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QHeaderView* get_selfptr() {
    return static_cast<QHeaderView*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QHeaderView() override {
      qDebug() << "wrapper_QHeaderView::destructor(self=" << get_selfvalue() << ")";
  }
};

Q_DECLARE_METATYPE(wrapper_QHeaderView)

#endif // WRAPPER_QHEADERVIEW_H
