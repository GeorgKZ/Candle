#ifndef WRAPPER_QICON_H
#define WRAPPER_QICON_H

#include <QtCore/QObject>
#include <QtGui/QIcon>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QIcon : public wrapper_common {

  Q_OBJECT

  // из файла qicon.h

public:

  Q_INVOKABLE wrapper_QIcon() :
    wrapper_common(new QIcon) {
  }
//Q_INVOKABLE wrapper_QIcon(const QPixmap &pixmap);
  Q_INVOKABLE wrapper_QIcon(const wrapper_QIcon &other) :
    wrapper_common(new QIcon(*other.get_selfptr())) {
  }
//  Q_INVOKABLE wrapper_QIcon(wrapper_QIcon &&other) : wrapper_common(new QIcon(*other.get_selfptr())) {}
  Q_INVOKABLE explicit wrapper_QIcon(const QString &fileName) :
    wrapper_common(new QIcon(fileName)) {
    qDebug() << "wrapper_QIcon::constructor(" << fileName << ")";
  }
//Q_INVOKABLE explicit wrapper_QIcon(wrapper_QIconEngine *engine);

#if 0
  Q_INVOKABLE wrapper_QIcon &operator=(const wrapper_QIcon &other);
  QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_MOVE_AND_SWAP(wrapper_QIcon)
  Q_INVOKABLE void swap(wrapper_QIcon &other);
  bool operator==(const wrapper_QIcon &) const = delete;
  bool operator!=(const wrapper_QIcon &) const = delete;

  Q_INVOKABLE operator QVariant() const;

  Q_INVOKABLE QPixmap pixmap(const QSize &size, Mode mode = Normal, State state = Off) const;
  Q_INVOKABLE QPixmap pixmap(int w, int h, Mode mode = Normal, State state = Off) const
  Q_INVOKABLE QPixmap pixmap(int extent, Mode mode = Normal, State state = Off) const
  Q_INVOKABLE QPixmap pixmap(const QSize &size, qreal devicePixelRatio, Mode mode = Normal, State state = Off) const;

  Q_INVOKABLE QSize actualSize(const QSize &size, Mode mode = Normal, State state = Off) const;
#endif
  Q_INVOKABLE QString name() const { return get_selfptr()->name(); }
#if 0
  Q_INVOKABLE void paint(QPainter *painter, const QRect &rect, Qt::Alignment alignment = Qt::AlignCenter, Mode mode = Normal, State state = Off) const;
  Q_INVOKABLE void paint(QPainter *painter, int x, int y, int w, int h, Qt::Alignment alignment = Qt::AlignCenter, Mode mode = Normal, State state = Off) const
#endif
  Q_INVOKABLE bool isNull() const { return get_selfptr()->isNull(); }
  Q_INVOKABLE bool isDetached() const { return get_selfptr()->isDetached(); }
  Q_INVOKABLE void detach() { get_selfptr()->detach(); }

  Q_INVOKABLE qint64 cacheKey() const { return get_selfptr()->cacheKey(); }
#if 0
  Q_INVOKABLE void addPixmap(const wrapper_QPixmap &pixmap, Mode mode = Normal, State state = Off);
  Q_INVOKABLE void addFile(const QString &fileName, const wrapper_QSize &size = wrapper_QSize(), Mode mode = Normal, State state = Off);

  Q_INVOKABLE QList<wrapper_QSize> availableSizes(Mode mode = Normal, State state = Off) const;
#endif
  Q_INVOKABLE void setIsMask(bool isMask) { get_selfptr()->setIsMask(isMask); }
  Q_INVOKABLE bool isMask() const { return get_selfptr()->isMask(); }
#if 0
  // static QIcon fromTheme(const QString &name);
  Q_INVOKABLE static QIcon fromTheme(const QString &name);
  // static QIcon fromTheme(const QString &name, const wrapper_QIcon &fallback);
  Q_INVOKABLE static wrapper_QIcon *fromTheme(const QString &name, const wrapper_QIcon &fallback);
#endif

  // static bool hasThemeIcon(const QString &name);
  Q_INVOKABLE static bool hasThemeIcon(const QString &name) { return QIcon::hasThemeIcon(name); }

  Q_INVOKABLE static QStringList themeSearchPaths() { return QIcon::themeSearchPaths(); }
  Q_INVOKABLE static void setThemeSearchPaths(const QStringList &searchpath) { QIcon::setThemeSearchPaths(searchpath); }

  Q_INVOKABLE static QStringList fallbackSearchPaths() { return QIcon::fallbackSearchPaths(); }
  Q_INVOKABLE static void setFallbackSearchPaths(const QStringList &paths) { QIcon::setFallbackSearchPaths(paths); }

  Q_INVOKABLE static QString themeName() { return QIcon::themeName(); }
  Q_INVOKABLE static void setThemeName(const QString &path) { QIcon::setThemeName(path); }

  Q_INVOKABLE static QString fallbackThemeName() { return QIcon::fallbackThemeName(); }
  Q_INVOKABLE static void setFallbackThemeName(const QString &name) { return QIcon::setFallbackThemeName(name); }

public:

  // Конструктор из объекта
  wrapper_QIcon(QIcon *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QIcon::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }
    
  // Деструктор
  virtual ~wrapper_QIcon() {
 //!!!   delete static_cast<QIcon*>(wrapper_common::get_selfptr());
  }

  // Получение константного указателя на объект
  const QIcon* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIcon::get_selfptr - got nullptr";
    }
    return static_cast<const QIcon*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QIcon* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIcon::get_selfptr - got nullptr";
    }
    return static_cast<QIcon*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QIcon);

#endif // WRAPPER_QICON_H
