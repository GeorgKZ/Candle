#ifndef WRAPPER_QPOINTF_H
#define WRAPPER_QPOINTF_H

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QPointF : public wrapper_common {

  Q_OBJECT

public:

  // Из файла qpoint.h

  Q_INVOKABLE wrapper_QPointF() :
    wrapper_common(new QPointF()) {
    qDebug() << "wrapper_QPointF::constructor()";
  }

  // constexpr QPointF(const QPoint &p) noexcept;

  // QPoint(int xpos, int ypos);
  Q_INVOKABLE wrapper_QPointF(qreal xpos, qreal ypos) :
    wrapper_common(new QPointF(xpos, ypos)) {
    qDebug() << "wrapper_QPointF::constructor(" << xpos << "," << ypos << ")";
  }

  // qreal manhattanLength() const;

  // bool isNull() const;

  // qreal x() const;

  // qreal y() const;

  // void setX(qreal x);

  // void setY(qreal y);

  // QPointF transposed() const

  // qreal &rx();

  // qreal &ry();

  // QPointF &operator+=(const QPointF &p);

  // QPointF &operator-=(const QPointF &p);

  // QPointF &operator*=(qreal c);

  // QPointF &operator/=(qreal c);

  // static qreal dotProduct(const QPointF &p1, const QPointF &p2);
  static qreal dotProduct(const QJSValue &p1, const QJSValue &p2) {
    QPointF P1 = *jsvalueToPointer(QPointF, p1);
    QPointF P2 = *jsvalueToPointer(QPointF, p2);
    return QPointF::dotProduct(P1, P2);
  }

  // QPoint toPoint() const;

#if defined(Q_OS_DARWIN) || defined(Q_QDOC)
  //  static wrapper_QPointF fromCGPoint(CGPoint point);
  //  CGPoint toCGPoint() const;
#endif

public:

  // Конструктор из объекта
  wrapper_QPointF(QPointF *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QPointF::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QPointF* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QPointF::get_selfptr - got nullptr";
    }
    return static_cast<const QPointF*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QPointF* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPointF::get_selfptr - got nullptr";
    }
    return static_cast<QPointF*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QPointF() {
    qDebug() << "wrapper_QPointF::destructor";
//    delete static_cast<QPoint*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QPointF);

#endif // WRAPPER_QPOINTF_H
