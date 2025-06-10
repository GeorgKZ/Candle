#ifndef WRAPPER_QWIDGET_H
#define WRAPPER_QWIDGET_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include "wrapper_QObject.h"

class wrapper_QWidget : public wrapper_QObject { // , public wrapper_QPaintDevice

  Q_OBJECT

  Q_PROPERTY(bool modal                        READ isModal)
  Q_PROPERTY(Qt::WindowModality windowModality READ windowModality WRITE setWindowModality)
  Q_PROPERTY(bool enabled                      READ isEnabled      WRITE setEnabled)

//!!!
#if 0
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)
    Q_PROPERTY(QRect frameGeometry READ frameGeometry)
    Q_PROPERTY(QRect normalGeometry READ normalGeometry)
    Q_PROPERTY(int x READ x)
    Q_PROPERTY(int y READ y)
    Q_PROPERTY(QPoint pos READ pos WRITE move DESIGNABLE false STORED false)
    Q_PROPERTY(QSize frameSize READ frameSize)
    Q_PROPERTY(QSize size READ size WRITE resize DESIGNABLE false STORED false)
    Q_PROPERTY(int width READ width)
    Q_PROPERTY(int height READ height)
    Q_PROPERTY(QRect rect READ rect)
    Q_PROPERTY(QRect childrenRect READ childrenRect)
    Q_PROPERTY(QRegion childrenRegion READ childrenRegion)
#endif
    Q_PROPERTY(QJSValue sizePolicy
        READ sizePolicy
        WRITE setSizePolicy)
#if 0
    Q_PROPERTY(QSize minimumSize READ minimumSize WRITE setMinimumSize)
    Q_PROPERTY(QSize maximumSize READ maximumSize WRITE setMaximumSize)
    Q_PROPERTY(int minimumWidth READ minimumWidth WRITE setMinimumWidth STORED false DESIGNABLE false)
    Q_PROPERTY(int minimumHeight READ minimumHeight WRITE setMinimumHeight STORED false DESIGNABLE false)
    Q_PROPERTY(int maximumWidth READ maximumWidth WRITE setMaximumWidth STORED false DESIGNABLE false)
    Q_PROPERTY(int maximumHeight READ maximumHeight WRITE setMaximumHeight STORED false DESIGNABLE false)
    Q_PROPERTY(QSize sizeIncrement READ sizeIncrement WRITE setSizeIncrement)
    Q_PROPERTY(QSize baseSize READ baseSize WRITE setBaseSize)
    Q_PROPERTY(QPalette palette READ palette WRITE setPalette)
    Q_PROPERTY(QFont font READ font WRITE setFont)
#ifndef QT_NO_CURSOR
    Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor RESET unsetCursor)
#endif
    Q_PROPERTY(bool mouseTracking READ hasMouseTracking WRITE setMouseTracking)
    Q_PROPERTY(bool tabletTracking READ hasTabletTracking WRITE setTabletTracking)
    Q_PROPERTY(bool isActiveWindow READ isActiveWindow)
    Q_PROPERTY(Qt::FocusPolicy focusPolicy READ focusPolicy WRITE setFocusPolicy)
    Q_PROPERTY(bool focus READ hasFocus)
    Q_PROPERTY(Qt::ContextMenuPolicy contextMenuPolicy READ contextMenuPolicy WRITE setContextMenuPolicy)
    Q_PROPERTY(bool updatesEnabled READ updatesEnabled WRITE setUpdatesEnabled DESIGNABLE false)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible DESIGNABLE false)
    Q_PROPERTY(bool minimized READ isMinimized)
    Q_PROPERTY(bool maximized READ isMaximized)
    Q_PROPERTY(bool fullScreen READ isFullScreen)
#endif
    Q_PROPERTY(QJSValue sizeHint // QSize
        READ sizeHint)
    Q_PROPERTY(QJSValue minimumSizeHint // QSize
        READ minimumSizeHint)
#if 0
    Q_PROPERTY(bool acceptDrops READ acceptDrops WRITE setAcceptDrops)
    Q_PROPERTY(QString windowTitle READ windowTitle WRITE setWindowTitle NOTIFY windowTitleChanged)
    Q_PROPERTY(QIcon windowIcon READ windowIcon WRITE setWindowIcon NOTIFY windowIconChanged)
    Q_PROPERTY(QString windowIconText READ windowIconText WRITE setWindowIconText NOTIFY windowIconTextChanged) // deprecated
    Q_PROPERTY(double windowOpacity READ windowOpacity WRITE setWindowOpacity)
    Q_PROPERTY(bool windowModified READ isWindowModified WRITE setWindowModified)
#endif

#if QT_CONFIG(tooltip)
    Q_PROPERTY(QString toolTip     READ toolTip         WRITE setToolTip)
    Q_PROPERTY(int toolTipDuration READ toolTipDuration WRITE setToolTipDuration)
#endif

#if 0
#if QT_CONFIG(statustip)
    Q_PROPERTY(QString statusTip READ statusTip WRITE setStatusTip)
#endif
#if QT_CONFIG(whatsthis)
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis)
#endif
#if QT_CONFIG(accessibility)
    Q_PROPERTY(QString accessibleName READ accessibleName WRITE setAccessibleName)
    Q_PROPERTY(QString accessibleDescription READ accessibleDescription WRITE setAccessibleDescription)
#endif
    Q_PROPERTY(Qt::LayoutDirection layoutDirection READ layoutDirection WRITE setLayoutDirection RESET unsetLayoutDirection)
    QDOC_PROPERTY(Qt::WindowFlags windowFlags READ windowFlags WRITE setWindowFlags)
    Q_PROPERTY(bool autoFillBackground READ autoFillBackground WRITE setAutoFillBackground)
#ifndef QT_NO_STYLE_STYLESHEET
    Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet)
#endif
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale RESET unsetLocale)
    Q_PROPERTY(QString windowFilePath READ windowFilePath WRITE setWindowFilePath)
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints WRITE setInputMethodHints)
#endif

public:

  // Из файла qwidget.h

  Q_INVOKABLE explicit wrapper_QWidget(wrapper_QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
    wrapper_QObject(new QWidget(parent == nullptr ? nullptr : parent->get_selfptr(), f)) {
    qDebug() << "wrapper_QWidget::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ", f)";
  }

  Q_INVOKABLE int devType() const { return get_selfptr()->devType(); }

  Q_INVOKABLE WId winId() const { return get_selfptr()->winId(); }
  Q_INVOKABLE void createWinId() { return get_selfptr()->createWinId(); }
  Q_INVOKABLE WId internalWinId() const { return get_selfptr()->internalWinId(); }
  Q_INVOKABLE WId effectiveWinId() const { return get_selfptr()->effectiveWinId(); }

#if 0
    // GUI style setting
    QStyle *style() const;
    void setStyle(QStyle *);
#endif

    // Widget types and states
  Q_INVOKABLE bool isWindow() const { return get_selfptr()->isWindow(); }

  Q_INVOKABLE bool isModal() const { return get_selfptr()->isModal(); }
  Q_INVOKABLE Qt::WindowModality windowModality() const { return get_selfptr()->windowModality(); }
  Q_INVOKABLE void setWindowModality(Qt::WindowModality windowModality) { get_selfptr()->setWindowModality(windowModality); }

  Q_INVOKABLE bool isEnabled() const {
    return get_selfptr()->isEnabled();
  }

#if 0
  Q_INVOKABLE bool isEnabledTo(const QWidget *) const;
#endif

public Q_SLOTS:

  Q_INVOKABLE void setEnabled(bool b) { get_selfptr()->setEnabled(b); }
  Q_INVOKABLE void setDisabled(bool b) { get_selfptr()->setDisabled(b); }
  Q_INVOKABLE void setWindowModified(bool b) { get_selfptr()->setWindowModified(b); }

public:
#if 0
    wrapper_QRect frameGeometry() const;
    const wrapper_QRect &geometry() const;
    wrapper_QRect normalGeometry() const;

    int x() const;
    int y() const;
    QPoint pos() const;
    QSize frameSize() const;
    QSize size() const;
    inline int width() const;
    inline int height() const;
    inline QRect rect() const;
    QRect childrenRect() const;
    QRegion childrenRegion() const;

    QSize minimumSize() const;
    QSize maximumSize() const;
    int minimumWidth() const;
    int minimumHeight() const;
    int maximumWidth() const;
    int maximumHeight() const;
    void setMinimumSize(const QSize &);
    void setMinimumSize(int minw, int minh);
    void setMaximumSize(const QSize &);
    void setMaximumSize(int maxw, int maxh);
    void setMinimumWidth(int minw);
    void setMinimumHeight(int minh);
    void setMaximumWidth(int maxw);
    void setMaximumHeight(int maxh);

#ifdef Q_QDOC
    void setupUi(QWidget *widget);
#endif

    QSize sizeIncrement() const;
    void setSizeIncrement(const QSize &);
    void setSizeIncrement(int w, int h);
    QSize baseSize() const;
    void setBaseSize(const QSize &);
    void setBaseSize(int basew, int baseh);

    void setFixedSize(const QSize &);
#endif

  Q_INVOKABLE void setFixedSize(int w, int h) { get_selfptr()->setFixedSize(w, h); }
  Q_INVOKABLE void setFixedWidth(int w) { get_selfptr()->setFixedWidth(w); }
  Q_INVOKABLE void setFixedHeight(int h) { get_selfptr()->setFixedHeight(h); }

#if 0
    // Widget coordinate mapping

    QPointF mapToGlobal(const QPointF &) const;
    QPoint mapToGlobal(const QPoint &) const;
    QPointF mapFromGlobal(const QPointF &) const;
    QPoint mapFromGlobal(const QPoint &) const;
    QPointF mapToParent(const QPointF &) const;
    QPoint mapToParent(const QPoint &) const;
    QPointF mapFromParent(const QPointF &) const;
    QPoint mapFromParent(const QPoint &) const;
    QPointF mapTo(const QWidget *, const QPointF &) const;
    QPoint mapTo(const QWidget *, const QPoint &) const;
    QPointF mapFrom(const QWidget *, const QPointF &) const;
    QPoint mapFrom(const QWidget *, const QPoint &) const;

    QWidget *window() const;
    QWidget *nativeParentWidget() const;
    inline QWidget *topLevelWidget() const { return window(); }

    // Widget appearance functions
    const QPalette &palette() const;
    void setPalette(const QPalette &);

    void setBackgroundRole(QPalette::ColorRole);
    QPalette::ColorRole backgroundRole() const;

    void setForegroundRole(QPalette::ColorRole);
    QPalette::ColorRole foregroundRole() const;

    const QFont &font() const;
    void setFont(const QFont &);
    QFontMetrics fontMetrics() const;
    QFontInfo fontInfo() const;

#ifndef QT_NO_CURSOR
    QCursor cursor() const;
    void setCursor(const QCursor &);
    void unsetCursor();
#endif

    void setMouseTracking(bool enable);
    bool hasMouseTracking() const;
    bool underMouse() const;

    void setTabletTracking(bool enable);
    bool hasTabletTracking() const;

    void setMask(const QBitmap &);
    void setMask(const QRegion &);
    QRegion mask() const;
    void clearMask();

    void render(QPaintDevice *target, const QPoint &targetOffset = QPoint(),
                const QRegion &sourceRegion = QRegion(),
                RenderFlags renderFlags = RenderFlags(DrawWindowBackground | DrawChildren));

    void render(QPainter *painter, const QPoint &targetOffset = QPoint(),
                const QRegion &sourceRegion = QRegion(),
                RenderFlags renderFlags = RenderFlags(DrawWindowBackground | DrawChildren));

    Q_INVOKABLE QPixmap grab(const QRect &rectangle = QRect(QPoint(0, 0), QSize(-1, -1)));

#if QT_CONFIG(graphicseffect)
    QGraphicsEffect *graphicsEffect() const;
    void setGraphicsEffect(QGraphicsEffect *effect);
#endif // QT_CONFIG(graphicseffect)

#ifndef QT_NO_GESTURES
    void grabGesture(Qt::GestureType type, Qt::GestureFlags flags = Qt::GestureFlags());
    void ungrabGesture(Qt::GestureType type);
#endif

#endif

#if 0

public Q_SLOTS:
    void setWindowTitle(const QString &);
#ifndef QT_NO_STYLE_STYLESHEET
    void setStyleSheet(const QString& styleSheet);
#endif
public:
#ifndef QT_NO_STYLE_STYLESHEET
    QString styleSheet() const;
#endif
    QString windowTitle() const;
    void setWindowIcon(const QIcon &icon);
    QIcon windowIcon() const;
    void setWindowIconText(const QString &);
    QString windowIconText() const;
    void setWindowRole(const QString &);
    QString windowRole() const;
    void setWindowFilePath(const QString &filePath);
    QString windowFilePath() const;

    void setWindowOpacity(qreal level);
    qreal windowOpacity() const;

    bool isWindowModified() const;
#endif

#if QT_CONFIG(tooltip)
  Q_INVOKABLE void setToolTip(const QString &tooltip) { get_selfptr()->setToolTip(tooltip); }
  Q_INVOKABLE QString toolTip() const { return get_selfptr()->toolTip(); }
  Q_INVOKABLE void setToolTipDuration(int msec) { get_selfptr()->setToolTipDuration(msec); }
  Q_INVOKABLE int toolTipDuration() const { return get_selfptr()->toolTipDuration(); }
#endif

#if 0

#if QT_CONFIG(statustip)
    void setStatusTip(const QString &);
    QString statusTip() const;
#endif
#if QT_CONFIG(whatsthis)
    void setWhatsThis(const QString &);
    QString whatsThis() const;
#endif
#if QT_CONFIG(accessibility)
    QString accessibleName() const;
    void setAccessibleName(const QString &name);
    QString accessibleDescription() const;
    void setAccessibleDescription(const QString &description);
#endif

    void setLayoutDirection(Qt::LayoutDirection direction);
    Qt::LayoutDirection layoutDirection() const;
    void unsetLayoutDirection();

    void setLocale(const QLocale &locale);
    QLocale locale() const;
    void unsetLocale();

    inline bool isRightToLeft() const { return layoutDirection() == Qt::RightToLeft; }
    inline bool isLeftToRight() const { return layoutDirection() == Qt::LeftToRight; }

public Q_SLOTS:
    inline void setFocus() { setFocus(Qt::OtherFocusReason); }

public:
    bool isActiveWindow() const;
    void activateWindow();
    void clearFocus();

    void setFocus(Qt::FocusReason reason);
    Qt::FocusPolicy focusPolicy() const;
    void setFocusPolicy(Qt::FocusPolicy policy);
    bool hasFocus() const;
    static void setTabOrder(QWidget *, QWidget *);
    void setFocusProxy(QWidget *);
    QWidget *focusProxy() const;
    Qt::ContextMenuPolicy contextMenuPolicy() const;
    void setContextMenuPolicy(Qt::ContextMenuPolicy policy);

    // Grab functions
    void grabMouse();
#ifndef QT_NO_CURSOR
    void grabMouse(const QCursor &);
#endif
    void releaseMouse();
    void grabKeyboard();
    void releaseKeyboard();
#ifndef QT_NO_SHORTCUT
    int grabShortcut(const QKeySequence &key, Qt::ShortcutContext context = Qt::WindowShortcut);
    void releaseShortcut(int id);
    void setShortcutEnabled(int id, bool enable = true);
    void setShortcutAutoRepeat(int id, bool enable = true);
#endif
    static QWidget *mouseGrabber();
    static QWidget *keyboardGrabber();

    // Update/refresh functions
    inline bool updatesEnabled() const;
    void setUpdatesEnabled(bool enable);

#if QT_CONFIG(graphicsview)
    QGraphicsProxyWidget *graphicsProxyWidget() const;
#endif

public Q_SLOTS:
    void update();
    void repaint();

public:
    inline void update(int x, int y, int w, int h);
    void update(const QRect&);
    void update(const QRegion&);

    void repaint(int x, int y, int w, int h);
    void repaint(const QRect &);
    void repaint(const QRegion &);

public Q_SLOTS:
    // Widget management functions

    virtual void setVisible(bool visible);
    void setHidden(bool hidden);
    void show();
    void hide();

    void showMinimized();
    void showMaximized();
    void showFullScreen();
    void showNormal();

    bool close();
    void raise();
    void lower();

public:
    void stackUnder(QWidget*);
    void move(int x, int y);
    void move(const QPoint &);
    void resize(int w, int h);
    void resize(const QSize &);
    inline void setGeometry(int x, int y, int w, int h);
    void setGeometry(const QRect &);
    QByteArray saveGeometry() const;
    bool restoreGeometry(const QByteArray &geometry);
    void adjustSize();
    bool isVisible() const;
    bool isVisibleTo(const QWidget *) const;
    inline bool isHidden() const;

    bool isMinimized() const;
    bool isMaximized() const;
    bool isFullScreen() const;

    Qt::WindowStates windowState() const;
    void setWindowState(Qt::WindowStates state);
    void overrideWindowState(Qt::WindowStates state);
#endif
    // virtual QSize sizeHint() const;
    virtual QJSValue sizeHint() const;
    
    // virtual QSize minimumSizeHint() const;
    virtual QJSValue minimumSizeHint() const;

    QJSValue sizePolicy() const;

    void setSizePolicy(const QJSValue &sizepolicy);
#if 0
    void setSizePolicy(QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical);
    virtual int heightForWidth(int) const;
    virtual bool hasHeightForWidth() const;

    QRegion visibleRegion() const;

    void setContentsMargins(int left, int top, int right, int bottom);
    void setContentsMargins(const QMargins &margins);
    QMargins contentsMargins() const;

    QRect contentsRect() const;
#endif
public:

  // QLayout *layout() const;
  Q_INVOKABLE QJSValue layout() const;

#if 0
    void setLayout(QLayout *);
    void updateGeometry();

    void setParent(QWidget *parent);
    void setParent(QWidget *parent, Qt::WindowFlags f);

    void scroll(int dx, int dy);
    void scroll(int dx, int dy, const QRect&);

    // Misc. functions

    QWidget *focusWidget() const;
    QWidget *nextInFocusChain() const;
    QWidget *previousInFocusChain() const;

    // drag and drop
    bool acceptDrops() const;
    void setAcceptDrops(bool on);

#ifndef QT_NO_ACTION
    //actions
    void addAction(QAction *action);
    void addActions(const QList<QAction*> &actions);
    void insertActions(QAction *before, const QList<QAction*> &actions);
    void insertAction(QAction *before, QAction *action);
    void removeAction(QAction *action);
    QList<QAction*> actions() const;

    // convenience action factories
    QAction *addAction(const QString &text);
    QAction *addAction(const QIcon &icon, const QString &text);
    QAction *addAction(const QString &text, const QObject *receiver,
                       const char *member, Qt::ConnectionType type = Qt::AutoConnection);
    QAction *addAction(const QIcon &icon, const QString &text, const QObject *receiver,
                       const char *member, Qt::ConnectionType type = Qt::AutoConnection);
    template <typename...Args, typename = compatible_action_slot_args<Args...>>
    QAction *addAction(const QString &text, Args&&...args)
    {
        QAction *result = addAction(text);
        connect(result, &QAction::triggered, std::forward<Args>(args)...);
        return result;
    }
    template <typename...Args, typename = compatible_action_slot_args<Args...>>
    QAction *addAction(const QIcon &icon, const QString &text, Args&&...args)
    {
        QAction *result = addAction(icon, text);
        connect(result, &QAction::triggered, std::forward<Args>(args)...);
        return result;
    }

#if QT_CONFIG(shortcut)
    QAction *addAction(const QString &text, const QKeySequence &shortcut);
    QAction *addAction(const QIcon &icon, const QString &text, const QKeySequence &shortcut);
    QAction *addAction(const QString &text, const QKeySequence &shortcut,
                       const QObject *receiver, const char *member,
                       Qt::ConnectionType type = Qt::AutoConnection);
    QAction *addAction(const QIcon &icon, const QString &text, const QKeySequence &shortcut,
                       const QObject *receiver, const char *member,
                       Qt::ConnectionType type = Qt::AutoConnection);

    template <typename...Args, typename = compatible_action_slot_args<Args...>>
    QAction *addAction(const QString &text, const QKeySequence &shortcut, Args&&...args)
    {
        QAction *result = addAction(text, shortcut);
        connect(result, &QAction::triggered, std::forward<Args>(args)...);
        return result;
    }
    template <typename...Args, typename = compatible_action_slot_args<Args...>>
    QAction *addAction(const QIcon &icon, const QString &text, const QKeySequence &shortcut, Args&&...args)
    {
        QAction *result = addAction(icon, text, shortcut);
        connect(result, &QAction::triggered, std::forward<Args>(args)...);
        return result;
    }
#endif // QT_CONFIG(shortcut)
#endif // QT_NO_ACTION

    QWidget *parentWidget() const;

    void setWindowFlags(Qt::WindowFlags type);
    inline Qt::WindowFlags windowFlags() const;
    void setWindowFlag(Qt::WindowType, bool on = true);
    void overrideWindowFlags(Qt::WindowFlags type);

    inline Qt::WindowType windowType() const;

    static QWidget *find(WId);
    inline QWidget *childAt(int x, int y) const;
    QWidget *childAt(const QPoint &p) const;

    void setAttribute(Qt::WidgetAttribute, bool on = true);
    inline bool testAttribute(Qt::WidgetAttribute) const;

    QPaintEngine *paintEngine() const override;

    void ensurePolished() const;

    bool isAncestorOf(const QWidget *child) const;

#ifdef QT_KEYPAD_NAVIGATION
    bool hasEditFocus() const;
    void setEditFocus(bool on);
#endif

    bool autoFillBackground() const;
    void setAutoFillBackground(bool enabled);

    QBackingStore *backingStore() const;

    QWindow *windowHandle() const;
    QScreen *screen() const;
    void setScreen(QScreen *);

    static QWidget *createWindowContainer(QWindow *window, QWidget *parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());

#endif

Q_SIGNALS:
    void windowTitleChanged(const QString &title);
    // QIcon
    void windowIconChanged(const QJSValue &icon);
    void windowIconTextChanged(const QString &iconText);
    // QPoint
    void customContextMenuRequested(const QJSValue &pos);

public:
#if 0
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery) const;

    Qt::InputMethodHints inputMethodHints() const;
    void setInputMethodHints(Qt::InputMethodHints hints);
#endif

public:

  // Конструктор из объекта
  explicit wrapper_QWidget(QWidget* self) :
    wrapper_QObject(self) {
    qDebug() << "wrapper_QWidget::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QWidget() {
    qDebug() << "wrapper_QWidget::desctructor";
    /* delete static_cast<QWidget*>(wrapper_QObject::get_selfptr()); */
  }

  // Получение константного указателя на объект
  const QWidget* get_selfptr() const {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QWidget::get_selfptr - got nullptr";
    }
    return static_cast<const QWidget*>(wrapper_QObject::get_selfptr());
  }

  // Получение указателя на объект
  QWidget* get_selfptr() {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QWidget::get_selfptr - got nullptr";
    }
    return static_cast<QWidget*>(wrapper_QObject::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QWidget);
Q_DECLARE_METATYPE(wrapper_QWidget*);

#endif // WRAPPER_QWIDGET_H
