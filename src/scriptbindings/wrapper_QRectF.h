#ifndef WRAPPER_QRECTF_H
#define WRAPPER_QRECTF_H

#include <QtCore/QObject>
#include <QtCore/QRectF>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QRectF : public wrapper_common {

    Q_OBJECT

public:

    // Из файла QRect.h

    // QRectF()
    Q_INVOKABLE wrapper_QRectF() :
        wrapper_common(new QRectF()) {
    }

    // QRectF(const QPointF &topleft, const QSizeF &size);

    // QRectF(const QPointF &topleft, const QPointF &bottomRight);

    // QRectF(qreal left, qreal top, qreal width, qreal height);
    wrapper_QRectF(qreal left, qreal top, qreal width, qreal height) :
        wrapper_common(new QRectF(left, top, width, height)) {
    }

    // QRectF(const QRect &rect);

    // bool isNull() const;
    Q_INVOKABLE bool isNull() const
    {
        return get_selfptr()->isNull();
    }

    // bool isEmpty() const;
    Q_INVOKABLE bool isEmpty() const
    {
        return get_selfptr()->isEmpty();
    }

    // bool isValid() const;
    Q_INVOKABLE bool isValid() const
    {
        return get_selfptr()->isValid();
    }

    // QRectF normalized() const;

    // qreal left() const
    // qreal top() const
    // qreal right() const
    // qreal bottom() const

    // qreal x() const;
    // qreal y() const;
    // void setLeft(qreal pos);
    // void setTop(qreal pos);
    // void setRight(qreal pos);
    // void setBottom(qreal pos);
    // void setX(qreal pos)
    // void setY(qreal pos)

    // QPointF topLeft() const
    // QPointF bottomRight() const
    // QPointF topRight() const
    // QPointF bottomLeft() const
    // QPointF center() const;

    // void setTopLeft(const QPointF &p);
    // void setBottomRight(const QPointF &p);
    // void setTopRight(const QPointF &p);
    // void setBottomLeft(const QPointF &p);

    // void moveLeft(qreal pos);
    // void moveTop(qreal pos);
    // void moveRight(qreal pos);
    // void moveBottom(qreal pos);
    // void moveTopLeft(const QPointF &p);
    // void moveBottomRight(const QPointF &p);
    // void moveTopRight(const QPointF &p);
    // void moveBottomLeft(const QPointF &p);
    // void moveCenter(const QPointF &p);

    // void translate(qreal dx, qreal dy);
    // void translate(const QPointF &p);

    // QRectF translated(qreal dx, qreal dy) const;
    // QRectF translated(const QPointF &p) const;

    // QRectF transposed() const;

    // void moveTo(qreal x, qreal y);
    // void moveTo(const QPointF &p);

    // void setRect(qreal x, qreal y, qreal w, qreal h);
    // void getRect(qreal *x, qreal *y, qreal *w, qreal *h) const;

    // void setCoords(qreal x1, qreal y1, qreal x2, qreal y2);
    // void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;

    // void adjust(qreal x1, qreal y1, qreal x2, qreal y2);
    // QRectF adjusted(qreal x1, qreal y1, qreal x2, qreal y2) const;

    // QSizeF size() const;
    // qreal width() const;
    // qreal height() const;
    // void setWidth(qreal w);
    // void setHeight(qreal h);
    // void setSize(const QSizeF &s);

    // QRectF operator|(const QRectF &r) const;
    // QRectF operator&(const QRectF &r) const;
    // QRectF &operator|=(const QRectF &r);
    // QRectF &operator&=(const QRectF &r);

    // bool contains(const QRectF &r) const;
    // bool contains(const QPointF &p) const;
    // bool contains(qreal x, qreal y) const;
    // QRectF united(const QRectF &other) const;
    // QRectF intersected(const QRectF &other) const;
    // bool intersects(const QRectF &r) const;

    // QRectF marginsAdded(const QMarginsF &margins) const;
    // QRectF marginsRemoved(const QMarginsF &margins) const;
    // QRectF &operator+=(const QMarginsF &margins);
    // QRectF &operator-=(const QMarginsF &margins);

    // QRect toRect() const;
    // QRect toAlignedRect() const;

#if defined(Q_OS_DARWIN) || defined(Q_QDOC)
    // static QRectF fromCGRect(CGRect rect);
    // CGRect toCGRect() const;
#endif

#if defined(Q_OS_WASM) || defined(Q_QDOC)
    // static QRectF fromDOMRect(emscripten::val domRect);
    // emscripten::val toDOMRect() const;
#endif

public:

  // Конструктор из объекта
  wrapper_QRectF(QRectF *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QRectF::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QRectF* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QRectF::get_selfptr - got nullptr";
    }
    return static_cast<const QRectF*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QRectF* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QRectF::get_selfptr - got nullptr";
    }
    return static_cast<QRectF*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QRectF() {
    qDebug() << "wrapper_QRectF::destructor";
//    delete static_cast<QRectF*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QRectF);

#endif // WRAPPER_QRectF_H
