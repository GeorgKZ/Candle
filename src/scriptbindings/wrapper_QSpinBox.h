#ifndef WRAPPER_QSPINBOX_H
#define WRAPPER_QSPINBOX_H

#include <QtWidgets/QSpinBox>
#include "wrapper_QAbstractSpinBox.h"

class wrapper_QSpinBox : public wrapper_QAbstractSpinBox
{
    Q_OBJECT

#if 0
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString cleanText READ cleanText)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(StepType stepType READ stepType WRITE setStepType)
#endif
    Q_PROPERTY(int value
        READ value
        WRITE setValue
        NOTIFY valueChanged
        USER true)
#if 0
    Q_PROPERTY(int displayIntegerBase READ displayIntegerBase WRITE setDisplayIntegerBase)
#endif

public:

#if 0
    explicit QSpinBox(QWidget *parent = nullptr);
#endif
    // int value() const
    Q_INVOKABLE int value() const
    {
        return get_selfptr()->value();
    }
#if 0
    QString prefix() const;
    void setPrefix(const QString &prefix);

    QString suffix() const;
    void setSuffix(const QString &suffix);

    QString cleanText() const;

    int singleStep() const;
    void setSingleStep(int val);

    int minimum() const;
    void setMinimum(int min);

    int maximum() const;
    void setMaximum(int max);

    void setRange(int min, int max);

    StepType stepType() const;
    void setStepType(StepType stepType);

    int displayIntegerBase() const;
    void setDisplayIntegerBase(int base);
#endif

public Q_SLOTS:

    // void setValue(int val)
    Q_INVOKABLE void setValue(int val)
    {
        get_selfptr()->setValue(val);
    }

Q_SIGNALS:

    void valueChanged(int);

    void textChanged(const QString &);

    public:

    // Конструктор из объекта
    wrapper_QSpinBox(QSpinBox *self) :
        wrapper_QAbstractSpinBox(self) {
        qDebug() << "wrapper_QSpinBox::constructor(self=" << (unsigned long long)self << ")";
    }

    // Получение константного указателя на объект
    const QSpinBox* get_selfptr() const {
        if (wrapper_QAbstractSpinBox::get_selfptr() == nullptr) {
            qCritical() << "wrapper_QSpinBox::get_selfptr - got nullptr";
        }
        return static_cast<const QSpinBox*>(wrapper_QAbstractSpinBox::get_selfptr());
    }

    // Получение указателя на объект
    QSpinBox* get_selfptr() {
        if (wrapper_QAbstractSpinBox::get_selfptr() == nullptr) {
            qCritical() << "wrapper_QSpinBox::get_selfptr - got nullptr";
        }
        return static_cast<QSpinBox*>(wrapper_QAbstractSpinBox::get_selfptr());
    }

    // Деструктор
    virtual ~wrapper_QSpinBox() {
        qDebug() << "wrapper_QSpinBox::destructor";
    }
};

class wrapper_QDoubleSpinBox : public wrapper_QAbstractSpinBox
{
    Q_OBJECT
#if 0
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(QString cleanText READ cleanText)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(StepType stepType READ stepType WRITE setStepType)
#endif
    Q_PROPERTY(double value
        READ value
        WRITE setValue
        NOTIFY valueChanged
        USER true)

public:

#if 0
    explicit QDoubleSpinBox(QWidget *parent = nullptr);

#endif
    // double value() const
    Q_INVOKABLE double value() const
    {
        return get_selfptr()->value();
    }
#if 0

    QString prefix() const;
    void setPrefix(const QString &prefix);

    QString suffix() const;
    void setSuffix(const QString &suffix);

    QString cleanText() const;

    double singleStep() const;
    void setSingleStep(double val);

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setRange(double min, double max);

    StepType stepType() const;
    void setStepType(StepType stepType);

    int decimals() const;
    void setDecimals(int prec);

    QValidator::State validate(QString &input, int &pos) const override;
    virtual double valueFromText(const QString &text) const;
    virtual QString textFromValue(double val) const;
    void fixup(QString &str) const override;
#endif

public Q_SLOTS:

    // void setValue(double val)
    Q_INVOKABLE void setValue(double val)
    {
        get_selfptr()->setValue(val);
    }

Q_SIGNALS:

    void valueChanged(double);

    void textChanged(const QString &);

    public:

    // Конструктор из объекта
    wrapper_QDoubleSpinBox(QDoubleSpinBox *self) :
        wrapper_QAbstractSpinBox(self) {
        qDebug() << "wrapper_QDoubleSpinBox::constructor(self=" << (unsigned long long)self << ")";
    }

    // Получение константного указателя на объект
    const QDoubleSpinBox* get_selfptr() const {
        if (wrapper_QAbstractSpinBox::get_selfptr() == nullptr) {
            qCritical() << "wrapper_QDoubleSpinBox::get_selfptr - got nullptr";
        }
        return static_cast<const QDoubleSpinBox*>(wrapper_QAbstractSpinBox::get_selfptr());
    }

    // Получение указателя на объект
    QDoubleSpinBox* get_selfptr() {
        if (wrapper_QAbstractSpinBox::get_selfptr() == nullptr) {
            qCritical() << "wrapper_QDoubleSpinBox::get_selfptr - got nullptr";
        }
        return static_cast<QDoubleSpinBox*>(wrapper_QAbstractSpinBox::get_selfptr());
    }

    // Деструктор
    virtual ~wrapper_QDoubleSpinBox() {
        qDebug() << "wrapper_QDoubleSpinBox::destructor";
    }
};

#endif // WRAPPER_QSPINBOX_H
