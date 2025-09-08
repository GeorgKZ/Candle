#ifndef WRAPPER_QABSTRACTBUTTON_H
#define WRAPPER_QABSTRACTBUTTON_H

#include <QObject>
#include <QJSValue>
#include <QAbstractButton>
#include "wrapper_QWidget.h"
#include "wrapper_QIcon.h"
#include "wrapper_QSize.h"

class WRAPPER_DLL_EXPORT wrapper_QAbstractButton : public wrapper_QWidget {

  Q_OBJECT

  // Из файла qabstractbutton.h
    Q_PROPERTY(QString text           READ text               WRITE setText)
    Q_PROPERTY(QJSValue icon          READ icon               WRITE setIcon)
    Q_PROPERTY(QJSValue iconSize      READ iconSize           WRITE setIconSize)
#ifndef QT_NO_SHORTCUT
//!!! wrapper?
    Q_PROPERTY(QKeySequence shortcut  READ shortcut           WRITE setShortcut)
#endif
    Q_PROPERTY(bool checkable         READ isCheckable        WRITE setCheckable)
    Q_PROPERTY(bool checked           READ isChecked          WRITE setChecked             NOTIFY toggled USER true)
    Q_PROPERTY(bool autoRepeat        READ autoRepeat         WRITE setAutoRepeat)
    Q_PROPERTY(bool autoExclusive     READ autoExclusive      WRITE setAutoExclusive)
    Q_PROPERTY(int autoRepeatDelay    READ autoRepeatDelay    WRITE setAutoRepeatDelay)
    Q_PROPERTY(int autoRepeatInterval READ autoRepeatInterval WRITE setAutoRepeatInterval)
    Q_PROPERTY(bool down              READ isDown             WRITE setDown                DESIGNABLE false)

public:

  Q_INVOKABLE explicit wrapper_QAbstractButton(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(parent == nullptr ? nullptr : parent->get_selfptr()) {
    setConnections();
    qDebug() << "wrapper_QAbstractButton::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  Q_INVOKABLE void setText(const QString &text) { get_selfptr()->setText(text); }
  Q_INVOKABLE QString text() const { return get_selfptr()->text(); }


// usercommands/script.js: w.icon = t.item(i, 1).data(Qt.DecorationRole);

  // void setIcon(const QIcon &icon)
  Q_INVOKABLE void setIcon(const QJSValue &value) {
//!!!TODO!!! Если иконки нет, валится!
    QIcon icon(*jsvalueToPointer(QIcon, value));
    get_selfptr()->setIcon(icon);
  }

  // QIcon icon()
  Q_INVOKABLE QJSValue icon() const {
    QIcon *icon = new QIcon(get_selfptr()->icon());
    return PointerToJsvalueMacro(QIcon, icon);
  }

  // QSize iconSize()
  Q_INVOKABLE QJSValue iconSize() const {
    QSize *size = new QSize(get_selfptr()->iconSize());
    return PointerToJsvalueMacro(QSize, size);
  }

#ifndef QT_NO_SHORTCUT
//!!! wrapper_QKeySequence?
  Q_INVOKABLE void setShortcut(const QKeySequence &key) { get_selfptr()->setShortcut(key); }
//!!! wrapper_QKeySequence?
  Q_INVOKABLE QKeySequence shortcut() const { return get_selfptr()->shortcut(); }
#endif

  Q_INVOKABLE void setCheckable(bool checkable) { get_selfptr()->setCheckable(checkable); }
  Q_INVOKABLE bool isCheckable() const { return get_selfptr()->isCheckable(); }

  Q_INVOKABLE bool isChecked() const { return get_selfptr()->isChecked(); }

  Q_INVOKABLE void setDown(bool down) { get_selfptr()->setDown(down); }
  Q_INVOKABLE bool isDown() const { return get_selfptr()->isDown(); }

  Q_INVOKABLE void setAutoRepeat(bool autorepeat) { return get_selfptr()->setAutoRepeat(autorepeat); }
  Q_INVOKABLE bool autoRepeat() const { return get_selfptr()->autoRepeat(); }

  Q_INVOKABLE void setAutoRepeatDelay(int delay) { return get_selfptr()->setAutoRepeatDelay(delay); }
  Q_INVOKABLE int autoRepeatDelay() const { return get_selfptr()->autoRepeatDelay(); }

  Q_INVOKABLE void setAutoRepeatInterval(int interval) { return get_selfptr()->setAutoRepeatInterval(interval); }
  Q_INVOKABLE int autoRepeatInterval() const { return get_selfptr()->autoRepeatInterval(); }

  Q_INVOKABLE void setAutoExclusive(bool autoexclusive) { get_selfptr()->setAutoExclusive(autoexclusive); }
  Q_INVOKABLE bool autoExclusive() const { return get_selfptr()->autoExclusive(); }

#if QT_CONFIG(buttongroup)
//!!! wrapper_QButtonGroup?
  Q_INVOKABLE QButtonGroup *group() const { return get_selfptr()->group(); }
#endif

public Q_SLOTS:

  // void setIconSize(const QSize &size)
  Q_INVOKABLE void setIconSize(const QJSValue &value_size) {
    QSize *size = jsvalueToPointer(QSize, value_size);
    qDebug() << "QAbstractButton::setIconSize(): size =" << *size;
    get_selfptr()->setIconSize(*size);
  }

  Q_INVOKABLE void animateClick() {
    get_selfptr()->animateClick();
  }

  Q_INVOKABLE void click() {
    get_selfptr()->click();
  }

  Q_INVOKABLE void toggle() {
    get_selfptr()->toggle();
  }

  Q_INVOKABLE void setChecked(bool checked) {
    get_selfptr()->setChecked(checked);
  }

Q_SIGNALS:

    void pressed();
    void released();
    void clicked(bool checked = false);
    void toggled(bool checked);

private:

    /**
     * \brief Соединения изменения объекта с сигналом прокси-класса
     */
    void setConnections()
    {
        QObject::connect(get_selfptr(),
          &QAbstractButton::clicked,
          [=](){emit clicked();});
    }

public:

  // Конструктор из объекта
  wrapper_QAbstractButton(void *self) : wrapper_QWidget(self) {
    setConnections();
    qDebug() << "wrapper_QAbstractButton::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QAbstractButton* get_selfptr() const {
    return static_cast<const QAbstractButton*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QAbstractButton* get_selfptr() {
    return static_cast<QAbstractButton*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QAbstractButton() override {
    qDebug() << "wrapper_QAbstractButton::destructor";
  }
};

Q_DECLARE_METATYPE(wrapper_QAbstractButton)

#endif // WRAPPER_QABSTRACTBUTTON_H
