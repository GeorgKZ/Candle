#ifndef WRAPPER_QRECT_H
#define WRAPPER_QRECT_H

#include <QtCore/QObject>
#include <QtCore/QRect>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QRect : public wrapper_common {

    Q_OBJECT

public:

    // Из файла QRect.h

    // QRect()
    Q_INVOKABLE wrapper_QRect() :
        wrapper_common(new QRect()) {
    }

    // QRect(const QPoint &topleft, const QPoint &bottomright);
    // QRect(const QPoint &topleft, const QSize &size);

    // QRect(int left, int top, int width, int height);
    wrapper_QRect(int left, int top, int width, int height) :
        wrapper_common(new QRect(left, top, width, height)) {
    }

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

    // int left() const;
    // int top() const;
    // int right() const;
    // int bottom() const;
    // QRect normalized() const;

    // int x() const;
    // int y() const;
    // void setLeft(int pos);
    // void setTop(int pos);
    // void setRight(int pos);
    // void setBottom(int pos);
    // void setX(int x);
    // void setY(int y);

    // void setTopLeft(const QPoint &p);
    // void setBottomRight(const QPoint &p);
    // void setTopRight(const QPoint &p);
    // void setBottomLeft(const QPoint &p);

    // QPoint topLeft() const;
    // QPoint bottomRight() const;
    // QPoint topRight() const;
    // QPoint bottomLeft() const;
    // QPoint center() const;

    // void moveLeft(int pos);
    // void moveTop(int pos);
    // void moveRight(int pos);
    // void moveBottom(int pos);
    // void moveTopLeft(const QPoint &p);
    // void moveBottomRight(const QPoint &p);
    // void moveTopRight(const QPoint &p);
    // void moveBottomLeft(const QPoint &p);
    // void moveCenter(const QPoint &p);

    // void translate(int dx, int dy);
    // void translate(const QPoint &p);
    // QRect translated(int dx, int dy) const;
    // QRect translated(const QPoint &p) const;
    // QRect transposed() const;

    // void moveTo(int x, int t);
    // void moveTo(const QPoint &p);

    // void setRect(int x, int y, int w, int h);
    // void getRect(int *x, int *y, int *w, int *h) const;

    // void setCoords(int x1, int y1, int x2, int y2);
    // void getCoords(int *x1, int *y1, int *x2, int *y2) const;

    // void adjust(int x1, int y1, int x2, int y2);
    // QRect adjusted(int x1, int y1, int x2, int y2) const;

    // QSize size() const;
    // int width() const;
    // int height() const;
    // void setWidth(int w);
    // void setHeight(int h);
    // void setSize(const QSize &s);

    // QRect operator|(const QRect &r) const;
    // QRect operator&(const QRect &r) const;
    // QRect &operator|=(const QRect &r);
    // QRect &operator&=(const QRect &r);

    // bool contains(const QRect &r, bool proper = false) const;
    // bool contains(const QPoint &p, bool proper = false) const;
    // bool contains(int x, int y) const;
    // bool contains(int x, int y, bool proper) const;
    // QRect united(const QRect &other) const;
    // QRect intersected(const QRect &other) const;
    // bool intersects(const QRect &r) const;

    // QRect marginsAdded(const QMargins &margins) const;
    // QRect marginsRemoved(const QMargins &margins) const;
    // QRect &operator+=(const QMargins &margins);
    // QRect &operator-=(const QMargins &margins);

    // static QRect span(const QPoint &p1, const QPoint &p2);



#if defined(Q_OS_DARWIN) || defined(Q_QDOC)
    // CGRect toCGRect() const;
#endif

    // QRectF toRectF() const


public:

  // Конструктор из объекта
  wrapper_QRect(QRect *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QRect::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QRect* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QRect::get_selfptr - got nullptr";
    }
    return static_cast<const QRect*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QRect* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QRect::get_selfptr - got nullptr";
    }
    return static_cast<QRect*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QRect() override {
    qDebug() << "wrapper_QRect::destructor";
//    delete static_cast<QRect*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QRect)

#endif // WRAPPER_QRECT_H
