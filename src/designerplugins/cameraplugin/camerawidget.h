#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QtWidgets/QGraphicsView>
#include "customwidgetsshared.h"

class QScrollArea;
class QCamera;
class QCameraDevice;
class QGraphicsVideoItem;
class QMediaCaptureSession;
class CameraWidget;

/**
 * \brief Объявление класса \ref myGraphicsView "myGraphicsView"
 */
class myGraphicsView: public QGraphicsView
{

public:
 
    /**
     * \brief Конструктор
     * \param [in] parent Родительский объект
     */
    myGraphicsView(CameraWidget *parent);

private:

    /**
     * \brief Указатель на родительский виджет
     */
    CameraWidget *m_parent;

    /**
     * \brief Последние обработанные координаты "мыши"
     */
    QPointF m_mousePos;

    /**
     * \brief Обработчик события перерисовки окна
     */
    virtual void paintEvent(QPaintEvent *e) override;

    /**
     * \brief Обработчик события изменения координат "мыши" в окне
     */
    virtual void mouseMoveEvent(QMouseEvent *e) override;

    /**
     * \brief Обработчик события нажатия кнопки "мыши" в окне
     */
    virtual void mousePressEvent(QMouseEvent *e) override;

    /**
     * \brief Обработчик события поворота колёсика "мыши" в окне
     */
    virtual void wheelEvent(QWheelEvent *e) override;
};

/**
 * \brief Объявление класса \ref CameraWidget "CameraWidget"
 */
class CUSTOMWIDGETS_DLLSPEC CameraWidget: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QStringList availableCameras
        READ availableCameras)
    Q_PROPERTY(QStringList availableResolutions
        READ availableResolutions)
    Q_PROPERTY(QString cameraName
        READ cameraName
        WRITE setCameraName)
    Q_PROPERTY(QSize resolution
        READ resolution
        WRITE setResolution
        NOTIFY resolutionChanged)
    Q_PROPERTY(qreal zoom
        READ zoom
        WRITE setZoom
        NOTIFY zoomChanged)
    Q_PROPERTY(QPoint pos
        READ pos
        WRITE setPos
        NOTIFY posChanged)
    Q_PROPERTY(QPoint aimPos
        READ aimPos
        WRITE setAimPos
        NOTIFY aimPosChanged
        STORED false)
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

    /**
     * \brief Конструктор
     * \param [in] parent Родительский объект
     */
    CameraWidget(QWidget *parent = nullptr);

    /**
     * \brief Деструктор
     */
    virtual ~CameraWidget() override;

    /**
     * \brief Проверить, работает ли текущая камера
     */
    bool isCameraActive() const;

    /**
     * \brief Получить список имён доступных камер
     */
    QStringList availableCameras() const;

    /**
     * \brief Получить список поддерживаемых разрешений текущей камеры
     */
    QStringList availableResolutions() const;

    /**
     * \brief Переключиться на камеру с указанным именем, изображение которой
     * выводится в окне "Камера"
     *
     * В том случае, когда камера с указанным именем отсутствует, текущая камера
     * и имя камеры не изменяются. В том случае, когда имя камеры пустое, в качестве текущей
     * камеры устанавливается "устройство по умолчанию" (фиктивная камера).
     */
    void setCameraName(QString cameraName);

    /**
     * \brief Получить имя текущей камеры, изображение которой выводится в окне "Камера"
     */
    QString cameraName() const;

    /**
     * \brief Установить разрешение изображения, выводимого с текущей камеры
     *
     * В том случае, когда в списке доступных разрешений указанное разрешение отсутствует,
     * текущее разрешение не изменяется.
     */
    void setResolution(const QSize& resolution);

    /**
     * \brief Получить разрешение изображения, выводимого с текущей камеры
     */
    QSize resolution() const;

    /**
     * \brief Установить коэффициент масштабирования изображения камеры
     */
    void setZoom(qreal zoom);

    /**
     * \brief Получить коэффициент масштабирования изображения камеры
     */
    qreal zoom() const;

    /**
     * \brief Установить новые координаты сдвига видеокадра относительно окна виджета
     */
    void setPos(const QPoint &pos);

    /**
     * \brief Получить координаты сдвига видеокадра относительно окна виджета
     */
    QPoint pos() const;

    /**
     * \brief Установить смещение перекрестия прицельных линий
     */
    void setAimPos(const QPoint &aimPos);

    /**
     * \brief Получить смещение перекрестия прицельных линий
     */
    QPoint aimPos() const;

    /**
     * \brief Установить диаметр прицельной окружности
     */
    void setAimSize(int aimSize);

    /**
     * \brief Получить диаметр прицельной окружности
     */
    int aimSize() const;

    /**
     * \brief Установить толщину линий прицельных элементов
     */
    void setAimLineWidth(int aimLineWidth);

    /**
     * \brief Получить толщину линий прицельных элементов
     */
    int aimLineWidth() const;

    /**
     * \brief Установить цвет прицельных элементов
     */
    void setAimColor(int aimColor);

    /**
     * \brief Получить цвет прицельных элементов
     */
    int aimColor() const;

    /**
     * \brief Получить коэффициент масштабирования изображения камеры при отображении
     */
    qreal videoScale() const;

signals:

    /**
     * \brief Разрешение изображения, выводимого с текущей камеры, изменено
     */
    void resolutionChanged(const QSize &resolution);

    /**
     * \brief Координаты сдвига видеокадра изменены
     */
    void posChanged(const QPoint &pos);

    /**
     * \brief Относительное смещение (координаты) перекрестия прицельных линий изменено
     */
    void aimPosChanged(const QPoint &aimPos);

    /**
     * \brief Диаметр прицельной окружности изменён
     */
    void aimSizeChanged(int aimSize);

    /**
     * \brief Толщина линий прицельных элементов изменена
     */
    void aimLineWidthChanged(int aimLineWidth);

    /**
     * \brief Цвет прицельных элементов изменён
     */
    void aimColorChanged(int aimColor);

    /**
     * \brief Коэффициент масштабирования изображения камеры изменён
     */
    void zoomChanged(qreal zoom);

public slots:

    void start();

    void stop();

private slots:

    /**
     * \brief Проверка разрешений на использование камеры
     */
    static void permissionChecking();

private:

    QCamera *m_camera;

    QMediaCaptureSession *m_captureSession;

    myGraphicsView *m_view;

    QGraphicsVideoItem *m_item;

    QGraphicsScene *m_scene;

    QScrollArea *m_scrollArea;

    /**
     * \brief Наименование камеры, изображение которой выводится в окне "Камера"
     */
    QString m_cameraName;

    /**
     * \brief Разрешение изображения, выводимого с камеры
     */
    QSize m_resolution;

    /**
     * \brief Коэффициент масштабирования изображения камеры, задаваемый поворотом колёсика "мыши"
     */
    qreal m_zoom;

    /**
     * \brief Коэффициент масштабирования изображения камеры при отображении
     */
    qreal m_videoScale;

    /**
     * \brief Цвет прицельных элементов
     */
    int m_aimColor;

    /**
     * \brief Диаметр прицельной окружности
     */
    int m_aimSize;

    /**
     * \brief Толщина линий прицельных элементов
     */
    int m_aimLineWidth;

    /**
     * \brief Смещение перекрестия прицельных линий в координатах
     * окна виджета (прямоугольника, в который может выводиться видеоизображение)
     */
    QPoint m_aimPosition;

    void updateSize();

    void updateCameras();

    void updateCameraDevice(QAction *action);

    void setCamera(const QCameraDevice& cameraDevice);

    /**
     * \brief Обработчик события изменения размер виджета
     */
    virtual void resizeEvent(QResizeEvent *e) override;

    /**
     * \brief Обработчик события скрытия виджета
     */
    virtual void hideEvent(QHideEvent *e) override;

    /**
     * \brief Обработчик события показа виджета
     */
    virtual void showEvent(QShowEvent *e) override;
};

#endif
