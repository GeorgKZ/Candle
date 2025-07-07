#ifndef WRAPPER_QSIZE_H
#define WRAPPER_QSIZE_H

#include <QtCore/QObject>
#include <QtCore/QSize>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QSize : public wrapper_common {

  Q_OBJECT

public:

  // Из файла qsize.h

  // Конструктор по умолчанию
  Q_INVOKABLE wrapper_QSize() :
    wrapper_common(new QSize()) { }

  Q_INVOKABLE wrapper_QSize(int w, int h) :
    wrapper_common(new QSize(w, h)) {}

  Q_INVOKABLE bool isNull() const { return get_selfptr()->isNull(); }
  Q_INVOKABLE bool isEmpty() const { return get_selfptr()->isEmpty(); }
  Q_INVOKABLE bool isValid() const { return get_selfptr()->isValid(); }

  Q_INVOKABLE int width() const { return get_selfptr()->width(); }
  Q_INVOKABLE int height() const { return get_selfptr()->height(); }
  Q_INVOKABLE void setWidth(int w) { get_selfptr()->setWidth(w); }
  Q_INVOKABLE void setHeight(int h) { get_selfptr()->setHeight(h); }
  Q_INVOKABLE void transpose() { get_selfptr()->transpose(); }
  // QSize transposed() const
  Q_INVOKABLE  wrapper_QSize *transposed() const { QSize *size = new QSize(get_selfptr()->transposed()); return new wrapper_QSize(size); }
//!!! Сделать!
#if 0
  Q_INVOKABLE void scale(int w, int h, Qt::AspectRatioMode mode) noexcept;
  Q_INVOKABLE void scale(const QSize &s, Qt::AspectRatioMode mode) noexcept;
  Q_INVOKABLE QSize scaled(int w, int h, Qt::AspectRatioMode mode) const noexcept;
  Q_INVOKABLE QSize scaled(const QSize &s, Qt::AspectRatioMode mode) const noexcept;

  Q_INVOKABLE QSize expandedTo(const QSize &) const noexcept;
  Q_INVOKABLE QSize boundedTo(const QSize &) const noexcept;

  Q_INVOKABLE QSize grownBy(QMargins m) const noexcept
  Q_INVOKABLE QSize shrunkBy(QMargins m) const noexcept

  Q_INVOKABLE int &rwidth() noexcept;
  Q_INVOKABLE int &rheight() noexcept;

  Q_INVOKABLE QSize &operator+=(const QSize &) noexcept;
  Q_INVOKABLE QSize &operator-=(const QSize &) noexcept;
  Q_INVOKABLE QSize &operator*=(qreal c) noexcept;
  Q_INVOKABLE QSize &operator/=(qreal c);

  friend inline constexpr bool operator==(const QSize &s1, const QSize &s2) noexcept
  friend inline constexpr bool operator!=(const QSize &s1, const QSize &s2) noexcept
  friend inline constexpr QSize operator+(const QSize &s1, const QSize &s2) noexcept
  friend inline constexpr QSize operator-(const QSize &s1, const QSize &s2) noexcept
  friend inline constexpr QSize operator*(const QSize &s, qreal c) noexcept
  friend inline constexpr QSize operator*(qreal c, const QSize &s) noexcept
  friend inline QSize operator/(const QSize &s, qreal c)
  friend inline constexpr size_t qHash(const QSize &, size_t) noexcept;
#endif

#if defined(Q_OS_DARWIN) || defined(Q_QDOC)
//  Q_INVOKABLE CGSize toCGSize() const { return get_selfptr()->toCGSize(); }
#endif

  Q_INVOKABLE QSizeF toSizeF() const { return get_selfptr()->toSizeF(); }

public:

  // Конструктор из объекта
  wrapper_QSize(QSize *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QSize::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QSize* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QSize::get_selfptr - got nullptr";
    }
    return static_cast<const QSize*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QSize* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QSize::get_selfptr - got nullptr";
    }
    return static_cast<QSize*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QSize() override {
//    delete static_cast<QSize*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QSize)

#endif // WRAPPER_QSIZE_H
