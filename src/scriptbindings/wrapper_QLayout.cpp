#include "wrapper_QLayout.h"
#include "wrapper_QLayoutItem.h"
#include "wrapper_QWidget.h"
#include "wrapper_QSize.h"

// explicit QLayout(QWidget *parent = nullptr)
wrapper_QLayout::wrapper_QLayout(wrapper_QWidget *parent) :
  wrapper_QObject(new QObject(parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QLayout::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
}

/***********************************************************************/
/* Наследованные функции из QLayoutItem                                */
/***********************************************************************/
// virtual QSize sizeHint() const
wrapper_QSize *wrapper_QLayout::sizeHint() const {
  QSize *size = new QSize(get_selfptr()->sizeHint());
  return new wrapper_QSize(size);
}

// virtual QSize minimumSize() const
wrapper_QSize *wrapper_QLayout::minimumSize() const {
  QSize *size = new QSize(get_selfptr()->minimumSize());
  return new wrapper_QSize(size);
}

// virtual QSize maximumSize() const
wrapper_QSize *wrapper_QLayout::maximumSize() const {
  QSize *size = new QSize(get_selfptr()->maximumSize());
  return new wrapper_QSize(size);
}

// virtual Qt::Orientations expandingDirections() const
Qt::Orientations wrapper_QLayout::expandingDirections() const {
  return get_selfptr()->expandingDirections();
}

//void wrapper_QLayoutItem::setGeometry(const wrapper_QRect&) = 0;

//wrapper_QRect *wrapper_QLayoutItem::geometry() const = 0;

bool wrapper_QLayout::isEmpty() const {
  return get_selfptr()->isEmpty();
}

bool wrapper_QLayout::hasHeightForWidth() const {
  return get_selfptr()->hasHeightForWidth();
}

int wrapper_QLayout::heightForWidth(int width) const {
  return get_selfptr()->heightForWidth(width);
}

int wrapper_QLayout::minimumHeightForWidth(int width) const {
  return get_selfptr()->minimumHeightForWidth(width);
}

void wrapper_QLayout::invalidate() {
  get_selfptr()->invalidate();
}

// virtual QWidget *widget() const;
QJSValue wrapper_QLayout::widget() const {
  QWidget *widget = get_selfptr()->widget();
  qDebug() << "wrapper_QLayout::widget() ->" << widget->metaObject()->className();
  return PointerToJsvalue(widget->metaObject()->className(), widget);
}

// virtual QLayout *layout();
QJSValue wrapper_QLayout::layout() {
  qDebug() << "wrapper_QLayout::layout() ->" << get_selfptr()->layout()->metaObject()->className();
  return PointerToJsvalue(get_selfptr()->layout()->metaObject()->className(), get_selfptr()->layout());
}

// virtual QSpacerItem *spacerItem();
//wrapper_QSpacerItem *spacerItem();

// Qt::Alignment alignment() const
Qt::Alignment wrapper_QLayout::alignment() const {
  return get_selfptr()->alignment();
}

// void setAlignment(Qt::Alignment a)
void wrapper_QLayout::setAlignment(Qt::Alignment a) {
  get_selfptr()->setAlignment(a);
}

// QSizePolicy::ControlTypes controlTypes() const
// wrapper_QSizePolicy::ControlTypes wrapper_QLayoutItem::controlTypes() const;

/*************************************************************************/


// virtual int spacing() const;
int wrapper_QLayout::spacing() const {
  return get_selfptr()->spacing();
}
// virtual void setSpacing(int);
void wrapper_QLayout::setSpacing(int spacing) {
  get_selfptr()->setSpacing(spacing);
}

// void setContentsMargins(int left, int top, int right, int bottom);
// void setContentsMargins(const QMargins &margins);
// void unsetContentsMargins();
// void getContentsMargins(int *left, int *top, int *right, int *bottom) const;
// QMargins contentsMargins() const;
// wrapper_QRect *contentsRect() const;

// bool setAlignment(wrapper_QWidget *w, Qt::Alignment alignment);
// bool setAlignmentwrapper_(QLayout *l, Qt::Alignment alignment);
//    using QLayoutItem::setAlignment;

// void setSizeConstraint(SizeConstraint);
void wrapper_QLayout::setSizeConstraint(wrapper_QLayout::SizeConstraint size) {
  get_selfptr()->setSizeConstraint((QLayout::SizeConstraint)(int)size);
}
// SizeConstraint sizeConstraint() const;
wrapper_QLayout::SizeConstraint wrapper_QLayout::sizeConstraint() const {
  return (wrapper_QLayout::SizeConstraint)(int)get_selfptr()->sizeConstraint();
}

// void setMenuBar(QWidget *w);
// wrapper_QWidget *menuBar() const;

// wrapper_QWidget *parentWidget() const;

// void invalidate() override;
// wrapper_QRect geometry() const override;

bool wrapper_QLayout::activate() {
  return get_selfptr()->activate();
}

void wrapper_QLayout::update() {
  get_selfptr()->update();
}

void wrapper_QLayout::addWidget(const QJSValue &widget) {
  qDebug() << "wrapper_QLayout::addWidget(QWidget)";

  QWidget *w = jsvalueToPointer(QWidget, widget);
  get_selfptr()->addWidget(w);
}

//  Q_INVOKABLE virtual void addItem(QLayoutItem *)

//  Q_INVOKABLEvoid removeWidget(QWidget *w);
//  Q_INVOKABLEvoid removeItem(QLayoutItem *);
#if 0
    Qt::Orientations expandingDirections() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    virtual void setGeometry(const QRect&) override;
#endif

// virtual QLayoutItem *itemAt(int index) const
QJSValue wrapper_QLayout::itemAt(int index) const {
  return PointerToJsvalueMacro(QLayoutItem, get_selfptr()->itemAt(index));
} 

// virtual QLayoutItem *takeAt(int index)
QJSValue wrapper_QLayout::takeAt(int index) {
  return PointerToJsvalueMacro(QLayoutItem, get_selfptr()->takeAt(index));
}

#if 0
    virtual int indexOf(const wrapper_QWidget *) const;
    virtual int indexOf(const wrapper_QLayoutItem *) const;
#endif

// virtual int count() const
int wrapper_QLayout::count() const {
  return get_selfptr()->count();
}

#if 0
    bool isEmpty() const override;
    QSizePolicy::ControlTypes controlTypes() const override;

    virtual QLayoutItem *replaceWidget(QWidget *from, QWidget *to, Qt::FindChildOptions options = Qt::FindChildrenRecursively);

    int totalMinimumHeightForWidth(int w) const;
    int totalHeightForWidth(int w) const;
    QSize totalMinimumSize() const;
    QSize totalMaximumSize() const;
    QSize totalSizeHint() const;
#endif

// QLayout *layout() override; - уже есть в хелпере

// void setEnabled(bool);
void wrapper_QLayout::setEnabled(bool enabled) {
  get_selfptr()->setEnabled(enabled);
}

// bool isEnabled() const;
bool wrapper_QLayout::isEnabled() const {
  return get_selfptr()->isEnabled();
}

// static QSize closestAcceptableSize(const wrapper_QWidget *w, const wrapper_QSize &s);
//  Q_INVOKABLE static QSize closestAcceptableSize(const wrapper_QWidget *w, const wrapper_QSize &s);
