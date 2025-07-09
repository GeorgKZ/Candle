#include "wrapper_QLayoutItem.h"
#include "wrapper_QLayout.h"
#include "wrapper_QWidget.h"
#include "wrapper_QSize.h"

// explicit QLayoutItem(Qt::Alignment alignment = Qt::Alignment())
wrapper_QLayoutItem::wrapper_QLayoutItem(Qt::Alignment alignment) :
  wrapper_common(nullptr /* new QLayoutItem(alignment) */) {
  Q_UNUSED(alignment);
  qDebug() << "wrapper_QLayoutItem::constructor(alignment)";
}

// virtual QSize sizeHint() const
wrapper_QSize *wrapper_QLayoutItem::sizeHint() const {
  QSize *size = new QSize(get_selfptr()->sizeHint());
  return new wrapper_QSize(size);
}

// virtual QSize minimumSize() const
wrapper_QSize *wrapper_QLayoutItem::minimumSize() const {
  QSize *size = new QSize(get_selfptr()->minimumSize());
  return new wrapper_QSize(size);
}

// virtual QSize maximumSize() const
wrapper_QSize *wrapper_QLayoutItem::maximumSize() const {
  QSize *size = new QSize(get_selfptr()->maximumSize());
  return new wrapper_QSize(size);
}

// virtual Qt::Orientations expandingDirections() const
Qt::Orientations wrapper_QLayoutItem::expandingDirections() const {
  return get_selfptr()->expandingDirections();
}

//void wrapper_QLayoutItem::setGeometry(const wrapper_QRect&) = 0;

//wrapper_QRect *wrapper_QLayoutItem::geometry() const = 0;

bool wrapper_QLayoutItem::isEmpty() const {
  return get_selfptr()->isEmpty();
}

bool wrapper_QLayoutItem::hasHeightForWidth() const {
  return get_selfptr()->hasHeightForWidth();
}

int wrapper_QLayoutItem::heightForWidth(int width) const {
  return get_selfptr()->heightForWidth(width);
}

int wrapper_QLayoutItem::minimumHeightForWidth(int width) const {
  return get_selfptr()->minimumHeightForWidth(width);
}

void wrapper_QLayoutItem::invalidate() {
  get_selfptr()->invalidate();
}

// virtual QWidget *widget() const;
QJSValue wrapper_QLayoutItem::widget() const {
  QWidget *widget = get_selfptr()->widget();
  return wrapperFactory(widget->metaObject()->className(), widget);
//  return PointerToJsvalue(QWidget, get_selfptr()->widget());
}

// virtual QLayout *layout();
QJSValue wrapper_QLayoutItem::layout() {
  QLayout* layout = get_selfptr()->layout();
  qDebug() << "wrapper_QLayoutItem::layout() ->" << layout->metaObject()->className();
  return wrapperFactory(layout->metaObject()->className(), layout);
//  return PointerToJsvalue(QLayout, get_selfptr()->layout());
}

// virtual QSpacerItem *spacerItem();
//wrapper_QSpacerItem *spacerItem();

// Qt::Alignment alignment() const
Qt::Alignment wrapper_QLayoutItem::alignment() const {
  return get_selfptr()->alignment();
}

// void setAlignment(Qt::Alignment a)
void wrapper_QLayoutItem::setAlignment(Qt::Alignment a) {
  get_selfptr()->setAlignment(a);
}

// QSizePolicy::ControlTypes controlTypes() const
// wrapper_QSizePolicy::ControlTypes wrapper_QLayoutItem::controlTypes() const;

// Конструктор из объекта
wrapper_QLayoutItem::wrapper_QLayoutItem(void* self) : wrapper_common(self) {
  qDebug() << "wrapper_QLayoutItem::constructor(self=" << get_selfvalue() << ")";
}

// Деструктор
wrapper_QLayoutItem::~wrapper_QLayoutItem() {
  qDebug() << "wrapper_QLayoutItem destructor";
}

// Получение константного указателя на объект
const QLayoutItem* wrapper_QLayoutItem::get_selfptr() const {
  return static_cast<const QLayoutItem*>(wrapper_common::get_selfptr());
}

// Получение указателя на объект
QLayoutItem* wrapper_QLayoutItem::get_selfptr() {
  return static_cast<QLayoutItem*>(wrapper_common::get_selfptr());
}

