/**
 * \file
 * \brief Заголовочный файл с объявлением классов \ref myGraphicsView "myGraphicsView" и \ref CameraWidget "CameraWidget"
 */

#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QGraphicsView>
#include "customwidgetsshared.h"

class QScrollArea;
class QCamera;
class QCameraDevice;
class QGraphicsVideoItem;
class QMediaCaptureSession;
class CameraWidget;

/**
 * \brief Объявление класса виджета камеры \ref myGraphicsView "myGraphicsView"
 */
class myGraphicsView: public QGraphicsView
{

public:
 
    /**
     * \brief Конструктор
     *
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

    /**
     * \property availableCameras
     * Список доступных камер
     */
    Q_PROPERTY(QStringList availableCameras
        READ availableCameras)
    /**
     * \property availableResolutions
     * Список доступных разрешений
     */
    Q_PROPERTY(QStringList availableResolutions
        READ availableResolutions)
    /**
     * \property cameraName
     * Имя камеры
     */
    Q_PROPERTY(QString cameraName
        READ cameraName
        WRITE setCameraName)
    /**
     * \property resolution
     * Текущее разрешение камеры
     */
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
    /**
     * \property aimPos
     * Смещение перекрестия прицельных линий
     */
    Q_PROPERTY(QPoint aimPos
        READ aimPos
        WRITE setAimPos
        NOTIFY aimPosChanged
        STORED false)
    /**
     * \property aimSize
     * диаметр прицельной окружности
     */
    Q_PROPERTY(int aimSize
        READ aimSize
        WRITE setAimSize
        NOTIFY aimSizeChanged)
    /**
     * \property aimLineWidth
     * толщина линий прицельных элементов
     */
    Q_PROPERTY(int aimLineWidth
        READ aimLineWidth
        WRITE setAimLineWidth
        NOTIFY aimLineWidthChanged)
    /**
     * \property aimColor
     * цвет прицельных элементов
     */
    Q_PROPERTY(int aimColor
        READ aimColor
        WRITE setAimColor
        NOTIFY aimColorChanged)

public:

    /**
     * \brief Конструктор
     *
     * \param [in] parent Родительский объект
     */
    CameraWidget(QWidget *parent = nullptr);

    /**
     * \brief Деструктор
     */
    virtual ~CameraWidget() override;

    /**
     * \brief Проверить, работает ли текущая камера
     *
     * \retval true если камера работает
     * \retval false если камера не работает
     */
    bool isCameraActive() const;

    /**
     * \brief Получить список имён доступных камер
     *
     * \return список имён доступных камер
     */
    QStringList availableCameras() const;

    /**
     * \brief Получить список поддерживаемых разрешений текущей камеры
     *
     * \return список поддерживаемых разрешений текущей камеры
     */
    QStringList availableResolutions() const;

    /**
     * \brief Переключиться на камеру с указанным именем
     *
     * \details
     * В том случае, когда камера с указанным именем отсутствует, текущая камера
     * и имя камеры не изменяются. В том случае, когда имя камеры пустое, в качестве текущей
     * камеры устанавливается "устройство по умолчанию" (фиктивная камера).
     *
     * \param [in] cameraName имя камеры, на которую надо переключиться
     */
    void setCameraName(QString cameraName);

    /**
     * \brief Получить имя текущей камеры, изображение которой выводится в окне "Камера"
     *
     * \return имя текущей камеры, изображение которой выводится в окне "Камера"
     */
    QString cameraName() const;

    /**
     * \brief Установить разрешение изображения, выводимого с текущей камеры
     *
     * \param [in] resolution разрешение камеры, которое требуется установить
     *
     * В том случае, когда в списке доступных разрешений указанное разрешение отсутствует,
     * текущее разрешение не изменяется.
     */
    void setResolution(const QSize& resolution);

    /**
     * \brief Получить разрешение изображения, выводимого с текущей камеры
     *
     * \return разрешение изображения, выводимого с текущей камеры
     */
    QSize resolution() const;

    /**
     * \brief Установить коэффициент масштабирования изображения камеры
     *
     * \param [in] zoom коэффициент масштабирования изображения камеры, который требуется установить
     */
    void setZoom(qreal zoom);

    /**
     * \brief Получить коэффициент масштабирования изображения камеры
     *
     * \return коэффициент масштабирования изображения камеры
     */
    qreal zoom() const;

    /**
     * \brief Установить новые координаты сдвига видеокадра относительно окна виджета
     *
     * \param [in] pos координаты сдвига видеокадра относительно окна виджета, которые требуется установить
     */
    void setPos(const QPoint &pos);

    /**
     * \brief Получить координаты сдвига видеокадра относительно окна виджета
     *
     * \return координаты сдвига видеокадра относительно окна виджета
     */
    QPoint pos() const;

    /**
     * \brief Установить смещение перекрестия прицельных линий
     *
     * \param [in] aimPos смещение перекрестия прицельных линий, которое требуется установить
     */
    void setAimPos(const QPoint &aimPos);

    /**
     * \brief Получить смещение перекрестия прицельных линий
     *
     * \return смещение перекрестия прицельных линий
     */
    QPoint aimPos() const;

    /**
     * \brief Установить диаметр прицельной окружности
     *
     * \param [in] aimSize диаметр прицельной окружности, который требуется установить
     */
    void setAimSize(int aimSize);

    /**
     * \brief Получить диаметр прицельной окружности
     *
     * \return диаметр прицельной окружности
     */
    int aimSize() const;

    /**
     * \brief Установить толщину линий прицельных элементов
     *
     * \param [in] aimLineWidth толщина линий прицельных элементов, которую требуется установить
     */
    void setAimLineWidth(int aimLineWidth);

    /**
     * \brief Получить толщину линий прицельных элементов
     *
     * \return толщину линий прицельных элементов
     */
    int aimLineWidth() const;

    /**
     * \brief Установить цвет прицельных элементов
     *
     * \param [in] aimColor цвет прицельных элементов, который требуется установить
     */
    void setAimColor(int aimColor);

    /**
     * \brief Получить цвет прицельных элементов
     *
     * \return цвет прицельных элементов
     */
    int aimColor() const;

    /**
     * \brief Получить коэффициент масштабирования изображения камеры при отображении
     *
     * \return коэффициент масштабирования изображения камеры при отображении
     */
    qreal videoScale() const;

signals:

    /**
     * \brief Сигнал изменения разрешения изображения, выводимого с текущей камеры
     */
    void resolutionChanged(const QSize &resolution);

    /**
     * \brief Сигнал изменения координат сдвига видеокадра
     */
    void posChanged(const QPoint &pos);

    /**
     * \brief Сигнал изменения относительного смещения (координат) перекрестия прицельных линий
     */
    void aimPosChanged(const QPoint &aimPos);

    /**
     * \brief Сигнал изменения диаметра прицельной окружности
     */
    void aimSizeChanged(int aimSize);

    /**
     * \brief Сигнал изменения толщины линий прицельных элементов
     */
    void aimLineWidthChanged(int aimLineWidth);

    /**
     * \brief Сигнал изменения цвета прицельных элементов
     */
    void aimColorChanged(int aimColor);

    /**
     * \brief Сигнал изменения коэффициента масштабирования изображения камеры
     */
    void zoomChanged(qreal zoom);

public slots:

    /**
     * \brief Слот начала работы камеры
     */
    void start();

    /**
     * \brief Слот остановки работы камеры
     */
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

    /**
     * \brief Вычислить и установить новый коэффициент масштабирования
     * изображения камеры при отображении на основе масштаба
     */
    void updateSize();

//    void updateCameras();

//    void updateCameraDevice(QAction *action);

    /**
     * \brief Переключиться но новую камеру по ссылке на [QCameraDevice](https://doc.qt.io/qt-6/qcameradevice.html)
     * \param [in] cameraDevice ссылка на [QCameraDevice](https://doc.qt.io/qt-6/qcameradevice.html)
     */
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

Q_DECLARE_METATYPE(CameraWidget)

#endif
