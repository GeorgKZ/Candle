#ifndef WRAPPER_QOBJECT_H
#define WRAPPER_QOBJECT_H

#include <QtCore/QObject>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QObject : public wrapper_common {

  Q_OBJECT

  // Из файла qobject.h
  Q_PROPERTY(QString objectName READ objectName WRITE setObjectName NOTIFY objectNameChanged ) // BINDABLE bindableObjectName)

public:

  Q_INVOKABLE explicit wrapper_QObject(wrapper_QObject *parent = nullptr) :
    wrapper_common(new QObject(parent == nullptr ? nullptr : parent->get_selfptr())) {
      qDebug() << "wrapper_QObject::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

#if 0

    virtual bool event(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);

#if defined(QT_NO_TRANSLATION) || defined(Q_CLANG_QDOC)
    static QString tr(const char *sourceText, const char * = nullptr, int = -1)
#endif // QT_NO_TRANSLATION
#endif

  Q_INVOKABLE QString objectName() const {
    return get_selfptr()->objectName();
  }

  // void setObjectName(const QString &name);
  Q_INVOKABLE void setObjectName(const QString &name) {
    get_selfptr()->setObjectName(name);
  }
//    void setObjectName(QAnyStringView name);
//    QBindable<QString> bindableObjectName();

#if 0

    inline bool isWidgetType() const
    inline bool isWindowType() const
    inline bool isQuickItemType() const

    inline bool signalsBlocked() const noexcept
    bool blockSignals(bool b) noexcept;

    QThread *thread() const;
    void moveToThread(QThread *thread);

    int startTimer(int interval, Qt::TimerType timerType = Qt::CoarseTimer);

    int startTimer(std::chrono::milliseconds time, Qt::TimerType timerType = Qt::CoarseTimer)
#endif

  // void killTimer(int id);
  Q_INVOKABLE void killTimer(int id) {
    get_selfptr()->killTimer(id);
  }

  Q_INVOKABLE QJSValue findChild(const QString &aName = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const;

#if 0
    template<typename T>
    inline QList<T> findChildren(const QString &aName, Qt::FindChildOptions options = Qt::FindChildrenRecursively) const

    template<typename T>
    QList<T> findChildren(Qt::FindChildOptions options = Qt::FindChildrenRecursively) const

#if QT_CONFIG(regularexpression)
    template<typename T>
    inline QList<T> findChildren(const QRegularExpression &re, Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
#endif // QT_CONFIG(regularexpression)

    const QObjectList &children() const

    void setParent(QObject *parent);
    void installEventFilter(QObject *filterObj);
    void removeEventFilter(QObject *obj);

    static QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const QObject *receiver, const char *member, Qt::ConnectionType = Qt::AutoConnection);

    static QMetaObject::Connection connect(const QObject *sender, const QMetaMethod &signal,
                        const QObject *receiver, const QMetaMethod &method,
                        Qt::ConnectionType type = Qt::AutoConnection);

    inline QMetaObject::Connection connect(const QObject *sender, const char *signal,
                        const char *member, Qt::ConnectionType type = Qt::AutoConnection) const;

#ifdef Q_CLANG_QDOC
    template<typename PointerToMemberFunction>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);
    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, Functor functor);
    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *context, Functor functor, Qt::ConnectionType type = Qt::AutoConnection);
#else
    //Connect a signal to a pointer to qobject member function
    template <typename Func1, typename Func2>
    static inline QMetaObject::Connection connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                     const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot,
                                     Qt::ConnectionType type = Qt::AutoConnection)

    //connect to a function pointer  (not a member)
    template <typename Func1, typename Func2>
    static inline typename std::enable_if<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0, QMetaObject::Connection>::type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)

    //connect to a function pointer  (not a member)
    template <typename Func1, typename Func2>
    static inline typename std::enable_if<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0 &&
                                          !QtPrivate::FunctionPointer<Func2>::IsPointerToMemberFunction, QMetaObject::Connection>::type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, const QObject *context, Func2 slot,
                    Qt::ConnectionType type = Qt::AutoConnection)

    //connect to a functor
    template <typename Func1, typename Func2>
    static inline typename std::enable_if<
        QtPrivate::FunctionPointer<Func2>::ArgumentCount == -1 &&
        !std::is_convertible_v<Func2, const char*>, // don't match old-style connect
    QMetaObject::Connection>::type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)

    //connect to a functor, with a "context" object defining in which event loop is going to be executed
    template <typename Func1, typename Func2>
    static inline typename std::enable_if<
        QtPrivate::FunctionPointer<Func2>::ArgumentCount == -1 &&
        !std::is_convertible_v<Func2, const char*>, // don't match old-style connect
    QMetaObject::Connection>::type
            connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, const QObject *context, Func2 slot,
                    Qt::ConnectionType type = Qt::AutoConnection)
#endif //Q_CLANG_QDOC

    static bool disconnect(const QObject *sender, const char *signal,
                           const QObject *receiver, const char *member);
    static bool disconnect(const QObject *sender, const QMetaMethod &signal,
                           const QObject *receiver, const QMetaMethod &member);
    inline bool disconnect(const char *signal = nullptr,
                           const QObject *receiver = nullptr, const char *member = nullptr) const
        { return disconnect(this, signal, receiver, member); }
    inline bool disconnect(const QObject *receiver, const char *member = nullptr) const
        { return disconnect(this, nullptr, receiver, member); }
    static bool disconnect(const QMetaObject::Connection &);

#ifdef Q_CLANG_QDOC
    template<typename PointerToMemberFunction>
    static bool disconnect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method);
#else
    template <typename Func1, typename Func2>
    static inline bool disconnect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                  const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)

    template <typename Func1>
    static inline bool disconnect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                  const QObject *receiver, void **zero)
#endif //Q_CLANG_QDOC

    void dumpObjectTree() const;
    void dumpObjectInfo() const;

    bool setProperty(const char *name, const QVariant &value);
    QVariant property(const char *name) const;
    QList<QByteArray> dynamicPropertyNames() const;
    QBindingStorage *bindingStorage() { return &d_ptr->bindingStorage; }
    const QBindingStorage *bindingStorage() const { return &d_ptr->bindingStorage; }

#endif

Q_SIGNALS:

    void destroyed(QObject *obj = nullptr);
    void objectNameChanged(const QString &objectName, QPrivateSignal);

public:

  Q_INVOKABLE wrapper_QObject *parent() const {
    return new wrapper_QObject(get_selfptr()->parent());
  }

  Q_INVOKABLE bool inherits(const char *classname) const {
    return get_selfptr()->inherits(classname);
  }

public Q_SLOTS:

  Q_INVOKABLE void deleteLater() {
    get_selfptr()->deleteLater();
  }

public:

  // Конструктор из объекта
  explicit wrapper_QObject(QObject* self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QObject::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QObject() {
    qDebug() << "wrapper_QObject::destructor";
    /* delete static_cast<QObject*>(wrapper_common::get_selfptr()); */
  }

  // Получение константного указателя на объект
  const QObject* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QObject::get_selfptr - got nullptr";
    }
    return static_cast<const QObject*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QObject* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QObject::get_selfptr - got nullptr";
    }
    return static_cast<QObject*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QObject);

#endif // WRAPPER_QOBJECT_H
