#ifndef WRAPPER_CAMERAWIDGET_H
#define WRAPPER_CAMERAWIDGET_H

#include <QtCore/QObject>
#include "camerawidget.h"
#include "wrapper_QWidget.h"
#include "wrapper_QSize.h"
#include "wrapper_QPoint.h"

class WRAPPER_DLL_EXPORT wrapper_CameraWidget : public wrapper_QWidget {

  Q_OBJECT

// Из файла camerawidget.h

    Q_PROPERTY(QStringList availableCameras
        READ availableCameras)
    Q_PROPERTY(QStringList availableResolutions
        READ availableResolutions)
    Q_PROPERTY(QString cameraName
        READ cameraName
        WRITE setCameraName)
    Q_PROPERTY(QJSValue resolution // QSize
        READ resolution
        WRITE setResolution
        NOTIFY resolutionChanged)
    Q_PROPERTY(qreal zoom
        READ zoom
        WRITE setZoom
        NOTIFY zoomChanged)
    Q_PROPERTY(QJSValue pos // QPoint
        READ pos
        WRITE setPos
        NOTIFY posChanged
        STORED false)
    Q_PROPERTY(QJSValue aimPos // QPoint
        READ aimPos
        WRITE setAimPos
        NOTIFY aimPosChanged)
    Q_PROPERTY(int aimSize
        READ aimSize
        WRITE setAimSize
        NOTIFY aimSizeChanged)
    Q_PROPERTY(int aimLineWidth
        READ aimLineWidth
        WRITE setAimLineWidth
        NOTIFY aimLineWidthChanged)
    Q_PROPERTY(int aimColor
        READ aimColor
        WRITE setAimColor
        NOTIFY aimColorChanged)

public:

  // CameraWidget(QWidget *parent = nullptr);
  Q_INVOKABLE wrapper_CameraWidget(const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QWidget(new CameraWidget(jsvalueToPointer(QWidget, parent))) {
    qDebug() << "wrapper_CameraWidget::constructor(parent=" << (unsigned long long)(get_selfptr())->parent() << ")";
    set_connections();
  }

  // QStringList availableCameras() const
  Q_INVOKABLE QStringList availableCameras() const {
    return get_selfptr()->availableCameras();
  }

  // QStringList availableResolutions() const
  Q_INVOKABLE QStringList availableResolutions() const {
    return get_selfptr()->availableResolutions();
  }

  Q_INVOKABLE void setCameraName(QString cameraName) { get_selfptr()->setCameraName(cameraName); }
  Q_INVOKABLE QString cameraName() const { return get_selfptr()->cameraName(); }

  Q_INVOKABLE void setResolution(const QJSValue &resolution) {
    qDebug() << "wrapper_CameraWidget::setResolution()";
    QSize* p = jsvalueToPointer(QSize, resolution);
    get_selfptr()->setResolution(*p);
    emit resolutionChanged(resolution);
  }

  Q_INVOKABLE  QJSValue resolution() const {
    qDebug() << "wrapper_CameraWidget::resolution()";
    QSize* p = new QSize(get_selfptr()->resolution());
//  return wrapperFactory("QSize", p);
    return PointerToJsvalue(QSize, p);
  }

  Q_INVOKABLE void setZoom(qreal zoom) {
    qDebug() << "wrapper_CameraWidget::setZoom(" << zoom << ")";
    get_selfptr()->setZoom(zoom);
    emit zoomChanged(zoom);
  }

  Q_INVOKABLE qreal zoom() const {
    qDebug() << "wrapper_CameraWidget::zoom()";
    return get_selfptr()->zoom();
  }

    Q_INVOKABLE void setPos(const QJSValue &pos) {
    qDebug() << "wrapper_CameraWidget::resolution()";
    QPoint* p = jsvalueToPointer(QPoint, pos);
    get_selfptr()->setPos(*p);
    emit posChanged(pos);
  }

  Q_INVOKABLE QJSValue pos() const {
    QPoint* p = new QPoint(get_selfptr()->pos());
//  return wrapperFactory("QPoint", p);
    return PointerToJsvalue(QPoint, p);
  }

  Q_INVOKABLE void setAimPos(const QJSValue &aimPos) {
    qDebug() << "wrapper_CameraWidget::setAimPos(QJSValue)";
    QPoint* p = jsvalueToPointer(QPoint, aimPos);
    get_selfptr()->setAimPos(*p);
    emit aimPosChanged(aimPos);
  }

  Q_INVOKABLE QJSValue aimPos() const {
    qDebug() << "wrapper_CameraWidget::aimPos()";
    QPoint* p = new QPoint(get_selfptr()->aimPos());
//  return wrapperFactory("QPoint", p);
    return PointerToJsvalue(QPoint, p);
  }

  Q_INVOKABLE void setAimSize(int aimSize) {
    get_selfptr()->setAimSize(aimSize);
    emit aimSizeChanged(aimSize);
  }

  Q_INVOKABLE int aimSize() const {
    return get_selfptr()->aimSize();
  }

  Q_INVOKABLE void setAimLineWidth(int aimLineWidth) {
    get_selfptr()->setAimLineWidth(aimLineWidth);
    emit aimLineWidthChanged(aimLineWidth);
  }

  Q_INVOKABLE int aimLineWidth() const {
    return get_selfptr()->aimLineWidth();
  }

  Q_INVOKABLE void setAimColor(int aimColor) {
    get_selfptr()->setAimColor(aimColor);
    emit aimColorChanged(aimColor);
  }

  Q_INVOKABLE int aimColor() const {
    return get_selfptr()->aimColor();
  }

signals:

  void resolutionChanged(const QJSValue &resolution);
  void zoomChanged(qreal zoom);
  void posChanged(const QJSValue &pos);
  void aimPosChanged(const QJSValue &aimPos);
  void aimSizeChanged(int aimSize);
  void aimLineWidthChanged(int aimLineWidth);
  void aimColorChanged(int aimColor);

public slots:

  Q_INVOKABLE void start() {
    get_selfptr()->start();
  }

  Q_INVOKABLE void stop() {
    get_selfptr()->stop();
  }

private:

    /**
     * \brief Соединения изменения объекта с сигналом прокси-класса
     */
    void set_connections()
    {
        QObject::connect(get_selfptr(),
          &CameraWidget::resolutionChanged,
          [=](){emit resolutionChanged(resolution());});
    
        QObject::connect(get_selfptr(),
          &CameraWidget::zoomChanged,
          [=](){emit zoomChanged(zoom());});
    
        QObject::connect(get_selfptr(),
          &CameraWidget::posChanged,
          [=](){emit posChanged(pos());});
    
        QObject::connect(get_selfptr(),
          &CameraWidget::aimPosChanged,
          [=](){emit aimPosChanged(aimPos());});
    
        QObject::connect(get_selfptr(),
          &CameraWidget::aimLineWidthChanged,
          [=](){emit aimLineWidthChanged(aimLineWidth());});
    
        QObject::connect(get_selfptr(),
          &CameraWidget::aimColorChanged,
          [=](){emit aimColorChanged(aimColor());});
    }

public:

  // Конструктор из объекта
  wrapper_CameraWidget(void *self) : wrapper_QWidget(self) {
    qDebug() << "wrapper_CameraWidget::constructor(self=" << get_selfvalue() << ")";
    set_connections();
  }

  // Получение константного указателя на объект
  const CameraWidget* get_selfptr() const {
   return static_cast<const CameraWidget*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  CameraWidget* get_selfptr() {
    return static_cast<CameraWidget*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_CameraWidget() override {
    qDebug() << "wrapper_CameraWidget::destructor(self=" << get_selfvalue() << ")";
  }
};

Q_DECLARE_METATYPE(wrapper_CameraWidget)

#endif // WRAPPER_CAMERAWIDGET_H
