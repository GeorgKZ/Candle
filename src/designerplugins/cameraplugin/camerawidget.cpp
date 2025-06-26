#include "camerawidget.h"

#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraDevice>
#include <QtMultimedia/QMediaCaptureSession>
#include <QtMultimedia/QMediaDevices>
#include <QtMultimediaWidgets/QGraphicsVideoItem>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsScene>

#ifdef QT_FEATURE_permissions
  #include <QtCore/QPermission>
#endif

/**
 * \file
 *
 * \brief Файл с определениями функций-членов класса \ref CameraWidget "CameraWidget"
 *
 * <BR>
 * Функции, являющиеся методами класса \ref CameraWidget "CameraWidget":
 * <BR>
 * * \copybrief CameraWidget::CameraWidget(QWidget *)
 */
CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent), m_captureSession(new QMediaCaptureSession)
{

//    qDebug() << "CameraWidget::constructor(parent=" << (unsigned long long)(parent) << ")";

#ifdef QT_FEATURE_permissions
    qDebug() << "Using premissions feature";
#endif


    /** 
     * Для MacOS в файле Info.plist должны быть установлены разрешения:
     * <key>NSCameraUsageDescription</key>
     * <string>The camera is used by CameraWidget plugin.</string>
     * <key>com.apple.security.device.camera</key>
     * <true/>
     * https://doc.qt.io/qt-6/macos.html
     */

    m_view = new myGraphicsView(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_scene = new QGraphicsScene(m_view);
    m_item = new QGraphicsVideoItem();
    m_view->setScene(m_scene);
    m_scene->addItem(m_item);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->horizontalScrollBar()->setEnabled(false);
    m_scrollArea->verticalScrollBar()->setEnabled(false);
    m_scrollArea->setWidget(m_view);

    layout->addWidget(m_scrollArea);
    layout->setContentsMargins(0,0,0,0);

    m_zoom = 1.0;
    m_videoScale = 1.0;
    m_camera = nullptr;
    m_aimColor = -65536;
    m_aimSize = 20;
    m_aimLineWidth = 1;
    m_aimPosition = QPoint(0,0);

    permissionChecking();

    QCameraDevice dev;
    if (QMediaDevices::videoInputs().empty()) {
        /** Взять камеру по умолчанию */
        dev = QMediaDevices::defaultVideoInput();
        m_cameraName = QString();
        /** Взять разрешение по умолчанию */
        m_resolution = QSize(1280,720);
        qDebug() << "CameraWidget::CameraWidget - got default camera";
    } else {
        /** Взять первую доступную камеру */
        dev = QMediaDevices::videoInputs()[0];
        m_cameraName = dev.description();
        /** Взять первое доступное разрешение */
        m_resolution = dev.videoFormats()[0].resolution();
        qDebug() << "CameraWidget::CameraWidget - got first available camera" << m_cameraName << ", resolution=" << m_resolution;
    }
    setCamera(dev);
}

/**
 * \file
 * * \copybrief CameraWidget::permissionChecking()
 */
void CameraWidget::permissionChecking()
{
#if defined(QT_FEATURE_permissions) || defined(__DOXYGEN__)
    QCameraPermission cameraPermission;

    /**
     * Алгоритм:
     *
     * 1. Проверить наличие разрешения на использование камеры (камер).
     */
    switch (qApp->checkPermission(cameraPermission)) {
    /**
     * 1.1. Если ни разрешение, ни запрет на использование камеры не были объявлены, запросить
     * разрешение, функция будет вызвана повторно.
     */
    case Qt::PermissionStatus::Undetermined:
        qDebug() << "Camera (p) permission is undetermined, requesting...";
        qApp->requestPermission(cameraPermission, // this,
            &CameraWidget::permissionChecking);
        qDebug() << "Camera (p) permission requested";
        break;
    /**
     * 1.2. Если явно объявлен запрет на использование камеры, закончить инициализацию.
     */
    case Qt::PermissionStatus::Denied:
        qWarning() << "Camera (p) permission is not granted!";
        break;
    /**
     * 1.3. Если явно объявлено разрешение на использование камеры, продолжить инициализацию.
     */
    case Qt::PermissionStatus::Granted:
        qDebug() << "Camera (p) permission is granted";
        break;
    }
#endif
}

CameraWidget::~CameraWidget()
{
    m_scrollArea->deleteLater();
    layout()->deleteLater();
    m_scene->removeItem(m_item);
    m_item->deleteLater();
    m_scene->deleteLater();
    m_view->deleteLater();
}

void CameraWidget::setCameraName(QString cameraName)
{
    qDebug() << "CameraWidget::setCameraName(" << cameraName << ")";

    if (m_cameraName.isEmpty()) {
        m_cameraName = cameraName;
        setCamera(QMediaDevices::defaultVideoInput());
        return;
    }

    foreach (const QCameraDevice &i, QMediaDevices::videoInputs()) {
        if (i.description() == cameraName) {
            m_cameraName = cameraName;
            setCamera(i);
            break;
        }
    }
}

QString CameraWidget::cameraName() const
{
    return m_cameraName;
}

QStringList CameraWidget::availableCameras() const
{
    QStringList l;
    foreach (const QCameraDevice &i, QMediaDevices::videoInputs()) {
        l << i.description();
    }
    return l;
}

QStringList CameraWidget::availableResolutions() const
{
    QStringList l;
    foreach(QCameraFormat f, m_camera->cameraDevice().videoFormats()) {
        l.append(QString("%1x%2").arg(f.resolution().width()).arg(f.resolution().height()));
    }
    return l;
}

void CameraWidget::setCamera(const QCameraDevice& cameraDevice)
{
    if (m_camera == nullptr || m_camera->cameraDevice() != cameraDevice) {

        if (m_captureSession->camera() != nullptr && m_captureSession->camera() != m_camera) {
          m_captureSession->camera()->stop();
          delete m_captureSession->camera();
          qDebug() << "CameraWidget::setCamera - delete prev. capture camera";
        }

        if (m_camera != nullptr) {
            if (m_camera->isActive()) {
               qDebug() << "CameraWidget::setCamera - stop prev. camera";
               this->stop();
            }
            m_camera->deleteLater();
            qDebug() << "CameraWidget::setCamera - delete prev. camera";
        }

        qDebug() << "CameraWidget::setCamera - creating new camera";
        m_camera = new QCamera(cameraDevice);

        qDebug() << "CameraWidget::setCamera - setting new capture camera";
        m_captureSession->setCamera(m_camera);

        // Установить preview для сессии захвата
        qDebug() << "CameraWidget::setCamera - setting new preview";
        m_captureSession->setVideoOutput(m_item);

        if (isVisible()) {
            qDebug() << "CameraWidget::setCamera - starting new camera";
            this->start();
        }
        setResolution(m_resolution);
    } else {
        qDebug() << "CameraWidget::setCamera - ignoring (same device)";
    }
}

bool CameraWidget::isCameraActive() const
{
    return m_camera->isActive();
}

void CameraWidget::start()
{
    qDebug() << "CameraWidget::start()";
    m_camera->start();
}

void CameraWidget::stop()
{
    qDebug() << "CameraWidget::stop()";
    m_camera->stop();
}

qreal CameraWidget::videoScale() const
{
    return m_videoScale;
}

void CameraWidget::updateSize()
{
    qreal widthRatio = static_cast<qreal>(m_scrollArea->contentsRect().size().width()) / m_resolution.width();
    qreal heightRatio = static_cast<qreal>(m_scrollArea->contentsRect().size().height()) / m_resolution.height();

    m_videoScale = qMax(qMax(heightRatio, widthRatio), m_zoom);

    m_item->setSize(m_videoScale * m_resolution);
    m_view->resize(m_videoScale * m_resolution);
}

void CameraWidget::setResolution(const QSize &resolution)
{
    foreach(QCameraFormat f, m_camera->cameraDevice().videoFormats()) {
        if (f.resolution() == resolution) {
            m_resolution = resolution;
            m_camera->setCameraFormat(f);
            updateSize();
            qDebug() << "CameraWidget::setResolution, resol=" << m_camera->cameraFormat().resolution();
            emit resolutionChanged(m_resolution);
            return;
        }
    }
    qDebug() << "CameraWidget::setResolution - ignoring wrong resolution";
}

QSize CameraWidget::resolution() const
{
    return m_resolution;
}

void CameraWidget::setZoom(qreal zoom)
{
    zoom = qBound<qreal>(1.0, zoom, 8.0);
    if (m_zoom != zoom) {
        m_zoom = zoom;
        updateSize();
        emit zoomChanged(m_zoom);
    }
}

qreal CameraWidget::zoom() const
{
    return m_zoom;
}

void CameraWidget::setPos(const QPoint &position)
{
    QPoint oldPos = pos();

    m_scrollArea->horizontalScrollBar()->setValue(position.x());
    m_scrollArea->verticalScrollBar()->setValue(position.y());

    QPoint newPos = pos();
    if (oldPos != newPos) {
        emit posChanged(newPos);
    }
}

QPoint CameraWidget::pos() const
{
    return QPoint(m_scrollArea->horizontalScrollBar()->value(),
                  m_scrollArea->verticalScrollBar()->value());
}

void CameraWidget::setAimPos(const QPoint &aimPos)
{
    int maxx = m_view->frameSize().width() - m_aimLineWidth;
    int maxy = m_view->frameSize().height() - m_aimLineWidth;

    if (maxx <= 0 || maxy <= 0) return;

    QPoint newAimPos( qBound<int>(0, aimPos.x(), maxx), qBound<int>(0, aimPos.y(), maxy) );

    if (newAimPos != m_aimPosition) {
        m_aimPosition = newAimPos;
        emit aimPosChanged(m_aimPosition);
    }
}

QPoint CameraWidget::aimPos() const
{
    return m_aimPosition;
}

void CameraWidget::setAimSize(int aimSize)
{
    if (aimSize >= 0 && m_aimSize != aimSize) {
        m_aimSize = aimSize;
        emit aimSizeChanged(aimSize);
    }
}

int CameraWidget::aimSize() const
{
    return m_aimSize;
}

void CameraWidget::setAimLineWidth(int aimLineWidth)
{
    if (m_aimLineWidth >= 0 && m_aimLineWidth != aimLineWidth) {
        m_aimLineWidth = aimLineWidth;
        emit aimLineWidthChanged(aimLineWidth);
    }
}

int CameraWidget::aimLineWidth() const
{
    return m_aimLineWidth;
}

void CameraWidget::setAimColor(int aimColor)
{
    if (m_aimColor != aimColor) {
        m_aimColor = aimColor;
        emit aimColorChanged(aimColor);
    }
}

int CameraWidget::aimColor() const
{
    return m_aimColor;
}

void CameraWidget::resizeEvent(QResizeEvent *e)
{
    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события изменения размера.
     */
    QWidget::resizeEvent(e);

    /**
     * Запомнить предыдущие координаты прицельных элементов и сдвига видеокадра,
     * предыдущий коэффициент масштабирования изображения камеры.
     */
    QPoint prevAim = aimPos();
    QPoint prevPos = pos();
    qreal prevScale = m_videoScale;

    /**
     * Выполнить пересчёт коэффициента масштабирования изображения камеры и
     * изменение размера видеокадра.
     */
    updateSize();

    /**
     * Пересчитать координаты прицельных элементов, чтобы они указывали по возможности
     * на ту же самую точку изображения
     */
    setAimPos(aimPos() * m_videoScale / prevScale);

    /**
     * Пересчитать координаты сдвига видеокадра, чтобы координаты прицельных элементов
     * относительно окна виджета по возможности остались прежними.
     */
    setPos(prevPos + aimPos() - prevAim);
}

void CameraWidget::hideEvent(QHideEvent *event)
{
//    qDebug() << "CameraWidget::hideEvent";

    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события выключения отображения.
     */
    QWidget::hideEvent(event);

    /**
     * Если текущая камера работает, выключить её.
     */
    if (isCameraActive()) {
        stop();
    }
}

void CameraWidget::showEvent(QShowEvent *event)
{
//    qDebug() << "CameraWidget::showEvent";

    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события включения отображения.
     */
    QWidget::showEvent(event);

    if (m_camera->isAvailable()) {
        setCameraName(m_cameraName);
    }

    /**
     * Если текущая камера не работает, включить её.
     */
    if (!isCameraActive()) {
        start();
    }
}

myGraphicsView::myGraphicsView(CameraWidget *parent) :
    QGraphicsView(static_cast<QWidget*>(parent)), m_parent(parent) {}

void myGraphicsView::paintEvent(QPaintEvent *event)
{
    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события отрисовки вида.
     */
    QGraphicsView::paintEvent(event);

    /**
     * Если текущая камера не работает, то больше ничего не делать.
     */
    if (!m_parent->isCameraActive()) {
        return;
    }

    /** Создать экземпляр QPainter на основе родительского виджета. */
    QPainter painter(viewport());

    /** Настроить "карандаш", который будет использоваться при отображении. */
    QPen pen(Qt::DashLine);
    pen.setWidth(m_parent->aimLineWidth());
    pen.setColor(QColor::fromRgb(m_parent->aimColor()));

    /** Получить координаты перекрестия прицельных элементов в системе координат окна виджета */
    int x = m_parent->aimPos().x();
    int y = m_parent->aimPos().y();

    /** Получить размеры видеокадра, приведённого к окну виджета */
    int width = frameSize().width();
    int height = frameSize().height();

    /** Установить "карандаш" в качестве используемого при отображении. */
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);

    /** Нарисовать прицельные линии. */
    if (x > m_parent->aimSize() / 2) {
        painter.drawLine(0, y, x - m_parent->aimSize() / 2, y);
    }
    if (x <= width - m_parent->aimSize() / 2) {
        painter.drawLine(x + m_parent->aimSize() / 2, y, width, y);
    }
    if (y > m_parent->aimSize() / 2) {
        painter.drawLine(x, 0, x, y - m_parent->aimSize() / 2);
    }
    if (y <= width - m_parent->aimSize() / 2) {
        painter.drawLine(x, y + m_parent->aimSize() / 2, x, height);
    }

    /** Нарисовать прицельную окружность. */
    painter.drawEllipse(m_parent->aimPos(), m_parent->aimSize() / 2, m_parent->aimSize() / 2);
}

void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события изменения координат "мыши".
     */
    QGraphicsView::mouseMoveEvent(event);

    /**
     * Если текущая камера не работает, то ничего не делать.
     */
    if (!m_parent->isCameraActive()) {
        return;
    }

    /**
     * Определить изменение координат "мыши" относительно последних сохранённых.
     */
    QPoint d = (event->globalPosition() - m_mousePos).toPoint();

    /** Сохранить новые координаты мыши */
    m_mousePos = event->globalPosition();

    if (event->buttons() == Qt::LeftButton) {

        /** Если было нажатие левой кнопки мыши с шифтом,... */
        if (event->modifiers() == Qt::ShiftModifier) {

            /** установить новые координаты перекрестия прицельных линий... */
             m_parent->setAimPos(m_parent->aimPos() + d);

        /** Если было нажатие левой кнопки мыши без шифта,... */
        } else {

            /** установить новые координаты сдвига видеокадра относительно окна виджета. */
            m_parent->setPos(m_parent->pos() - d);
        }
    }
}

void myGraphicsView::wheelEvent(QWheelEvent *event)
{

    /**
     * Алгоритм:
     *
     * Сандартный обработчик события поворота колёсика "мыши" не вызывать, так как он
     * обычно приводит к сдвигу видекадра (действует на скроллеры).
     *
     * Если текущая камера не работает, то ничего не делать.
     */
    if (!m_parent->isCameraActive()) {
        return;
    }

    /**
     * Запомнить предыдущие координаты прицельных элементов и сдвига видеокадра,
     * предыдущий коэффициент масштабирования изображения камеры.
     */
    QPoint prevAim = m_parent->aimPos();
    QPoint prevPos = m_parent->pos();
    qreal prevScale = m_parent->videoScale();

    /**
     * Установить новый коэффициент масштабирования видеокадра в зависимости от
     * угла поворота колёсика "мыши" --- сильнее при "наезде" и слабее при "отъезде".
     * Если видеокадр уже масштабирован из-за размеров окна виджета, превышающих
     * размер видеокадра, повторить изменение коэффициента.
     */
    for (int i = 0; m_parent->videoScale() == prevScale && i < 3; ++i) {
        m_parent->setZoom(m_parent->zoom() * (event->angleDelta().y() > 0 ? 1.25 : 0.8));
    }

    /**
     * Пересчитать координаты прицельных элементов, чтобы они указывали по возможности
     * на ту же самую точку изображения
     */
    m_parent->setAimPos(m_parent->aimPos() * m_parent->videoScale() / prevScale);

    /**
     * Пересчитать координаты сдвига видеокадра, чтобы координаты прицельных элементов
     * относительно окна виджета по возможности остались прежними.
     */
    m_parent->setPos(prevPos + m_parent->aimPos() - prevAim);
}

void myGraphicsView::mousePressEvent(QMouseEvent *event)
{
    /**
     * Алгоритм:
     *
     * Вызвать стандартный обработчик события нажатия клавиши "мыши".
     */
    QGraphicsView::mousePressEvent(event);

    /**
     * Сохранить новые координаты мыши
     */
    m_mousePos = event->globalPosition();
}
