#ifndef WRAPPER_QCOLOR_H
#define WRAPPER_QCOLOR_H

#include <QtCore/QObject>
#include <QtGui/QColor>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QColor : public wrapper_common {
  Q_OBJECT

  // Из файла qcolor.h
public:

  // constexpr QColor() noexcept
  Q_INVOKABLE wrapper_QColor() : wrapper_common(new QColor()) {
    qDebug() << "wrapper_QColor::constructor()";
  }
//    wrapper_QColor(Qt::GlobalColor color)
//    wrapper_QColor(int r, int g, int b, int a = 255)

  // QColor(QRgb rgb) noexcept;
  Q_INVOKABLE wrapper_QColor(QRgb rgb) :
    wrapper_common(new QColor(rgb)) {
    qDebug() << "wrapper_QColor::constructor(rgb)";
  }

#if 0
    QColor(QRgba64 rgba64) noexcept;
    inline QColor(const QString& name);
    explicit inline QColor(QStringView name);
    inline QColor(const char *aname);
    inline QColor(QLatin1StringView name);
    QColor(Spec spec) noexcept;

    static QColor fromString(QAnyStringView name) noexcept;

    QColor &operator=(Qt::GlobalColor color) noexcept;

    bool isValid() const noexcept;

    QString name(NameFormat format = HexRgb) const;

    static QStringList colorNames();

    inline Spec spec() const noexcept
    { return cspec; }

    int alpha() const noexcept;
    void setAlpha(int alpha);

    float alphaF() const noexcept;
    void setAlphaF(float alpha);

    int red() const noexcept;
    int green() const noexcept;
    int blue() const noexcept;
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    float redF() const noexcept;
    float greenF() const noexcept;
    float blueF() const noexcept;
    void setRedF(float red);
    void setGreenF(float green);
    void setBlueF(float blue);

    void getRgb(int *r, int *g, int *b, int *a = nullptr) const;
    void setRgb(int r, int g, int b, int a = 255);

    void getRgbF(float *r, float *g, float *b, float *a = nullptr) const;
    void setRgbF(float r, float g, float b, float a = 1.0);

    QRgba64 rgba64() const noexcept;
    void setRgba64(QRgba64 rgba) noexcept;

    QRgb rgba() const noexcept;
    void setRgba(QRgb rgba) noexcept;

    QRgb rgb() const noexcept;
    void setRgb(QRgb rgb) noexcept;

    int hue() const noexcept; // 0 <= hue < 360
    int saturation() const noexcept;
    int hsvHue() const noexcept; // 0 <= hue < 360
    int hsvSaturation() const noexcept;
    int value() const noexcept;

    float hueF() const noexcept; // 0.0 <= hueF < 360.0
    float saturationF() const noexcept;
    float hsvHueF() const noexcept; // 0.0 <= hueF < 360.0
    float hsvSaturationF() const noexcept;
    float valueF() const noexcept;

    void getHsv(int *h, int *s, int *v, int *a = nullptr) const;
    void setHsv(int h, int s, int v, int a = 255);

    void getHsvF(float *h, float *s, float *v, float *a = nullptr) const;
    void setHsvF(float h, float s, float v, float a = 1.0);

    int cyan() const noexcept;
    int magenta() const noexcept;
    int yellow() const noexcept;
    int black() const noexcept;

    float cyanF() const noexcept;
    float magentaF() const noexcept;
    float yellowF() const noexcept;
    float blackF() const noexcept;

    void getCmyk(int *c, int *m, int *y, int *k, int *a = nullptr) const;
    void setCmyk(int c, int m, int y, int k, int a = 255);

    void getCmykF(float *c, float *m, float *y, float *k, float *a = nullptr) const;
    void setCmykF(float c, float m, float y, float k, float a = 1.0);

    int hslHue() const noexcept; // 0 <= hue < 360
    int hslSaturation() const noexcept;
    int lightness() const noexcept;

    float hslHueF() const noexcept; // 0.0 <= hueF < 360.0
    float hslSaturationF() const noexcept;
    float lightnessF() const noexcept;

    void getHsl(int *h, int *s, int *l, int *a = nullptr) const;
    void setHsl(int h, int s, int l, int a = 255);

    void getHslF(float *h, float *s, float *l, float *a = nullptr) const;
    void setHslF(float h, float s, float l, float a = 1.0);

    QColor toRgb() const noexcept;
    QColor toHsv() const noexcept;
    QColor toCmyk() const noexcept;
    QColor toHsl() const noexcept;
    QColor toExtendedRgb() const noexcept;

    [[nodiscard]] QColor convertTo(Spec colorSpec) const noexcept;

    static QColor fromRgb(QRgb rgb) noexcept;
    static QColor fromRgba(QRgb rgba) noexcept;

    static QColor fromRgb(int r, int g, int b, int a = 255);
    static QColor fromRgbF(float r, float g, float b, float a = 1.0);

    static QColor fromRgba64(ushort r, ushort g, ushort b, ushort a = USHRT_MAX) noexcept;
    static QColor fromRgba64(QRgba64 rgba) noexcept;

    static QColor fromHsv(int h, int s, int v, int a = 255);
    static QColor fromHsvF(float h, float s, float v, float a = 1.0);

    static QColor fromCmyk(int c, int m, int y, int k, int a = 255);
    static QColor fromCmykF(float c, float m, float y, float k, float a = 1.0);

    static QColor fromHsl(int h, int s, int l, int a = 255);
    static QColor fromHslF(float h, float s, float l, float a = 1.0);

    [[nodiscard]] QColor lighter(int f = 150) const noexcept;
    [[nodiscard]] QColor darker(int f = 200) const noexcept;

    bool operator==(const QColor &c) const noexcept;
    bool operator!=(const QColor &c) const noexcept;

    operator QVariant() const;

    static bool isValidColorName(QAnyStringView) noexcept;

#endif

public:

  // Конструктор из объекта
  wrapper_QColor(QColor *self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QColor::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

//  // Копирующий конструктор
//  wrapper_QColor(const wrapper_QColor &obj) :
//    wrapper_common(static_cast<QColor*>((void*)obj.get_selfptr())) { }
    
  // Деструктор
  virtual ~wrapper_QColor() override {
    qDebug() << "wrapper_QColor::desctructor";
    delete static_cast<QColor*>(wrapper_common::get_selfptr());
  }

  // Получение константного указателя на объект
  const QColor* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QColor::get_selfptr - got nullptr";
    }
    return static_cast<const QColor*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QColor* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QColor::get_selfptr - got nullptr";
    }
    return static_cast<QColor*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QColor)

#endif // WRAPPER_QCOLOR_H
