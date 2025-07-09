#ifndef WRAPPER_QTOOLBUTTON_H
#define WRAPPER_QTOOLBUTTON_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <QtWidgets/QToolButton>
#include "wrapper_QAbstractButton.h"

class WRAPPER_DLL_EXPORT wrapper_QToolButton : public wrapper_QAbstractButton {

  Q_OBJECT

  // из файла QToolButton.h

  Q_ENUMS(Qt::ToolButtonStyle Qt::ArrowType)

#if QT_CONFIG(menu)
  Q_PROPERTY(ToolButtonPopupMode popupMode       READ popupMode       WRITE setPopupMode)
#endif

  Q_PROPERTY(Qt::ToolButtonStyle toolButtonStyle READ toolButtonStyle WRITE setToolButtonStyle)
  Q_PROPERTY(bool                autoRaise       READ autoRaise       WRITE setAutoRaise)
  Q_PROPERTY(Qt::ArrowType       arrowType       READ arrowType       WRITE setArrowType)
    
public:

  enum ToolButtonPopupMode {
    DelayedPopup,
    MenuButtonPopup,
    InstantPopup
  };
  Q_ENUM(ToolButtonPopupMode)

  // explicit QToolButton(QWidget *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QToolButton(wrapper_QWidget *parent = nullptr) :
    wrapper_QAbstractButton(new QToolButton(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QToolButton::constructor(parent=" << (parent == nullptr ? 0 : reinterpret_cast<unsigned long long>(parent->get_selfptr())) << ")";
  }

  // QSize sizeHint() const
  Q_INVOKABLE virtual QJSValue sizeHint() const override {
    QSize *size = new QSize(get_selfptr()->sizeHint());
//  return wrapperFactory("QSize", size);
    return PointerToJsvalue(QSize, size);
  }

  // QSize minimumSizeHint()
  Q_INVOKABLE virtual QJSValue minimumSizeHint() const override {
    QSize *size = new QSize(get_selfptr()->minimumSizeHint());
//  return wrapperFactory("QSize", size);
    return PointerToJsvalue(QSize, size);
  }

  // Qt::ToolButtonStyle toolButtonStyle() const;
  Q_INVOKABLE Qt::ToolButtonStyle toolButtonStyle() const {
    return get_selfptr()->toolButtonStyle();
  }

  // Qt::ArrowType arrowType() const;
  Q_INVOKABLE Qt::ArrowType arrowType() const {
    return get_selfptr()->arrowType();
  }

  // void setArrowType(Qt::ArrowType type);
  Q_INVOKABLE void setArrowType(Qt::ArrowType type) {
    get_selfptr()->setArrowType(type);
  }

#if QT_CONFIG(menu)
  //!!! void setMenu(QMenu* menu);
  //!!! QMenu* menu() const;

  // void setPopupMode(ToolButtonPopupMode mode);
  Q_INVOKABLE void setPopupMode(ToolButtonPopupMode mode) {
    get_selfptr()->setPopupMode(static_cast<QToolButton::ToolButtonPopupMode>(static_cast<int>(mode)));
  }

  // ToolButtonPopupMode popupMode() const;
  Q_INVOKABLE ToolButtonPopupMode popupMode() const {
    return static_cast<ToolButtonPopupMode>(static_cast<int>(get_selfptr()->popupMode()));
  }
#endif

  //!!! QAction *defaultAction() const;

  // void setAutoRaise(bool enable);
  Q_INVOKABLE void setAutoRaise(bool enable) {
    get_selfptr()->setAutoRaise(enable);
  }

  // bool autoRaise() const;
  Q_INVOKABLE bool autoRaise() const {
    return get_selfptr()->autoRaise();
  }

public Q_SLOTS:

#if QT_CONFIG(menu)
  // void showMenu();
  Q_INVOKABLE void showMenu() {
    get_selfptr()->showMenu();
  }
#endif

  // void setToolButtonStyle(Qt::ToolButtonStyle style);
  Q_INVOKABLE void setToolButtonStyle(Qt::ToolButtonStyle style) {
    get_selfptr()->setToolButtonStyle(style);
  }

  // void setDefaultAction(QAction *);
  //!!! Q_INVOKABLE void setDefaultAction(QAction *);

Q_SIGNALS:
  //!!! void triggered(QAction *);

public:

  // Конструктор из объекта
  wrapper_QToolButton(void *self) : wrapper_QAbstractButton(self) {
    qDebug() << "wrapper_QToolButton::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QToolButton* get_selfptr() const {
    return static_cast<const QToolButton*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QToolButton* get_selfptr() {
    return static_cast<QToolButton*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QToolButton() override {
    qDebug() << "wrapper_QToolButton::destructor";
  }
};

Q_DECLARE_METATYPE(wrapper_QToolButton)

#endif // WRAPPER_QTOOLBUTTON_H
