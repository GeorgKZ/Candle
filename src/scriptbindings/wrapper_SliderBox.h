#ifndef WRAPPER_SLIDERBOX_H
#define WRAPPER_SLIDERBOX_H

#include <QtCore/QObject>
#include "sliderbox.h"
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_SliderBox : public wrapper_QWidget {

  Q_OBJECT

  // Из файла SliderBox.h
  Q_PROPERTY(int value
             READ value
             WRITE setValue)
  Q_PROPERTY(int currentValue
             READ currentValue
             WRITE setCurrentValue)
  Q_PROPERTY(int sliderPosition
             READ sliderPosition
             WRITE setSliderPosition)
  Q_PROPERTY(bool isCheckable
             READ isCheckable
             WRITE setCheckable)
  Q_PROPERTY(bool isChecked
             READ isChecked
             WRITE setChecked)
  Q_PROPERTY(int ratio
             READ ratio
             WRITE setRatio)
  Q_PROPERTY(int minimum
             READ minimum
             WRITE setMinimum)
  Q_PROPERTY(int maximum
             READ maximum
             WRITE setMaximum)
  Q_PROPERTY(QString suffix
             READ suffix
             WRITE setSuffix)
  Q_PROPERTY(QString title
             READ title
             WRITE setTitle)

public:

  Q_INVOKABLE explicit wrapper_SliderBox(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(new SliderBox(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_SliderBox::constructor(parent)";
  }

  // int value() const;
  Q_INVOKABLE int value() const {
    return get_selfptr()->currentValue();
  }

  // void setValue(int value);
  Q_INVOKABLE void setValue(int value) {
    get_selfptr()->setValue(value);
  }

  // int currentValue() const;
  Q_INVOKABLE int currentValue() const {
    return get_selfptr()->currentValue();
  }

  // void setCurrentValue(int currentValue);
  Q_INVOKABLE void setCurrentValue(int currentValue) {
    get_selfptr()->setCurrentValue(currentValue);
  }

  //int sliderPosition() const;
  Q_INVOKABLE int sliderPosition() const { return get_selfptr()->sliderPosition(); }

  //void setSliderPosition(int position);
  Q_INVOKABLE void setSliderPosition(int position) { get_selfptr()->setSliderPosition(position); }

  //bool isCheckable() const;
  Q_INVOKABLE bool isCheckable() const { return get_selfptr()->isCheckable(); }

  //void setCheckable(bool checkable);
  Q_INVOKABLE void setCheckable(bool checkable) { get_selfptr()->setCheckable(checkable); }

  // bool isChecked() const;
  Q_INVOKABLE bool isChecked() const { return get_selfptr()->isChecked(); }

  // void setChecked(bool checked);
  Q_INVOKABLE void setChecked(bool checked) { get_selfptr()->setChecked(checked); }

  // int ratio() const;
  Q_INVOKABLE int ratio() const { return get_selfptr()->ratio(); }

  // void setRatio(int ratio);
  Q_INVOKABLE void setRatio(int ratio) { get_selfptr()->setRatio(ratio); }

  // int minimum() const;
  Q_INVOKABLE int minimum() const { return get_selfptr()->minimum(); }

  // void setMinimum(int minimum);
  Q_INVOKABLE void setMinimum(int minimum) { get_selfptr()->setMinimum(minimum); }

  // int maximum() const;
  Q_INVOKABLE int maximum() const { return get_selfptr()->maximum(); }

  // void setMaximum(int maximum);
  Q_INVOKABLE void setMaximum(int maximum) { get_selfptr()->setMaximum(maximum); }

  // QString suffix() const;
  Q_INVOKABLE QString suffix() const { return get_selfptr()->suffix(); }

  // void setSuffix(QString suffix);
  Q_INVOKABLE void setSuffix(QString suffix) { get_selfptr()->setSuffix(suffix); }

  // QString title() const;
  Q_INVOKABLE QString title() const { return get_selfptr()->title(); }

  // void setTitle(QString title);
  Q_INVOKABLE void setTitle(QString title) { get_selfptr()->setTitle(title); }

public slots:

  // void click()
  Q_INVOKABLE void click() { get_selfptr()->click(); }

signals:

  void valueUserChanged();

  void valueChanged();

  void toggled(bool checked);

public:

  // Конструктор из объекта
  wrapper_SliderBox(void *self) : wrapper_QWidget(self) {
    qDebug() << "wrapper_SliderBox::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const SliderBox* get_selfptr() const {
    return static_cast<const SliderBox*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  SliderBox* get_selfptr() {
    return static_cast<SliderBox*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_SliderBox() override {
    qDebug() << "wrapper_SliderBox::destructor";
  }
};

Q_DECLARE_METATYPE(wrapper_SliderBox)

#endif // WRAPPER_SLIDERBOX_H
