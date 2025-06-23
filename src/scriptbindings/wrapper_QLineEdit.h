#ifndef WRAPPER_QLINEEDIT_H
#define WRAPPER_QLINEEDIT_H

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QLineEdit : public wrapper_QWidget {

  Q_OBJECT

  // Из файла qlineedit.h

#if 0
    Q_PROPERTY(QString inputMask READ inputMask WRITE setInputMask)
#endif
    Q_PROPERTY(QString text
        READ text
        WRITE setText
        NOTIFY textChanged
        USER true)
#if 0
    Q_PROPERTY(int maxLength READ maxLength WRITE setMaxLength)
    Q_PROPERTY(bool frame READ hasFrame WRITE setFrame)
    Q_PROPERTY(EchoMode echoMode READ echoMode WRITE setEchoMode)
    Q_PROPERTY(QString displayText READ displayText)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool modified READ isModified WRITE setModified DESIGNABLE false)
    Q_PROPERTY(bool hasSelectedText READ hasSelectedText)
    Q_PROPERTY(QString selectedText READ selectedText)
    Q_PROPERTY(bool dragEnabled READ dragEnabled WRITE setDragEnabled)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    Q_PROPERTY(bool undoAvailable READ isUndoAvailable)
    Q_PROPERTY(bool redoAvailable READ isRedoAvailable)
    Q_PROPERTY(bool acceptableInput READ hasAcceptableInput)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
    Q_PROPERTY(Qt::CursorMoveStyle cursorMoveStyle READ cursorMoveStyle WRITE setCursorMoveStyle)
    Q_PROPERTY(bool clearButtonEnabled READ isClearButtonEnabled WRITE setClearButtonEnabled)
#endif

public:

    enum ActionPosition {
        LeadingPosition,
        TrailingPosition
    };
    Q_ENUM(ActionPosition)

#if 0
    explicit QLineEdit(QWidget *parent = nullptr);

    explicit QLineEdit(const QString &, QWidget *parent = nullptr);

#endif

    // QString text() const;
    Q_INVOKABLE QString text() const
    {
        return get_selfptr()->text();
    }

#if 0
    QString displayText() const;

    QString placeholderText() const;
    void setPlaceholderText(const QString &);

    int maxLength() const;
    void setMaxLength(int);

    void setFrame(bool);
    bool hasFrame() const;

    void setClearButtonEnabled(bool enable);
    bool isClearButtonEnabled() const;

    enum EchoMode { Normal, NoEcho, Password, PasswordEchoOnEdit };
    Q_ENUM(EchoMode)
    EchoMode echoMode() const;
    void setEchoMode(EchoMode);

    bool isReadOnly() const;
    void setReadOnly(bool);

#ifndef QT_NO_VALIDATOR
    void setValidator(const QValidator *);
    const QValidator * validator() const;
#endif

#if QT_CONFIG(completer)
    void setCompleter(QCompleter *completer);
    QCompleter *completer() const;
#endif

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    int cursorPosition() const;
    void setCursorPosition(int);
    int cursorPositionAt(const QPoint &pos);

    void setAlignment(Qt::Alignment flag);
    Qt::Alignment alignment() const;

    void cursorForward(bool mark, int steps = 1);
    void cursorBackward(bool mark, int steps = 1);
    void cursorWordForward(bool mark);
    void cursorWordBackward(bool mark);
    void backspace();
    void del();
    void home(bool mark);
    void end(bool mark);

    bool isModified() const;
    void setModified(bool);

    void setSelection(int, int);
    bool hasSelectedText() const;
    QString selectedText() const;
    int selectionStart() const;
    int selectionEnd() const;
    int selectionLength() const;

    bool isUndoAvailable() const;
    bool isRedoAvailable() const;

    void setDragEnabled(bool b);
    bool dragEnabled() const;

    void setCursorMoveStyle(Qt::CursorMoveStyle style);
    Qt::CursorMoveStyle cursorMoveStyle() const;

    QString inputMask() const;
    void setInputMask(const QString &inputMask);
    bool hasAcceptableInput() const;

    void setTextMargins(int left, int top, int right, int bottom);
    void setTextMargins(const QMargins &margins);
    QMargins textMargins() const;

#if QT_CONFIG(action)
    using QWidget::addAction;
    void addAction(QAction *action, ActionPosition position);
    QAction *addAction(const QIcon &icon, ActionPosition position);
#endif

#endif

public Q_SLOTS:

    // void setText(const QString &);
    Q_INVOKABLE void setText(const QString &s)
    {
        get_selfptr()->setText(s);
    }

#if 0
    void clear();
    void selectAll();
    void undo();
    void redo();
#ifndef QT_NO_CLIPBOARD
    void cut();
    void copy() const;
    void paste();
#endif

public:

    void deselect();
    void insert(const QString &);
#ifndef QT_NO_CONTEXTMENU
    QMenu *createStandardContextMenu();
#endif

#endif

Q_SIGNALS:

    void textChanged(const QString &);

#if 0
    void textEdited(const QString &);
    void cursorPositionChanged(int, int);
    void returnPressed();
    void editingFinished();
    void selectionChanged();
    void inputRejected();

public:

    QVariant inputMethodQuery(Qt::InputMethodQuery) const override;
    Q_INVOKABLE QVariant inputMethodQuery(Qt::InputMethodQuery property, QVariant argument) const;
    void timerEvent(QTimerEvent *) override;
    bool event(QEvent *) override;

#endif

public:

  // Конструктор из объекта
  wrapper_QLineEdit(QLineEdit *self) :
    wrapper_QWidget(self) {
    qDebug() << "wrapper_QLineEdit::constructor(self=" << (unsigned long long)self << ")";
  }
    
  // Деструктор
  virtual ~wrapper_QLineEdit() {
    qDebug() << "wrapper_QLineEdit::desctructor";
    delete static_cast<QLineEdit*>(wrapper_QWidget::get_selfptr());
  }

  // Получение константного указателя на объект
  const QLineEdit* get_selfptr() const {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QLineEdit::get_selfptr - got nullptr";
    }
    return static_cast<const QLineEdit*>(wrapper_QWidget::get_selfptr());
  }

  // Получение указателя на объект
  QLineEdit* get_selfptr() {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QLineEdit::get_selfptr - got nullptr";
    }
    return static_cast<QLineEdit*>(wrapper_QWidget::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QLineEdit);

#endif // WRAPPER_QLINEEDIT_H
