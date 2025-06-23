#ifndef WRAPPER_QLAYOUT_H
#define WRAPPER_QLAYOUT_H

#include <QtCore/QObject>
#include <QtWidgets/QLayout>
#include "wrapper_QObject.h"

class wrapper_QMargins;
class wrapper_QRect;
class wrapper_QSize;
class wrapper_QWidget;
class wrapper_QLayoutItem;

// QLayout - абстрактный класс
class WRAPPER_DLL_EXPORT wrapper_QLayout : public wrapper_QObject {

  Q_OBJECT

  Q_PROPERTY(int spacing                       READ spacing         WRITE setSpacing)
//Q_PROPERTY(wrapper_QMargins *contentsMargins READ contentsMargins WRITE setContentsMargins  RESET unsetContentsMargins)
  Q_PROPERTY(SizeConstraint sizeConstraint     READ sizeConstraint  WRITE setSizeConstraint)

public:

  enum SizeConstraint {
      SetDefaultConstraint,
      SetNoConstraint,
      SetMinimumSize,
      SetFixedSize,
      SetMaximumSize,
      SetMinAndMaxSize
  };
//  Q_ENUM(SizeConstraint)

  // explicit QLayout(QWidget *parent = nullptr)
  Q_INVOKABLE explicit wrapper_QLayout(wrapper_QWidget *parent = nullptr);

  // Прокси-функции класса wrapper_QLayoutItem
  #include "funcs_QLayoutItem.h"

  // virtual int spacing() const;
  Q_INVOKABLE virtual int spacing() const;
  // virtual void setSpacing(int);
  Q_INVOKABLE virtual void setSpacing(int spacing);

//  Q_INVOKABLE void setContentsMargins(int left, int top, int right, int bottom);
//  Q_INVOKABLE void setContentsMargins(const wrapper_QMargins &margins);
//  Q_INVOKABLE void unsetContentsMargins();
//  Q_INVOKABLE void getContentsMargins(int *left, int *top, int *right, int *bottom) const;
//  Q_INVOKABLE wrapper_QMargins *contentsMargins() const;
//  Q_INVOKABLE wrapper_QRect *contentsRect() const;

//  Q_INVOKABLE bool setAlignment(wrapper_QWidget *w, Qt::Alignment alignment);
//  Q_INVOKABLE bool setAlignment(wrapper_QLayout *l, Qt::Alignment alignment);
//    using QLayoutItem::setAlignment;

  Q_INVOKABLE void setSizeConstraint(SizeConstraint size);
  Q_INVOKABLE SizeConstraint sizeConstraint() const;
//  Q_INVOKABLE void setMenuBar(wrapper_QWidget *w);
//  Q_INVOKABLE wrapper_QWidget *menuBar() const;

//  Q_INVOKABLE wrapper_QWidget *parentWidget() const;

//  Q_INVOKABLE void invalidate() override;
//  Q_INVOKABLE wrapper_QRect *geometry() const override;
  Q_INVOKABLE bool activate();
  Q_INVOKABLE void update();

  // void addWidget(QWidget *w)
  Q_INVOKABLE void addWidget(const QJSValue &widget);

//  Q_INVOKABLE virtual void addItem(wrapper_QLayoutItem *);

//  Q_INVOKABLE void removeWidget(wrapper_QWidget *w);
//  Q_INVOKABLE void removeItem(wrapper_QLayoutItem *);

//  Q_INVOKABLE Qt::Orientations expandingDirections() const override;
//  Q_INVOKABLE wrapper_QSize *minimumSize() const override;
//  Q_INVOKABLE wrapper_QSize *maximumSize() const override;
//  Q_INVOKABLE virtual void setGeometry(const wrapper_QRect&) override;

  // virtual QLayoutItem *itemAt(int index) const
  Q_INVOKABLE virtual QJSValue itemAt(int index) const;

  // virtual QLayoutItem *takeAt(int index)
  Q_INVOKABLE virtual QJSValue takeAt(int index);

  // virtual int indexOf(const QWidget *) const
//  Q_INVOKABLE virtual int indexOf(const wrapper_QWidget *) const;

  // virtual int indexOf(const QLayoutItem *) const
//  Q_INVOKABLE virtual int indexOf(const wrapper_QLayoutItem *) const;

  // virtual int count() const
  Q_INVOKABLE virtual int count() const;

  // bool isEmpty() const override;
//  Q_INVOKABLE bool isEmpty() const override;

  // QSizePolicy::ControlTypes controlTypes() const override
  // QSizePolicy::ControlTypes controlTypes() const override;

//  Q_INVOKABLE virtual wrapper_QLayoutItem *replaceWidget(wrapper_QWidget *from, wrapper_QWidget *to, Qt::FindChildOptions options = Qt::FindChildrenRecursively);

//  Q_INVOKABLE int totalMinimumHeightForWidth(int w) const;
//  Q_INVOKABLE int totalHeightForWidth(int w) const;
//  Q_INVOKABLE wrapper_QSize *totalMinimumSize() const;
//  Q_INVOKABLE wrapper_QSize *totalMaximumSize() const;
//  Q_INVOKABLE wrapper_QSize *totalSizeHint() const;

  // QLayout *layout() override - новая реализация имеющегося описания
  //Q_INVOKABLE QObject/*wrapper_QLayout*/ *layout();

  // void setEnabled(bool);
  Q_INVOKABLE void setEnabled(bool);
  // bool isEnabled() const;
  Q_INVOKABLE bool isEnabled() const;

  // static QSize closestAcceptableSize(const wrapper_QWidget *w, const wrapper_QSize &s);
//  Q_INVOKABLE static wrapper_QSize *closestAcceptableSize(const wrapper_QWidget *w, const wrapper_QSize &s);

public:

  // Конструктор из объекта
  explicit wrapper_QLayout(QLayout* self) :
    wrapper_QObject(static_cast<QObject*>(self)) {
    qDebug() << "wrapper_QLayout::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QLayout() {
    qDebug() << "wrapper_QLayout destructor";
//    delete static_cast<QLayout*>(wrapper_QObject::get_selfptr());
  }

  // Получение константного указателя на объект
  const QLayout* get_selfptr() const {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QLayout::get_selfptr - got nullptr";
    }
    return static_cast<const QLayout*>(wrapper_QObject::get_selfptr());
  }

  // Получение указателя на объект
  QLayout* get_selfptr() {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QLayout::get_selfptr - got nullptr";
    }
    return static_cast<QLayout*>(wrapper_QObject::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QLayout);
Q_DECLARE_METATYPE(wrapper_QLayout*);

#endif // WRAPPER_QLAYOUT_H
