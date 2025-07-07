#ifndef WRAPPER_QLAYOUTITEM_H
#define WRAPPER_QLAYOUTITEM_H

#include <QtCore/QObject>
#include <QtWidgets/QLayoutItem>
#include "wrapper_common.h"

class wrapper_QWidget;
class wrapper_QSize;
class wrapper_QSpacerItem;
class wrapper_QLayout;
class wrapper_QRect;

// QLayoutItem - абстрактный класс
class WRAPPER_DLL_EXPORT wrapper_QLayoutItem : public wrapper_common {

  Q_OBJECT
    // Из файла qlayoutitem.h

public:

  // explicit QLayoutItem(Qt::Alignment alignment = Qt::Alignment())
  Q_INVOKABLE explicit wrapper_QLayoutItem(Qt::Alignment alignment = Qt::Alignment());

  // Прокси-функции класса wrapper_QLayoutItem
  #include "funcs_QLayoutItem.h"

public:

  // Конструктор из объекта
  explicit wrapper_QLayoutItem(QLayoutItem* self);

  // Деструктор
  virtual ~wrapper_QLayoutItem() override;

  // Получение константного указателя на объект
  const QLayoutItem* get_selfptr() const;

  // Получение указателя на объект
  QLayoutItem* get_selfptr();
};

Q_DECLARE_METATYPE(wrapper_QLayoutItem)
Q_DECLARE_METATYPE(wrapper_QLayoutItem*)

#endif // WRAPPER_QLAYOUTITEM_H
