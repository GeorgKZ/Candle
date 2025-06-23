#ifndef WRAPPER_QPUSHBUTTON_H
#define WRAPPER_QPUSHBUTTON_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "wrapper_QAbstractButton.h"

class WRAPPER_DLL_EXPORT wrapper_QPushButton : public wrapper_QAbstractButton {

  Q_OBJECT

  // из файла QPushButton.h

  Q_PROPERTY(bool autoDefault
      READ autoDefault
      WRITE setAutoDefault)
  Q_PROPERTY(bool default
      READ isDefault
      WRITE setDefault)
  Q_PROPERTY(bool flat
      READ isFlat
      WRITE setFlat)
    
public:

  // explicit QPushButton(QWidget *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QPushButton(wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractButton(new QPushButton(parent == nullptr ? nullptr : parent->get_selfptr())) {
      set_connections();
      qDebug() << "wrapper_QPushButton::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // explicit QPushButton(const QString &text, QWidget *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QPushButton(const QString &text, wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractButton(new QPushButton(text, parent == nullptr ? nullptr : parent->get_selfptr())) {
    set_connections();
    qDebug() << "wrapper_QPushButton::constructor(text, parent)";
  }

  // QPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
  Q_INVOKABLE wrapper_QPushButton(const QJSValue& icon, const QString &text, wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractButton(new QPushButton(*(QIcon*)jsvalueToObject_ptr("QIcon", icon), text, parent == nullptr ? nullptr : parent->get_selfptr())) {
    set_connections();
    qDebug() << "wrapper_QPushButton::constructor(icon, text, parent)";
  }


  // QSize sizeHint() const
  Q_INVOKABLE QJSValue sizeHint() const {
    QSize *size = new QSize(get_selfptr()->sizeHint());
    return wrapperFactory("QSize", size);
  }

  // QSize minimumSizeHint()
  Q_INVOKABLE QJSValue minimumSizeHint() const {
    QSize *size = new QSize(get_selfptr()->minimumSizeHint());
    return wrapperFactory("QSize", size);
  }

  // bool autoDefault() const;
  Q_INVOKABLE bool autoDefault() const { return get_selfptr()->autoDefault(); }

  // void setAutoDefault(bool);
  Q_INVOKABLE void setAutoDefault(bool autodefault) { get_selfptr()->setAutoDefault(autodefault); }

  // bool isDefault() const;
  Q_INVOKABLE bool isDefault() const { return get_selfptr()->isDefault(); }

  // void setDefault(bool);
  Q_INVOKABLE void setDefault(bool def) { get_selfptr()->setDefault(def); }

#if QT_CONFIG(menu)
//!!!  Q_INVOKABLE void setMenu(QMenu* menu);
//!!!  Q_INVOKABLE QMenu* menu() const;
#endif

  // void setFlat(bool);
  Q_INVOKABLE void setFlat(bool flat) { get_selfptr()->setFlat(flat); }

  // bool isFlat() const;
  Q_INVOKABLE bool isFlat() const { return get_selfptr()->isFlat(); }

public Q_SLOTS:

#if QT_CONFIG(menu)
  // void showMenu();
  void showMenu() { get_selfptr()->showMenu(); }
#endif

private:

    /**
     * \brief Соединения изменения объекта с сигналом прокси-класса
     */
    void set_connections()
    {
    }

public:

  // Конструктор из объекта
  wrapper_QPushButton(QPushButton *self) :
    wrapper_QAbstractButton(self) {
    set_connections();
    qDebug() << "wrapper_QPushButton::constructor(self=" << (unsigned long long)self << ")";
  }

  // Получение константного указателя на объект
  const QPushButton* get_selfptr() const {
    if (wrapper_QAbstractButton::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPushButton::get_selfptr - got nullptr";
    }
    return static_cast<const QPushButton*>(wrapper_QAbstractButton::get_selfptr());
  }

  // Получение указателя на объект
  QPushButton* get_selfptr() {
    if (wrapper_QAbstractButton::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QPushButton::get_selfptr - got nullptr";
    }
    return static_cast<QPushButton*>(wrapper_QAbstractButton::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QPushButton() {
    qDebug() << "wrapper_QPushButton::descructor";
  }
};

Q_DECLARE_METATYPE(wrapper_QPushButton);

#endif // WRAPPER_QPUSHBUTTON_H
