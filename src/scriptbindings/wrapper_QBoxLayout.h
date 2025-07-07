#ifndef WRAPPER_QBOXLAYOUT_H
#define WRAPPER_QBOXLAYOUT_H

#include <QtCore/QObject>
#include <QtWidgets/QBoxLayout>
#include "wrapper_QLayout.h"
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QBoxLayout : public wrapper_QLayout {

  Q_OBJECT
  // Из файла qboxlayout.h

public:
  enum Direction {
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop,
    Down = TopToBottom,
    Up = BottomToTop
  };

  Q_INVOKABLE explicit wrapper_QBoxLayout(Direction direction, wrapper_QWidget *parent = nullptr) :
    wrapper_QLayout(new QBoxLayout((QBoxLayout::Direction)(int)direction, parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QBoxLayout::constructor(direction, parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

#if 0
    Direction direction() const;
    void setDirection(Direction);

    void addSpacing(int size);
    void addStretch(int stretch = 0);
    void addSpacerItem(QSpacerItem *spacerItem);
#endif

  // void addWidget(QWidget *, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
  Q_INVOKABLE void addWidget(const QJSValue &widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment()) {
    QWidget *w = jsvalueToPointer(QWidget, widget);
    get_selfptr()->addWidget(w, stretch, alignment);
  }

  // addLayout(QLayout *layout, int stretch = 0);
  Q_INVOKABLE void addLayout(wrapper_QLayout *layout, int stretch = 0) {
    get_selfptr()->addLayout(layout->get_selfptr(), stretch);
  }

#if 0
    void addStrut(int);
    void addItem(QLayoutItem *) override;

    void insertSpacing(int index, int size);
    void insertStretch(int index, int stretch = 0);
    void insertSpacerItem(int index, QSpacerItem *spacerItem);
    void insertWidget(int index, QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    void insertLayout(int index, QLayout *layout, int stretch = 0);
    void insertItem(int index, QLayoutItem *);

    int spacing() const override;
    void setSpacing(int spacing) override;

    bool setStretchFactor(QWidget *w, int stretch);
    bool setStretchFactor(QLayout *l, int stretch);
    void setStretch(int index, int stretch);
    int stretch(int index) const;

    QSize sizeHint() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;

    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int minimumHeightForWidth(int) const override;

    Qt::Orientations expandingDirections() const override;
    void invalidate() override;
    QLayoutItem *itemAt(int) const override;
    QLayoutItem *takeAt(int) override;
    int count() const override;
    void setGeometry(const QRect&) override;

#endif

public:

  // Конструктор из объекта
  explicit wrapper_QBoxLayout(QBoxLayout* self) :
    wrapper_QLayout(self) {
    qDebug() << "wrapper_QBoxLayout::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QBoxLayout() override {
    delete static_cast<QBoxLayout*>(wrapper_QLayout::get_selfptr());
  }

  // Получение константного указателя на объект
  const QBoxLayout* get_selfptr() const {
    if (wrapper_QLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<const QBoxLayout*>(wrapper_QLayout::get_selfptr());
  }

  // Получение указателя на объект
  QBoxLayout* get_selfptr() {
    if (wrapper_QLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<QBoxLayout*>(wrapper_QLayout::get_selfptr());
  }
};

class /* Q_WIDGETS_EXPORT */ wrapper_QHBoxLayout : public wrapper_QBoxLayout {

  Q_OBJECT

  // Из файла qboxlayout.h

public:

  Q_INVOKABLE wrapper_QHBoxLayout() :
    wrapper_QBoxLayout(new QHBoxLayout()) {}
  Q_INVOKABLE explicit wrapper_QHBoxLayout(wrapper_QWidget *parent) :
    wrapper_QBoxLayout(new QHBoxLayout(parent == nullptr ? nullptr : parent->get_selfptr())) {}

public:

  // Конструктор из объекта
  explicit wrapper_QHBoxLayout(QHBoxLayout* self) :
    wrapper_QBoxLayout(self) {
    qDebug() << "wrapper_QHBoxLayout::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QHBoxLayout() override {
    delete static_cast<QHBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }

  // Получение константного указателя на объект
  const QHBoxLayout* get_selfptr() const {
    if (wrapper_QBoxLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QHBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<const QHBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }

  // Получение указателя на объект
  QHBoxLayout* get_selfptr() {
    if (wrapper_QBoxLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QHBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<QHBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }
};

class /* Q_WIDGETS_EXPORT */ wrapper_QVBoxLayout : public wrapper_QBoxLayout {

  Q_OBJECT

  // Из файла qboxlayout.h

public:

  Q_INVOKABLE wrapper_QVBoxLayout() :
    wrapper_QBoxLayout(new QVBoxLayout()) {}
  Q_INVOKABLE explicit wrapper_QVBoxLayout(wrapper_QWidget *parent) :
    wrapper_QBoxLayout(new QVBoxLayout(parent == nullptr ? nullptr : parent->get_selfptr())) {}

public:

  // Конструктор из объекта
  explicit wrapper_QVBoxLayout(QVBoxLayout* self) :
    wrapper_QBoxLayout(self) {
    qDebug() << "wrapper_QVBoxLayout::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QVBoxLayout() override {
    delete static_cast<QVBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }

  // Получение константного указателя на объект
  const QVBoxLayout* get_selfptr() const {
    if (wrapper_QBoxLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QVBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<const QVBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }

  // Получение указателя на объект
  QVBoxLayout* get_selfptr() {
    if (wrapper_QBoxLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QVBoxLayout::get_selfptr - got nullptr";
    }
    return static_cast<QVBoxLayout*>(wrapper_QBoxLayout::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QBoxLayout)

#endif // WRAPPER_QBOXLAYOUT_H
