#ifndef WRAPPER_QPAINTER_H
#define WRAPPER_QPAINTER_H

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QPaintDevice : public wrapper_common {

public:

  enum PaintDeviceMetric {
    PdmWidth = 1,
    PdmHeight,
    PdmWidthMM,
    PdmHeightMM,
    PdmNumColors,
    PdmDepth,
    PdmDpiX,
    PdmDpiY,
    PdmPhysicalDpiX,
    PdmPhysicalDpiY,
    PdmDevicePixelRatio,
    PdmDevicePixelRatioScaled
  };

  // virtual int devType() const
  Q_INVOKABLE int devType() const { return get_selfptr()->devType(); }

  // bool paintingActive() const
  Q_INVOKABLE bool paintingActive() const { return get_selfptr()->paintingActive(); }

  //!!! virtual QPaintEngine *paintEngine() const = 0;

  // int width() const
  Q_INVOKABLE int width() const { return get_selfptr()->width(); }

  // int height() const
  Q_INVOKABLE int height() const { return get_selfptr()->height(); }

  // int widthMM() const
  Q_INVOKABLE int widthMM() const { return get_selfptr()->widthMM(); }

  // int heightMM() const
  Q_INVOKABLE int heightMM() const { return get_selfptr()->heightMM(); }

  // int logicalDpiX() const
  Q_INVOKABLE int logicalDpiX() const { return get_selfptr()->logicalDpiX(); }

  // int logicalDpiY() const
  Q_INVOKABLE int logicalDpiY() const { return get_selfptr()->logicalDpiY(); }

  // int physicalDpiX() const
  Q_INVOKABLE int physicalDpiX() const { return get_selfptr()->physicalDpiX(); }

  // int physicalDpiY() const
  Q_INVOKABLE int physicalDpiY() const { return get_selfptr()->physicalDpiY(); }

  // qreal devicePixelRatio() const
  Q_INVOKABLE qreal devicePixelRatio() const { return get_selfptr()->devicePixelRatio(); }

  // qreal devicePixelRatioF()
  Q_INVOKABLE qreal devicePixelRatioF()  const { return get_selfptr()->devicePixelRatioF(); }

  // int colorCount()
  Q_INVOKABLE int colorCount() const { return get_selfptr()->colorCount(); }

  // int depth() const
  Q_INVOKABLE int depth() const { return get_selfptr()->depth(); }

  // static qreal devicePixelRatioFScale()
  Q_INVOKABLE static qreal devicePixelRatioFScale() { return QPaintDevice::devicePixelRatioFScale(); }

protected:

//  wrapper_QPaintDevice() noexcept;

public:

  // Конструктор из объекта
  wrapper_QPaintDevice(QPaintDevice *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QPaintDevice::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QPaintDevice() {
    qDebug() << "wrapper_QPaintDevice::destructor";
  }

  // Получение константного указателя на объект
  const QPaintDevice* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QPaintDevice::get_selfptr - got nullptr";
    }
    return static_cast<const QPaintDevice*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QPaintDevice* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPaintDevice::get_selfptr - got nullptr";
    }
    return static_cast<QPaintDevice*>(wrapper_common::get_selfptr());
  }
};


class wrapper_QPainter : public wrapper_common {

public:

  enum RenderHint {
      Antialiasing = 0x01,
      TextAntialiasing = 0x02,
      SmoothPixmapTransform = 0x04,
      VerticalSubpixelPositioning = 0x08,
      LosslessImageRendering = 0x40,
  };
  Q_FLAG(RenderHint)

  Q_DECLARE_FLAGS(RenderHints, RenderHint)
  Q_FLAG(RenderHints)

  class PixmapFragment {

  public:
      qreal x;
      qreal y;
      qreal sourceLeft;
      qreal sourceTop;
      qreal width;
      qreal height;
      qreal scaleX;
      qreal scaleY;
      qreal rotation;
      qreal opacity;
      static PixmapFragment Q_GUI_EXPORT create(const QPointF &pos, const QRectF &sourceRect,
                                          qreal scaleX = 1, qreal scaleY = 1,
                                          qreal rotation = 0, qreal opacity = 1);
  };

  enum PixmapFragmentHint {
      OpaqueHint = 0x01
  };

  Q_DECLARE_FLAGS(PixmapFragmentHints, PixmapFragmentHint)

#if 0

  Q_INVOKABLE  wrapper_QPainter();

  Q_INVOKABLE explicit wrapper_QPainter(QPaintDevice *);

  Q_INVOKABLE QPaintDevice *device() const;

  Q_INVOKABLE bool begin(QPaintDevice *);

  Q_INVOKABLE bool end();

  Q_INVOKABLE bool isActive() const;

  enum CompositionMode {
      CompositionMode_SourceOver,
      CompositionMode_DestinationOver,
      CompositionMode_Clear,
      CompositionMode_Source,
      CompositionMode_Destination,
      CompositionMode_SourceIn,
      CompositionMode_DestinationIn,
      CompositionMode_SourceOut,
      CompositionMode_DestinationOut,
      CompositionMode_SourceAtop,
      CompositionMode_DestinationAtop,
      CompositionMode_Xor,

      //svg 1.2 blend modes
      CompositionMode_Plus,
      CompositionMode_Multiply,
      CompositionMode_Screen,
      CompositionMode_Overlay,
      CompositionMode_Darken,
      CompositionMode_Lighten,
      CompositionMode_ColorDodge,
      CompositionMode_ColorBurn,
      CompositionMode_HardLight,
      CompositionMode_SoftLight,
      CompositionMode_Difference,
      CompositionMode_Exclusion,

      // ROPs
      RasterOp_SourceOrDestination,
      RasterOp_SourceAndDestination,
      RasterOp_SourceXorDestination,
      RasterOp_NotSourceAndNotDestination,
      RasterOp_NotSourceOrNotDestination,
      RasterOp_NotSourceXorDestination,
      RasterOp_NotSource,
      RasterOp_NotSourceAndDestination,
      RasterOp_SourceAndNotDestination,
      RasterOp_NotSourceOrDestination,
      RasterOp_SourceOrNotDestination,
      RasterOp_ClearDestination,
      RasterOp_SetDestination,
      RasterOp_NotDestination
  };

  Q_INVOKABLE void setCompositionMode(CompositionMode mode);

  Q_INVOKABLE CompositionMode compositionMode() const;

//  Q_INVOKABLE const QFont &font() const;

//  Q_INVOKABLE void setFont(const QFont &f);

//  QFontMetrics fontMetrics() const;
//  QFontInfo fontInfo() const;

//  void setPen(const QColor &color);
//  void setPen(const QPen &pen);
//  void setPen(Qt::PenStyle style);
//  const QPen &pen() const;

//  void setBrush(const QBrush &brush);
//  void setBrush(Qt::BrushStyle style);
//  const QBrush &brush() const;

  // attributes/modes
  void setBackgroundMode(Qt::BGMode mode);

  Qt::BGMode backgroundMode() const;

  QPoint brushOrigin() const;

  void setBrushOrigin(int x, int y);

  void setBrushOrigin(const QPoint &);

  void setBrushOrigin(const QPointF &);

  void setBackground(const QBrush &bg);

  const QBrush &background() const;

  qreal opacity() const;
  void setOpacity(qreal opacity);

  // Clip functions
  QRegion clipRegion() const;

  QPainterPath clipPath() const;

  void setClipRect(const QRectF &, Qt::ClipOperation op = Qt::ReplaceClip);

  void setClipRect(const QRect &, Qt::ClipOperation op = Qt::ReplaceClip);

  void setClipRect(int x, int y, int w, int h, Qt::ClipOperation op = Qt::ReplaceClip);

  void setClipRegion(const QRegion &, Qt::ClipOperation op = Qt::ReplaceClip);

  void setClipPath(const QPainterPath &path, Qt::ClipOperation op = Qt::ReplaceClip);

  void setClipping(bool enable);

  bool hasClipping() const;

  QRectF clipBoundingRect() const;

  void save();

  void restore();

  // XForm functions
  void setTransform(const QTransform &transform, bool combine = false);

  const QTransform &transform() const;

  const QTransform &deviceTransform() const;

  void resetTransform();

  void setWorldTransform(const QTransform &matrix, bool combine = false);

  const QTransform &worldTransform() const;

  QTransform combinedTransform() const;

  void setWorldMatrixEnabled(bool enabled);
  bool worldMatrixEnabled() const;

  void scale(qreal sx, qreal sy);

  void shear(qreal sh, qreal sv);

  void rotate(qreal a);

  void translate(const QPointF &offset);

  void translate(const QPoint &offset);

  void translate(qreal dx, qreal dy);

  QRect window() const;
  void setWindow(const QRect &window);
  void setWindow(int x, int y, int w, int h);

  QRect viewport() const;

  void setViewport(const QRect &viewport);

  void setViewport(int x, int y, int w, int h);

  void setViewTransformEnabled(bool enable);

  bool viewTransformEnabled() const;

  // drawing functions
  void strokePath(const QPainterPath &path, const QPen &pen);

  void fillPath(const QPainterPath &path, const QBrush &brush);

  void drawPath(const QPainterPath &path);

  void drawPoint(const QPointF &pt);
  void drawPoint(const QPoint &p);
  void drawPoint(int x, int y);

  void drawPoints(const QPointF *points, int pointCount);
  void drawPoints(const QPolygonF &points);
  void drawPoints(const QPoint *points, int pointCount);
  void drawPoints(const QPolygon &points);

  void drawLine(const QLineF &line);
  void drawLine(const QLine &line);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawLine(const QPoint &p1, const QPoint &p2);
  void drawLine(const QPointF &p1, const QPointF &p2);

  void drawLines(const QLineF *lines, int lineCount);
  void drawLines(const QList<QLineF> &lines);
  void drawLines(const QPointF *pointPairs, int lineCount);
  void drawLines(const QList<QPointF> &pointPairs);
  void drawLines(const QLine *lines, int lineCount);
  void drawLines(const QList<QLine> &lines);
  void drawLines(const QPoint *pointPairs, int lineCount);
  void drawLines(const QList<QPoint> &pointPairs);

  void drawRect(const QRectF &rect);
  void drawRect(int x1, int y1, int w, int h);
  void drawRect(const QRect &rect);

  void drawRects(const QRectF *rects, int rectCount);
  void drawRects(const QList<QRectF> &rectangles);
  void drawRects(const QRect *rects, int rectCount);
  void drawRects(const QList<QRect> &rectangles);

  void drawEllipse(const QRectF &r);
  void drawEllipse(const QRect &r);
  void drawEllipse(int x, int y, int w, int h);

  void drawEllipse(const QPointF &center, qreal rx, qreal ry);
  void drawEllipse(const QPoint &center, int rx, int ry);

  void drawPolyline(const QPointF *points, int pointCount);
  void drawPolyline(const QPolygonF &polyline);
  void drawPolyline(const QPoint *points, int pointCount);
  void drawPolyline(const QPolygon &polygon);

  void drawPolygon(const QPointF *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
  void drawPolygon(const QPolygonF &polygon, Qt::FillRule fillRule = Qt::OddEvenFill);
  void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
  void drawPolygon(const QPolygon &polygon, Qt::FillRule fillRule = Qt::OddEvenFill);

  void drawConvexPolygon(const QPointF *points, int pointCount);
  void drawConvexPolygon(const QPolygonF &polygon);
  void drawConvexPolygon(const QPoint *points, int pointCount);
  void drawConvexPolygon(const QPolygon &polygon);

  void drawArc(const QRectF &rect, int a, int alen);
  void drawArc(const QRect &, int a, int alen);
  void drawArc(int x, int y, int w, int h, int a, int alen);

  void drawPie(const QRectF &rect, int a, int alen);
  void drawPie(int x, int y, int w, int h, int a, int alen);
  void drawPie(const QRect &, int a, int alen);

  void drawChord(const QRectF &rect, int a, int alen);
  void drawChord(int x, int y, int w, int h, int a, int alen);
  void drawChord(const QRect &, int a, int alen);

  void drawRoundedRect(const QRectF &rect, qreal xRadius, qreal yRadius,
                       Qt::SizeMode mode = Qt::AbsoluteSize);
  void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius,
                              Qt::SizeMode mode = Qt::AbsoluteSize);
  void drawRoundedRect(const QRect &rect, qreal xRadius, qreal yRadius,
                              Qt::SizeMode mode = Qt::AbsoluteSize);

  void drawTiledPixmap(const QRectF &rect, const QPixmap &pm, const QPointF &offset = QPointF());
  void drawTiledPixmap(int x, int y, int w, int h, const QPixmap &, int sx=0, int sy=0);
  void drawTiledPixmap(const QRect &, const QPixmap &, const QPoint & = QPoint());
#ifndef QT_NO_PICTURE
  void drawPicture(const QPointF &p, const QPicture &picture);
  void drawPicture(int x, int y, const QPicture &picture);
  void drawPicture(const QPoint &p, const QPicture &picture);
#endif

  void drawPixmap(const QRectF &targetRect, const QPixmap &pixmap, const QRectF &sourceRect);
  void drawPixmap(const QRect &targetRect, const QPixmap &pixmap, const QRect &sourceRect);
  void drawPixmap(int x, int y, int w, int h, const QPixmap &pm,
                         int sx, int sy, int sw, int sh);
  void drawPixmap(int x, int y, const QPixmap &pm,
                         int sx, int sy, int sw, int sh);
  void drawPixmap(const QPointF &p, const QPixmap &pm, const QRectF &sr);
  void drawPixmap(const QPoint &p, const QPixmap &pm, const QRect &sr);
  void drawPixmap(const QPointF &p, const QPixmap &pm);
  void drawPixmap(const QPoint &p, const QPixmap &pm);
  void drawPixmap(int x, int y, const QPixmap &pm);
  void drawPixmap(const QRect &r, const QPixmap &pm);
  void drawPixmap(int x, int y, int w, int h, const QPixmap &pm);

  void drawPixmapFragments(const PixmapFragment *fragments, int fragmentCount,
                           const QPixmap &pixmap, PixmapFragmentHints hints = PixmapFragmentHints());

  void drawImage(const QRectF &targetRect, const QImage &image, const QRectF &sourceRect,
                 Qt::ImageConversionFlags flags = Qt::AutoColor);
  void drawImage(const QRect &targetRect, const QImage &image, const QRect &sourceRect,
                        Qt::ImageConversionFlags flags = Qt::AutoColor);
  void drawImage(const QPointF &p, const QImage &image, const QRectF &sr,
                        Qt::ImageConversionFlags flags = Qt::AutoColor);
  void drawImage(const QPoint &p, const QImage &image, const QRect &sr,
                        Qt::ImageConversionFlags flags = Qt::AutoColor);
  void drawImage(const QRectF &r, const QImage &image);
  void drawImage(const QRect &r, const QImage &image);
  void drawImage(const QPointF &p, const QImage &image);
  void drawImage(const QPoint &p, const QImage &image);
  void drawImage(int x, int y, const QImage &image, int sx = 0, int sy = 0,
                        int sw = -1, int sh = -1, Qt::ImageConversionFlags flags = Qt::AutoColor);

  void setLayoutDirection(Qt::LayoutDirection direction);
  Qt::LayoutDirection layoutDirection() const;

#if !defined(QT_NO_RAWFONT)
    void drawGlyphRun(const QPointF &position, const QGlyphRun &glyphRun);
#endif

  void drawStaticText(const QPointF &topLeftPosition, const QStaticText &staticText);
  void drawStaticText(const QPoint &topLeftPosition, const QStaticText &staticText);
  void drawStaticText(int left, int top, const QStaticText &staticText);

  void drawText(const QPointF &p, const QString &s);
  void drawText(const QPoint &p, const QString &s);
  void drawText(int x, int y, const QString &s);

  void drawText(const QPointF &p, const QString &str, int tf, int justificationPadding);

  void drawText(const QRectF &r, int flags, const QString &text, QRectF *br = nullptr);
  void drawText(const QRect &r, int flags, const QString &text, QRect *br = nullptr);
  void drawText(int x, int y, int w, int h, int flags, const QString &text, QRect *br = nullptr);

  void drawText(const QRectF &r, const QString &text, const QTextOption &o = QTextOption());

  QRectF boundingRect(const QRectF &rect, int flags, const QString &text);
  QRect boundingRect(const QRect &rect, int flags, const QString &text);
  QRect boundingRect(int x, int y, int w, int h, int flags, const QString &text);

  QRectF boundingRect(const QRectF &rect, const QString &text, const QTextOption &o = QTextOption());

  void drawTextItem(const QPointF &p, const QTextItem &ti);
  void drawTextItem(int x, int y, const QTextItem &ti);
  void drawTextItem(const QPoint &p, const QTextItem &ti);

  void fillRect(const QRectF &, const QBrush &);
  void fillRect(int x, int y, int w, int h, const QBrush &);
  void fillRect(const QRect &, const QBrush &);

  void fillRect(const QRectF &, const QColor &color);
  void fillRect(int x, int y, int w, int h, const QColor &color);
  void fillRect(const QRect &, const QColor &color);

  void fillRect(int x, int y, int w, int h, Qt::GlobalColor c);
  void fillRect(const QRect &r, Qt::GlobalColor c);
  void fillRect(const QRectF &r, Qt::GlobalColor c);

  void fillRect(int x, int y, int w, int h, Qt::BrushStyle style);
  void fillRect(const QRect &r, Qt::BrushStyle style);
  void fillRect(const QRectF &r, Qt::BrushStyle style);

  void fillRect(int x, int y, int w, int h, QGradient::Preset preset);
  void fillRect(const QRect &r, QGradient::Preset preset);
  void fillRect(const QRectF &r, QGradient::Preset preset);

  void eraseRect(const QRectF &);
  void eraseRect(int x, int y, int w, int h);
  void eraseRect(const QRect &);

  void setRenderHint(RenderHint hint, bool on = true);
  void setRenderHints(RenderHints hints, bool on = true);
  RenderHints renderHints() const;
  bool testRenderHint(RenderHint hint) const { return renderHints() & hint; }

  // QPaintEngine *paintEngine() const;

  void beginNativePainting();

  void endNativePainting();

#endif

public:

  // Конструктор из объекта
  wrapper_QPainter(QPainter *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QPainter::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QPainter() {
    qDebug() << "wrapper_QPainter::destructor";
  }

  // Получение константного указателя на объект
  const QPainter* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QPainter::get_selfptr - got nullptr";
    }
    return static_cast<const QPainter*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QPainter* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPainter::get_selfptr - got nullptr";
    }
    return static_cast<QPainter*>(wrapper_common::get_selfptr());
  }
};

#endif // WRAPPER_QPAINTER_H
