#include "wrapper_QPainter.h"

// virtual int devType() const
int wrapper_QPaintDevice::devType() const { return get_selfptr()->devType(); }

// bool paintingActive() const
bool wrapper_QPaintDevice::paintingActive() const { return get_selfptr()->paintingActive(); }

// int width() const
int wrapper_QPaintDevice::width() const { return get_selfptr()->width(); }

// int height() const
int wrapper_QPaintDevice::height() const { return get_selfptr()->height(); }

// int widthMM() const
int wrapper_QPaintDevice::widthMM() const { return get_selfptr()->widthMM(); }

// int heightMM() const
int wrapper_QPaintDevice::heightMM() const { return get_selfptr()->heightMM(); }

// int logicalDpiX() const
int wrapper_QPaintDevice::logicalDpiX() const { return get_selfptr()->logicalDpiX(); }

// int logicalDpiY() const
int wrapper_QPaintDevice::logicalDpiY() const { return get_selfptr()->logicalDpiY(); }

// int physicalDpiX() const
int wrapper_QPaintDevice::physicalDpiX() const { return get_selfptr()->physicalDpiX(); }

// int physicalDpiY() const
int wrapper_QPaintDevice::physicalDpiY() const { return get_selfptr()->physicalDpiY(); }

// qreal devicePixelRatio() const
qreal wrapper_QPaintDevice::devicePixelRatio() const { return get_selfptr()->devicePixelRatio(); }

// qreal devicePixelRatioF()
qreal wrapper_QPaintDevice::devicePixelRatioF()  const { return get_selfptr()->devicePixelRatioF(); }

// int colorCount()
int wrapper_QPaintDevice::colorCount() const { return get_selfptr()->colorCount(); }

// int depth() const
int wrapper_QPaintDevice::depth() const { return get_selfptr()->depth(); }

// static qreal devicePixelRatioFScale()
qreal wrapper_QPaintDevice::devicePixelRatioFScale() { return QPaintDevice::devicePixelRatioFScale(); }


// Конструктор из объекта
wrapper_QPaintDevice::wrapper_QPaintDevice(void *self) : wrapper_common(self) {
  qDebug() << "wrapper_QPaintDevice::constructor(self=" << get_selfvalue() << ")";
}

// Деструктор
wrapper_QPaintDevice::~wrapper_QPaintDevice() {
  qDebug() << "wrapper_QPaintDevice::destructor(self=" << get_selfvalue() << ")";
}

// Получение константного указателя на объект
const QPaintDevice* wrapper_QPaintDevice::get_selfptr() const {
  return static_cast<const QPaintDevice*>(wrapper_common::get_selfptr());
}

// Получение указателя на объект
QPaintDevice* wrapper_QPaintDevice::get_selfptr() {
  return static_cast<QPaintDevice*>(wrapper_common::get_selfptr());
}


#if 0

   wrapper_QPainter();

  explicit wrapper_QPainter(QPaintDevice *);

  QPaintDevice *device() const;

  bool begin(QPaintDevice *);

  bool end();

  bool isActive() const;

  void setCompositionMode(CompositionMode mode);

  CompositionMode compositionMode() const;

//  const QFont &font() const;

//  void setFont(const QFont &f);

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

// Конструктор из объекта
wrapper_QPainter::wrapper_QPainter(void *self) :  wrapper_common(self) {
    qDebug() << "wrapper_QPainter::constructor(self=" << get_selfvalue() << ")";
  }

// Деструктор
wrapper_QPainter::~wrapper_QPainter() {
  qDebug() << "wrapper_QPainter::destructor(self=" << get_selfvalue() << ")";
}

// Получение константного указателя на объект
const QPainter* wrapper_QPainter::get_selfptr() const {
  return static_cast<const QPainter*>(wrapper_common::get_selfptr());
}

// Получение указателя на объект
QPainter* wrapper_QPainter::get_selfptr() {
  return static_cast<QPainter*>(wrapper_common::get_selfptr());
}
