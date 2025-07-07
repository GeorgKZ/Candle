#ifndef WRAPPER_QPOINT_H
#define WRAPPER_QPOINT_H

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QPoint : public wrapper_common {

  Q_OBJECT

public:

  // Из файла QPoint.h

  Q_INVOKABLE wrapper_QPoint() :
    wrapper_common(new QPoint()) {
    qDebug() << "wrapper_QPoint::constructor()";
  }

  // QPoint(int xpos, int ypos);
  Q_INVOKABLE wrapper_QPoint(int xpos, int ypos) :
    wrapper_common(new QPoint(xpos, ypos)) {
    qDebug() << "wrapper_QPoint::constructor(" << xpos << "," << ypos << ")";
  }

  // bool isNull() const;

  // int x() const;
  Q_INVOKABLE int x() const {
    return get_selfptr()->x();
  }

  // int y() const;
  Q_INVOKABLE int y() const {
    return get_selfptr()->y();
  }

  // void setX(int x);

  // void setY(int y);

  // int manhattanLength() const;

  // QPoint transposed() const

  // int &rx();

  // int &ry();

  // QPoint &operator+=(const QPoint &p);

  // QPoint &operator-=(const QPoint &p);

  // QPoint &operator*=(float factor);

  // QPoint &operator*=(double factor);

  // QPoint &operator*=(int factor);

  // QPoint &operator/=(qreal divisor);

  // static int dotProduct(const QPoint &p1, const QPoint &p2)
  static int dotProduct(const QJSValue &p1, const QJSValue &p2) {
    QPoint P1 = *jsvalueToPointer(QPoint, p1);
    QPoint P2 = *jsvalueToPointer(QPoint, p2);
    return QPoint::dotProduct(P1, P2);
  }

#if 0
  friend bool operator==(const QPoint &p1, const QPoint &p2)
  friend bool operator!=(const QPoint &p1, const QPoint &p2)
  friend QPoint operator+(const QPoint &p1, const QPoint &p2)
  friend QPoint operator-(const QPoint &p1, const QPoint &p2)
  friend QPoint operator*(const QPoint &p, float factor)
  friend QPoint operator*(const QPoint &p, double factor)
  friend QPoint operator*(const QPoint &p, int factor)
  friend QPoint operator*(float factor, const QPoint &p)
  friend QPoint operator*(double factor, const QPoint &p)
  friend QPoint operator*(int factor, const QPoint &p)
  friend QPoint operator+(const QPoint &p)
  friend QPoint operator-(const QPoint &p)
  friend QPoint operator/(const QPoint &p, qreal c)
#endif

#if defined(Q_OS_DARWIN) || defined(Q_QDOC)
    CGPoint toCGPoint() const;
#endif

public:

  // Конструктор из объекта
  wrapper_QPoint(QPoint *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QPoint::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QPoint* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QPoint::get_selfptr - got nullptr";
    }
    return static_cast<const QPoint*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QPoint* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPoint::get_selfptr - got nullptr";
    }
    return static_cast<QPoint*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QPoint() override {
    qDebug() << "wrapper_QPoint::destructor";
//    delete static_cast<QPoint*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QPoint)

#endif // WRAPPER_QPOINT_H
