#ifndef WRAPPER_QACTION_H
#define WRAPPER_QACTION_H

#include <QtCore/QObject>
#include <QtGui/QAction>
#include "wrapper_QObject.h"

class wrapper_QAction : public wrapper_QObject {

  Q_OBJECT

  // Из файла qaction.h
  Q_PROPERTY(bool checkable        
             READ isCheckable
             WRITE setCheckable
             NOTIFY checkableChanged
             FINAL)
  Q_PROPERTY(bool checked
             READ isChecked
             WRITE setChecked
             NOTIFY toggled)
  Q_PROPERTY(bool enabled
             READ isEnabled
             WRITE setEnabled
             NOTIFY enabledChanged
             RESET resetEnabled
             FINAL)
//  Q_PROPERTY(QIcon icon            READ icon WRITE setIcon NOTIFY changed)
  Q_PROPERTY(QString text          READ text WRITE setText NOTIFY changed)
  Q_PROPERTY(QString iconText      READ iconText WRITE setIconText NOTIFY changed)
  Q_PROPERTY(QString toolTip       READ toolTip WRITE setToolTip NOTIFY changed)
  Q_PROPERTY(QString statusTip     READ statusTip WRITE setStatusTip NOTIFY changed)
  Q_PROPERTY(QString whatsThis     READ whatsThis WRITE setWhatsThis NOTIFY changed)
//Q_PROPERTY(QFont font            READ font WRITE setFont NOTIFY changed)
#if QT_CONFIG(shortcut)
//  Q_PROPERTY(QKeySequence shortcut READ shortcut WRITE setShortcut NOTIFY changed)
  Q_PROPERTY(Qt::ShortcutContext shortcutContext
             READ shortcutContext
             WRITE setShortcutContext
             NOTIFY changed)
  Q_PROPERTY(bool autoRepeat
             READ autoRepeat
             WRITE setAutoRepeat
             NOTIFY changed)
#endif // QT_CONFIG(shortcut)
  Q_PROPERTY(bool visible           READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)
  Q_PROPERTY(MenuRole menuRole      READ menuRole WRITE setMenuRole NOTIFY changed)
  Q_PROPERTY(bool iconVisibleInMenu READ isIconVisibleInMenu WRITE setIconVisibleInMenu             NOTIFY changed)
  Q_PROPERTY(bool shortcutVisibleInContextMenu
             READ isShortcutVisibleInContextMenu
             WRITE setShortcutVisibleInContextMenu
             NOTIFY changed)
  Q_PROPERTY(Priority priority
             READ priority
             WRITE setPriority
             NOTIFY changed)

public:

  enum MenuRole {
    NoRole = 0,
    TextHeuristicRole,
    ApplicationSpecificRole,
    AboutQtRole,
    AboutRole,
    PreferencesRole,
    QuitRole
  };
  Q_ENUM(MenuRole)

  enum Priority {
    LowPriority = 0,
    NormalPriority = 128,
    HighPriority = 256
  };
  Q_ENUM(Priority)

  Q_INVOKABLE explicit wrapper_QAction(wrapper_QObject* parent = nullptr) :
    wrapper_QObject(new QAction(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QAction::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // explicit QAction(const QString &text, QObject *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QAction(const QString &text, const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QObject(new QAction(text,
    (QObject*)jsvalueToObject_ptr("QObject", parent)))  {
    qDebug() << "wrapper_QAction::constructor(" << text << ", obj. " << (unsigned long long)get_selfptr()->parent() << ")";
  }

  // explicit QAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

  // QList<QObject *> associatedObjects() const;

  // void setActionGroup(QActionGroup *group);

  // QActionGroup *actionGroup() const;

  // void setIcon(const QIcon &icon);

  // QIcon icon() const;

  // void setText(const QString &text);
  Q_INVOKABLE void setText(const QString &text) { get_selfptr()->setText(text); }

  // QString text() const;
  Q_INVOKABLE QString text() const { return get_selfptr()->text(); }

  // void setIconText(const QString &text);
  Q_INVOKABLE void setIconText(const QString &text) { get_selfptr()->setIconText(text); }

  // QString iconText() const;
  Q_INVOKABLE QString iconText() const { return get_selfptr()->iconText(); }

  // void setToolTip(const QString &tip);
  Q_INVOKABLE void setToolTip(const QString &tip) { get_selfptr()->setToolTip(tip); }

  // QString toolTip() const;
  Q_INVOKABLE QString toolTip() const { return get_selfptr()->toolTip(); }

  // void setStatusTip(const QString &statusTip);
  Q_INVOKABLE void setStatusTip(const QString &statusTip) { get_selfptr()->setStatusTip(statusTip); }

  // QString statusTip() const;
  Q_INVOKABLE QString statusTip() const { return get_selfptr()->statusTip(); }

  // void setWhatsThis(const QString &what);
  Q_INVOKABLE void setWhatsThis(const QString &what) { get_selfptr()->setWhatsThis(what); }

  // QString whatsThis() const;
  Q_INVOKABLE QString whatsThis() const { return get_selfptr()->whatsThis(); }

  // void setPriority(Priority priority);
  Q_INVOKABLE void setPriority(Priority priority) { get_selfptr()->setPriority((QAction::Priority)(int)priority); }

  // Priority priority() const;
  Q_INVOKABLE Priority priority() const { return (Priority)(int)get_selfptr()->priority(); }

  // void setSeparator(bool b);
  Q_INVOKABLE void setSeparator(bool b) { get_selfptr()->setSeparator(b); }

  // bool isSeparator() const;
  Q_INVOKABLE bool isSeparator() const { return get_selfptr()->isSeparator(); }

#if QT_CONFIG(shortcut)

  // void setShortcut(const QKeySequence &shortcut);

  // QKeySequence shortcut() const;

  // void setShortcuts(const QList<QKeySequence> &shortcuts);

  // void setShortcuts(QKeySequence::StandardKey);

  // QList<QKeySequence> shortcuts() const;

  // void setShortcutContext(Qt::ShortcutContext context);
  Q_INVOKABLE void setShortcutContext(Qt::ShortcutContext context) { return get_selfptr()->setShortcutContext(context); }

  // Qt::ShortcutContext shortcutContext() const;
  Q_INVOKABLE Qt::ShortcutContext shortcutContext() const { return get_selfptr()->shortcutContext(); }

  // void setAutoRepeat(bool autoRepeat);
  Q_INVOKABLE void setAutoRepeat(bool autoRepeat) { get_selfptr()->setAutoRepeat(autoRepeat); }

  // bool autoRepeat() const;
  Q_INVOKABLE bool autoRepeat() const { return get_selfptr()->autoRepeat(); }

#endif // QT_CONFIG(shortcut)

  // void setFont(const QFont &font);

  // QFont font() const;

  // void setCheckable(bool);
  Q_INVOKABLE void setCheckable(bool checkable) { get_selfptr()->setCheckable(checkable); }

  // bool isCheckable() const;
  Q_INVOKABLE bool isCheckable() const { return get_selfptr()->isCheckable(); }

  // QVariant data() const;

  // void setData(const QVariant &var);

  // bool isChecked() const;
  Q_INVOKABLE bool isChecked() const { return get_selfptr()->isChecked(); }

  // bool isEnabled() const;
  Q_INVOKABLE bool isEnabled() const { return get_selfptr()->isEnabled(); }

  // bool isVisible() const;
  Q_INVOKABLE bool isVisible() const { return get_selfptr()->isVisible(); }

  enum ActionEvent {
    Trigger,
    Hover
  };

  // void activate(ActionEvent event);
  Q_INVOKABLE void activate(ActionEvent event) { get_selfptr()->activate((QAction::ActionEvent)(int)event); }

  // void setMenuRole(MenuRole menuRole);
  Q_INVOKABLE void setMenuRole(MenuRole menuRole) { get_selfptr()->setMenuRole((QAction::MenuRole)(int)menuRole); }

  // MenuRole menuRole() const;
  Q_INVOKABLE MenuRole menuRole() const { return (MenuRole)(int)get_selfptr()->menuRole(); }

#ifdef Q_CLANG_QDOC
  // QMenu *menu() const;
  // void setMenu(QMenu *menu);
#else
  //   template<typename T = QMenu*>
  //   T menu() const

  //   template<typename T = QMenu*>
  //   void setMenu(T m)
#endif

  // void setIconVisibleInMenu(bool visible);
  Q_INVOKABLE void setIconVisibleInMenu(bool visible) { get_selfptr()->setIconVisibleInMenu(visible); }

  // bool isIconVisibleInMenu() const;
  Q_INVOKABLE bool isIconVisibleInMenu() const { return get_selfptr()->isIconVisibleInMenu(); }

  // void setShortcutVisibleInContextMenu(bool show);
  Q_INVOKABLE void setShortcutVisibleInContextMenu(bool show) { get_selfptr()->setShortcutVisibleInContextMenu(show); }

  // bool isShortcutVisibleInContextMenu() const;
  Q_INVOKABLE bool isShortcutVisibleInContextMenu() const { return get_selfptr()->isShortcutVisibleInContextMenu(); }

  // bool showStatusText(QObject *object = nullptr);

public Q_SLOTS:

  // void trigger()
  Q_INVOKABLE void trigger() { get_selfptr()->trigger(); }

  // void hover()
  Q_INVOKABLE void hover() { get_selfptr()->hover(); }

  // void setChecked(bool);
  Q_INVOKABLE void setChecked(bool checked) { get_selfptr()->setChecked(checked); }

  // void toggle();
  Q_INVOKABLE void toggle() { get_selfptr()->toggle(); }

  // void setEnabled(bool);
  Q_INVOKABLE void setEnabled(bool enable) { get_selfptr()->setEnabled(enable); }

  // void resetEnabled();
  Q_INVOKABLE void resetEnabled() { get_selfptr()->resetEnabled(); }

  // void setDisabled(bool b)
  Q_INVOKABLE void setDisabled(bool b) { get_selfptr()->setDisabled(b); }

  // void setVisible(bool)
  Q_INVOKABLE void setVisible(bool v) { get_selfptr()->setVisible(v); }

Q_SIGNALS:
  void changed();
  void enabledChanged(bool enabled);
  void checkableChanged(bool checkable);
  void visibleChanged();
  void triggered(bool checked = false);
  void hovered();
  void toggled(bool);

public:

  // Конструктор из объекта
  explicit wrapper_QAction(QAction* self) :
    wrapper_QObject(self) {
    qDebug() << "wrapper_QAction::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QAction() {
    qDebug() << "wrapper_QAction::desctructor";
    /* delete static_cast<QAction*>(wrapper_QObject::get_selfptr()); */
  }

  // Получение константного указателя на объект
  const QAction* get_selfptr() const {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAction::get_selfptr - got nullptr";
    }
    return static_cast<const QAction*>(wrapper_QObject::get_selfptr());
  }

  // Получение указателя на объект
  QAction* get_selfptr() {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QAction::get_selfptr - got nullptr";
    }
    return static_cast<QAction*>(wrapper_QObject::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QAction);

#endif // WRAPPER_QACTION_H
