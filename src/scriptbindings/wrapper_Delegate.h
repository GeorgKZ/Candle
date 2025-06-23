#ifndef WRAPPER_DELEGATE_H
#define WRAPPER_DELEGATE_H

#include <QtCore/QObject>
#include <QtCore/QtCore>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QModelIndex>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QStyledItemDelegate>
#include "wrapper_QAbstractItemDelegate.h"
#include "wrapper_QStyledItemDelegate.h"

class WRAPPER_DLL_EXPORT IconDelegate : public QStyledItemDelegate {

  Q_OBJECT

public:

  explicit IconDelegate(const QString pluginPath, QObject *parent = nullptr) :
    QStyledItemDelegate(parent) {
    m_pluginPath = pluginPath;
  }

  ~IconDelegate() {}

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

    Q_UNUSED(option)
    Q_UNUSED(index)

    qDebug() << "IconDelegate::createEditor";

    QDir *dir = new QDir(m_pluginPath + "/images");
    QStringList flist = dir->entryList(QDir::Files);
    QComboBox *combo = new QComboBox(parent);

    for (auto i = 0; i < flist.length(); i++) {
        QIcon *icon = new QIcon(m_pluginPath + "/images/" + flist[i]);
        combo->addItem(*icon, flist[i]);
    }

    return combo;
  }

  void setEditorData(QWidget *editor, const QModelIndex &index) const override {

    qDebug() << "IconDelegate::setEditorData";

    QVariant data = index.data();
//!!! проверить data

    const char *className = editor->metaObject()->className();
    if (strcmp(className, "QComboBox") == 0) {
      ((QComboBox*)editor)->setCurrentText(data.toString());
    } else {
      qCritical() << "IconDelegate::setEditorData - wrong editor type " << className << ", not QComboBox";
    }
  }

  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {

    qDebug() << "IconDelegate::setModelData";

    const char *className = editor->metaObject()->className();
    if (strcmp(className, "QComboBox") == 0) {
      model->setData(index, ((QComboBox*)editor)->currentText());
      model->setData(index, ((QComboBox*)editor)->itemIcon(((QComboBox*)editor)->currentIndex()), Qt::DecorationRole);
    } else {
      qCritical() << "IconDelegate::setModelData - wrong editor type " << className << ", not QComboBox";
    }
  }

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    Q_UNUSED(index)
    qDebug() << "IconDelegate::updateEditorGeometry";

    const char *className = editor->metaObject()->className();
    if (strcmp(className, "QComboBox") == 0) {
      ((QComboBox*)editor)->setGeometry(option.rect);
    } else {
      qCritical() << "IconDelegate::updateEditorGeometry - wrong editor type " << className << ", not QComboBox";
    }
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QColor(0xcdcdff));
    }

    QVariant q = index.data(Qt::DecorationRole);
    if (q.isValid()) {
      const char *className = q.typeName();
      qDebug() << "IconDelegate::paint: row=" << index.row() << ", column=" <<  index.column() << " datatype=" << className;

      if (q.canConvert<QIcon>()) {

        QIcon icon = q.value<QIcon>();
        icon.paint(painter, option.rect);
      } else {
        qCritical() << "IconDelegate::paint - wrong data type";
      }
    }

    if (option.state & QStyle::State_HasFocus) {
        QPen *p = new QPen();
        p->setStyle(Qt::DotLine);
        painter->setPen(*p);
        painter->drawRect(option.rect.adjusted(1, 0, -2, -1));
    }
  }

private:

  QString m_pluginPath;
};

class wrapper_IconDelegate : public wrapper_QStyledItemDelegate {

  Q_OBJECT

public:

  Q_INVOKABLE explicit wrapper_IconDelegate(const QString pluginPath, const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QStyledItemDelegate(new IconDelegate(pluginPath, (QObject*)jsvalueToObject_ptr("QObject", parent))) {
  }

public:

  // Конструктор из объекта
  wrapper_IconDelegate(IconDelegate *self) :
    wrapper_QStyledItemDelegate(self) {
    qDebug() << "wrapper_IconDelegate::constructor(self=" << (unsigned long long)self << ")";
  }

  // Получение константного указателя на объект
  const IconDelegate* get_selfptr() const {
    if (wrapper_QStyledItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<const IconDelegate*>(wrapper_QStyledItemDelegate::get_selfptr());
  }

  // Получение указателя на объект
  IconDelegate* get_selfptr() {
    if (wrapper_QStyledItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<IconDelegate*>(wrapper_QStyledItemDelegate::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_IconDelegate() {
    qDebug() << "wrapper_IconDelegate::destructor";
  }
};


class CodeDelegate : public QStyledItemDelegate {

  Q_OBJECT

public:

  explicit CodeDelegate(QObject *parent = nullptr) :
    QStyledItemDelegate(parent) {
    m_adjustHeight = false;
    m_alignment = Qt::AlignCenter;
  }

  ~CodeDelegate() { }

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

    Q_UNUSED(option)
    Q_UNUSED(index)

    qDebug() << "CodeDelegate::createEditor"; 
    QTextEdit *widget = new QTextEdit(parent);
    return widget;
  }

  void setEditorData(QWidget *editor, const QModelIndex &index) const override {

    QVariant data = index.data();
    //!!! Проверить тип data
    ((QTextEdit *)editor)->setPlainText(data.toString());
    QTextCursor c = ((QTextEdit *)editor)->textCursor();
    c.movePosition(QTextCursor::End);
    ((QTextEdit *)editor)->setTextCursor(c);    
  }

  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {

    qDebug() << "CodeDelegate::setmodelData";

        model->setData(index, ((QTextEdit *)editor)->toPlainText());
    }

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

    Q_UNUSED(index)

    qDebug() << "CodeDelegate::updateEditorGeometry";

      QRect r = option.rect;

      if (m_adjustHeight) {
        QTableView *t = (QTableView *)parent(); //!!! Проверить тип
        r.setTop(0);
        r.setHeight(t->height() - t->horizontalHeader()->height() - t->frameWidth() * 2);
      }

      ((QTextEdit *)editor)->setGeometry(r);
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

    qDebug() << "CodeDelegate::paint";

    QString q = index.data().toString();

    if (option.state & QStyle::State_Selected) {
      painter->fillRect(option.rect, QColor(0xcdcdff));
    }

    if (q.size() != 0) { //!!!
      QFontMetrics m(option.font);
      QRect r = option.rect.adjusted(4, 4, -4, -4);
      QStringList l = q.split("\n");
      int n = l.length();
      int k = qMin(r.height() / m.lineSpacing(), n);
      QString s = "";

      for (auto i = 0; i < k; i++) {
        if ((i == (k - 1)) && (k < n)) s += "..."; else s += l[i];
        if (i < (k - 1)) s += "\n";
      }

      painter->drawText(r, m_alignment | 0, s, &r);
    }

    if (option.state & QStyle::State_HasFocus) {
      QPen p;
      p.setStyle(Qt::DotLine);
      painter->setPen(p);
      painter->drawRect(option.rect.adjusted(1, 0, -2, -1));
    }
  }

  private:

  bool m_adjustHeight;

  Qt::Alignment m_alignment;
};


class wrapper_CodeDelegate : public wrapper_QStyledItemDelegate {

  Q_OBJECT

public:

  Q_INVOKABLE explicit wrapper_CodeDelegate(const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QStyledItemDelegate(new CodeDelegate((QObject*)jsvalueToObject_ptr("QObject", parent))) {
  }

public:

  // Конструктор из объекта
  wrapper_CodeDelegate(CodeDelegate *self) :
    wrapper_QStyledItemDelegate(self) {
    qDebug() << "wrapper_CodeDelegate::constructor(self=" << (unsigned long long)self << ")";
  }

  // Получение константного указателя на объект
  const CodeDelegate* get_selfptr() const {
    if (wrapper_QStyledItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<const CodeDelegate*>(wrapper_QStyledItemDelegate::get_selfptr());
  }

  // Получение указателя на объект
  CodeDelegate* get_selfptr() {
    if (wrapper_QStyledItemDelegate::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QStyledItemDelegate::get_selfptr - got nullptr";
    }
    return static_cast<CodeDelegate*>(wrapper_QStyledItemDelegate::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_CodeDelegate() {
    qDebug() << "wrapper_CodeDelegate::destructor";
  }
};

#endif // WRAPPER_DELEGATE_H
