#ifndef WRAPPER_QCOMBOBOX_H
#define WRAPPER_QCOMBOBOX_H

#include <QtCore/QObject>
#include <QtWidgets/QComboBox>
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QComboBox : public wrapper_QWidget {

  Q_OBJECT

  // из файла qcombobox.h

#if 0
  Q_PROPERTY(bool editable       READ isEditable WRITE setEditable)
  Q_PROPERTY(int count           READ count)
#endif
  Q_PROPERTY(QString currentText
    READ currentText
    WRITE setCurrentText
    NOTIFY currentTextChanged
    USER true)
#if 0
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QVariant currentData READ currentData)
    Q_PROPERTY(int maxVisibleItems READ maxVisibleItems WRITE setMaxVisibleItems)
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
    Q_PROPERTY(InsertPolicy insertPolicy READ insertPolicy WRITE setInsertPolicy)
    Q_PROPERTY(SizeAdjustPolicy sizeAdjustPolicy READ sizeAdjustPolicy WRITE setSizeAdjustPolicy)
    Q_PROPERTY(int minimumContentsLength         READ minimumContentsLength WRITE setMinimumContentsLength)
    Q_PROPERTY(QSize iconSize                    READ iconSize WRITE setIconSize)
    Q_PROPERTY(QString placeholderText           READ placeholderText WRITE setPlaceholderText)
    Q_PROPERTY(bool duplicatesEnabled            READ duplicatesEnabled WRITE setDuplicatesEnabled)
    Q_PROPERTY(bool frame                        READ hasFrame WRITE setFrame)
    Q_PROPERTY(int modelColumn           READ modelColumn WRITE setModelColumn)
#endif

public:

  Q_INVOKABLE explicit wrapper_QComboBox(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(parent) {
    qDebug() << "wrapper_QComboBox::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
}

#if 0
    int maxVisibleItems() const;
    void setMaxVisibleItems(int maxItems);

    int count() const;
    void setMaxCount(int max);
    int maxCount() const;

    bool duplicatesEnabled() const;
    void setDuplicatesEnabled(bool enable);

    void setFrame(bool);
    bool hasFrame() const;

    inline int findText(const QString &text,
                        Qt::MatchFlags flags = static_cast<Qt::MatchFlags>(Qt::MatchExactly|Qt::MatchCaseSensitive)) const
        { return findData(text, Qt::DisplayRole, flags); }
    int findData(const QVariant &data, int role = Qt::UserRole,
                 Qt::MatchFlags flags = static_cast<Qt::MatchFlags>(Qt::MatchExactly|Qt::MatchCaseSensitive)) const;

    enum InsertPolicy {
        NoInsert,
        InsertAtTop,
        InsertAtCurrent,
        InsertAtBottom,
        InsertAfterCurrent,
        InsertBeforeCurrent,
        InsertAlphabetically
    };
    Q_ENUM(InsertPolicy)

    InsertPolicy insertPolicy() const;
    void setInsertPolicy(InsertPolicy policy);

    enum SizeAdjustPolicy {
        AdjustToContents,
        AdjustToContentsOnFirstShow,
        AdjustToMinimumContentsLengthWithIcon
    };
    Q_ENUM(SizeAdjustPolicy)

    SizeAdjustPolicy sizeAdjustPolicy() const;
    void setSizeAdjustPolicy(SizeAdjustPolicy policy);
    int minimumContentsLength() const;
    void setMinimumContentsLength(int characters);
    QSize iconSize() const;
    void setIconSize(const QSize &size);

    void setPlaceholderText(const QString &placeholderText);
    QString placeholderText() const;

    bool isEditable() const;
    void setEditable(bool editable);
    void setLineEdit(QLineEdit *edit);
    QLineEdit *lineEdit() const;
#ifndef QT_NO_VALIDATOR
    void setValidator(const QValidator *v);
    const QValidator *validator() const;
#endif

#if QT_CONFIG(completer)
    void setCompleter(QCompleter *c);
    QCompleter *completer() const;
#endif

    QAbstractItemDelegate *itemDelegate() const;
    void setItemDelegate(QAbstractItemDelegate *delegate);

    QAbstractItemModel *model() const;
    virtual void setModel(QAbstractItemModel *model);

    QModelIndex rootModelIndex() const;
    void setRootModelIndex(const QModelIndex &index);

    int modelColumn() const;
    void setModelColumn(int visibleColumn);

    int currentIndex() const;
#endif
    Q_INVOKABLE QString currentText() const {return get_selfptr()->currentText(); }
#if 0
    QVariant currentData(int role = Qt::UserRole) const;

    QString itemText(int index) const;
    QIcon itemIcon(int index) const;
    QVariant itemData(int index, int role = Qt::UserRole) const;

    inline void addItem(const QString &text, const QVariant &userData = QVariant());
    inline void addItem(const QIcon &icon, const QString &text,
                        const QVariant &userData = QVariant());
    inline void addItems(const QStringList &texts)
        { insertItems(count(), texts); }

    inline void insertItem(int index, const QString &text, const QVariant &userData = QVariant());
    void insertItem(int index, const QIcon &icon, const QString &text,
                    const QVariant &userData = QVariant());
    void insertItems(int index, const QStringList &texts);
    void insertSeparator(int index);

    void removeItem(int index);

    void setItemText(int index, const QString &text);
    void setItemIcon(int index, const QIcon &icon);
    void setItemData(int index, const QVariant &value, int role = Qt::UserRole);

    QAbstractItemView *view() const;
    void setView(QAbstractItemView *itemView);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    virtual void showPopup();
    virtual void hidePopup();

    bool event(QEvent *event) override;
    QVariant inputMethodQuery(Qt::InputMethodQuery) const override;
    Q_INVOKABLE QVariant inputMethodQuery(Qt::InputMethodQuery query, const QVariant &argument) const;
#endif

public Q_SLOTS:

  Q_INVOKABLE void clear() { get_selfptr()->clear(); }
  Q_INVOKABLE void clearEditText() { get_selfptr()->clearEditText(); }
  Q_INVOKABLE void setEditText(const QString &text) { get_selfptr()->setEditText(text); }
  Q_INVOKABLE void setCurrentIndex(int index) { get_selfptr()->setCurrentIndex(index); }
  Q_INVOKABLE void setCurrentText(const QString &text) { get_selfptr()->setCurrentText(text); }

Q_SIGNALS:

  void editTextChanged(const QString &);
  void activated(int index);
  void textActivated(const QString &);
  void highlighted(int index);
  void textHighlighted(const QString &);
  void currentIndexChanged(int index);
  void currentTextChanged(const QString &);

public:

  Q_INVOKABLE void addItem(const QString &text) { get_selfptr()->addItem(text); }

  Q_INVOKABLE void addItems(const QStringList &texts) { get_selfptr()->addItems(texts); }



public:

  // Конструктор из объекта
  wrapper_QComboBox(QComboBox *self) :
    wrapper_QWidget(self) {
    qDebug() << "wrapper_QComboBox::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const QComboBox* get_selfptr() const {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QConboBox::get_selfptr - got nullptr";
    }
    return static_cast<const QComboBox*>(wrapper_QWidget::get_selfptr());
  }

  // Получение указателя на объект
  QComboBox* get_selfptr() {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QConboBox::get_selfptr - got nullptr";
    }
    return static_cast<QComboBox*>(wrapper_QWidget::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QComboBox() {
  }
};

Q_DECLARE_METATYPE(wrapper_QComboBox);

#endif // WRAPPER_QCOMBOBOX_H
