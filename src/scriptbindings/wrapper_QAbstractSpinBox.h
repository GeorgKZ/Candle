#ifndef WRAPPER_QABSTRACTSPOINBOX_H
#define WRAPPER_QABSTRACTSPOINBOX_H

#include <QtCore/QObject>
#include <QtWidgets/QAbstractSpinBox>
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QAbstractSpinBox : public wrapper_QWidget {

  Q_OBJECT

    Q_PROPERTY(bool wrapping
        READ wrapping
        WRITE setWrapping)
    Q_PROPERTY(bool frame
        READ hasFrame
        WRITE setFrame)
    Q_PROPERTY(Qt::Alignment alignment
        READ alignment
        WRITE setAlignment)
    Q_PROPERTY(bool readOnly
        READ isReadOnly
        WRITE setReadOnly)
    Q_PROPERTY(ButtonSymbols buttonSymbols
        READ buttonSymbols
        WRITE setButtonSymbols)
    Q_PROPERTY(QString specialValueText
        READ specialValueText
        WRITE setSpecialValueText)
    Q_PROPERTY(QString text
        READ text)
    Q_PROPERTY(bool accelerated
        READ isAccelerated
        WRITE setAccelerated)
    Q_PROPERTY(CorrectionMode correctionMode
        READ correctionMode
        WRITE setCorrectionMode)
    Q_PROPERTY(bool acceptableInput
        READ hasAcceptableInput)
    Q_PROPERTY(bool keyboardTracking
        READ keyboardTracking
        WRITE setKeyboardTracking)
    Q_PROPERTY(bool showGroupSeparator
        READ isGroupSeparatorShown
        WRITE setGroupSeparatorShown)

public:

  // Из файла QAbstractSpinBox.h

  enum StepEnabledFlag {
    StepNone = 0x00,
    StepUpEnabled = 0x01,
    StepDownEnabled = 0x02
  };
  Q_DECLARE_FLAGS(StepEnabled, StepEnabledFlag)

  enum ButtonSymbols {
    UpDownArrows,
    PlusMinus,
    NoButtons
  };
  Q_ENUM(ButtonSymbols)

    Q_INVOKABLE ButtonSymbols buttonSymbols() const
    {
        return (ButtonSymbols)(int)get_selfptr()->buttonSymbols();
    }

    Q_INVOKABLE void setButtonSymbols(ButtonSymbols bs)
    {
        get_selfptr()->setButtonSymbols((QAbstractSpinBox::ButtonSymbols)(int)bs);
    } 

    enum CorrectionMode {
      CorrectToPreviousValue,
      CorrectToNearestValue
    };
    Q_ENUM(CorrectionMode)

    Q_INVOKABLE void setCorrectionMode(CorrectionMode cm)
    {
        get_selfptr()->setCorrectionMode((QAbstractSpinBox::CorrectionMode)(int)cm);
    }

    Q_INVOKABLE CorrectionMode correctionMode() const
    {
        return (CorrectionMode)(int)get_selfptr()->correctionMode();
    }

    Q_INVOKABLE bool hasAcceptableInput() const
    {
        return get_selfptr()->hasAcceptableInput();
    }

    Q_INVOKABLE QString text() const
    {
        return get_selfptr()->text();
    }

    Q_INVOKABLE QString specialValueText() const
    {
        return get_selfptr()->specialValueText();
    }

    Q_INVOKABLE void setSpecialValueText(const QString &txt)
    {
        get_selfptr()->setSpecialValueText(txt);
    }

    Q_INVOKABLE bool wrapping() const
    {
        return get_selfptr()->wrapping();
    }

    Q_INVOKABLE void setWrapping(bool w)
    {
        get_selfptr()->setWrapping(w);
    }

    Q_INVOKABLE void setReadOnly(bool r)
    {
        get_selfptr()->setReadOnly(r);
    }

    Q_INVOKABLE bool isReadOnly() const
    {
        return get_selfptr()->isReadOnly();
    }

    Q_INVOKABLE void setKeyboardTracking(bool kt)
    {
        get_selfptr()->setKeyboardTracking(kt);
    }

    Q_INVOKABLE bool keyboardTracking() const
    {
        return get_selfptr()->keyboardTracking();
    }

    Q_INVOKABLE void setAlignment(Qt::Alignment flag)
    {
        get_selfptr()->setAlignment(flag);
    }

    Q_INVOKABLE Qt::Alignment alignment() const
    {
        return get_selfptr()->alignment();
    }

    Q_INVOKABLE void setFrame(bool frame)
    {
        get_selfptr()->setFrame(frame);
    }

    Q_INVOKABLE bool hasFrame() const
    {
        return get_selfptr()->hasFrame();
    }

    Q_INVOKABLE void setAccelerated(bool on)
    {
        get_selfptr()->setAccelerated(on);
    }

    Q_INVOKABLE bool isAccelerated() const
    {
        return get_selfptr()->isAccelerated();
    }

    // void setGroupSeparatorShown(bool shown)
    Q_INVOKABLE void setGroupSeparatorShown(bool shown)
    {
        get_selfptr()->setGroupSeparatorShown(shown);
    }

    // bool isGroupSeparatorShown() const
    Q_INVOKABLE bool isGroupSeparatorShown() const
    {
        return get_selfptr()->isGroupSeparatorShown();
    }

    // virtual QSize sizeHint() const override;
    Q_INVOKABLE QJSValue sizeHint() const override
    {
        return wrapperFactory("QSize", new QSize(get_selfptr()->sizeHint()));
    }

    // virtual QSize minimumSizeHint() const override;
    Q_INVOKABLE QJSValue minimumSizeHint() const override
    {
        return wrapperFactory("QSize", new QSize(get_selfptr()->minimumSizeHint()));
    }

#if 0
  Q_INVOKABLE void interpretText();

  Q_INVOKABLE bool event(QEvent *event) override;

  Q_INVOKABLE QVariant inputMethodQuery(Qt::InputMethodQuery) const; //!!! override;

  Q_INVOKABLE virtual QValidator::State validate(QString &input, int &pos) const;
  Q_INVOKABLE virtual void fixup(QString &input) const;

  Q_INVOKABLE virtual void stepBy(int steps);
#endif

  enum StepType {
    DefaultStepType,
    AdaptiveDecimalStepType
  };
  Q_ENUM(StepType)

public Q_SLOTS:

    Q_INVOKABLE void stepUp()
    {
        get_selfptr()->stepUp();
    }

    Q_INVOKABLE void stepDown()
    {
        get_selfptr()->stepDown();
    }

    Q_INVOKABLE void selectAll()
    {
        get_selfptr()->selectAll();
    }

    Q_INVOKABLE virtual void clear()
    {
        get_selfptr()->clear();
    }

Q_SIGNALS:

  void editingFinished();

private:

public:

  // Конструктор из объекта
  wrapper_QAbstractSpinBox(QAbstractSpinBox *self) : wrapper_QWidget(self) {
    qDebug() << "QAbstractSpinBox::copy_constructor";
  }

  // Деструктор
  virtual ~wrapper_QAbstractSpinBox() {
    qDebug() << "QAbstractSpinBox::destructor";
  }

  // Получение константного указателя на объект
  virtual const QAbstractSpinBox* get_selfptr() const {
    return static_cast<const QAbstractSpinBox*>(wrapper_QWidget::get_selfptr());
   }

  // Получение указателя на объект
  virtual QAbstractSpinBox* get_selfptr() {
    return static_cast<QAbstractSpinBox*>(wrapper_QWidget::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QAbstractSpinBox);

#endif // WRAPPER_QABSTRACTSPOINBOX_H
