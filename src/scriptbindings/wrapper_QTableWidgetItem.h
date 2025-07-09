#ifndef WRAPPER_QTABLEWIDGETITEM_H
#define WRAPPER_QTABLEWIDGETITEM_H

#include <QtCore/QObject>
#include <QtWidgets/QTableWidget>
#include "wrapper_common.h"
#include "wrapper_QIcon.h"
#include "wrapper_QSize.h"

class WRAPPER_DLL_EXPORT wrapper_QTableWidgetItem : public wrapper_common {

  Q_OBJECT

  // из файла qtablewidgetitem.h

public:

  enum ItemType {
    Type = 0,
    UserType = 1000
  };
  Q_ENUM(ItemType)

  Q_INVOKABLE wrapper_QTableWidgetItem(int type = Type) :
    wrapper_common(new QTableWidgetItem((QTableWidgetItem::ItemType)(int)type)) {
    qDebug() << "QTableWidgetItem::constructor(type)";
  }

  // explicit QTableWidgetItem(const QString &text, int type = Type);

  // explicit QTableWidgetItem(const QIcon &icon, const QString &text, int type = Type);

  // QTableWidgetItem(const QTableWidgetItem &other);


//  Q_INVOKABLE wrapper_QTableWidget *tableWidget() const {
//    return new wrapper_QTableWidget(get_selfptr()->tableWidget());
//  }

  Q_INVOKABLE int row() const { return get_selfptr()->row(); }
  Q_INVOKABLE int column() const { return get_selfptr()->column(); }

  Q_INVOKABLE void setSelected(bool select) { get_selfptr()->setSelected(select); }
  Q_INVOKABLE bool isSelected() const { return get_selfptr()->isSelected(); }

//  Q_INVOKABLE Qt::ItemFlags flags() const { return itemFlags; }
//  Q_INVOKABLE void setFlags(Qt::ItemFlags flags);

  Q_INVOKABLE QString text() const { return get_selfptr()->text(); }
  Q_INVOKABLE void setText(const QString &text) { get_selfptr()->setText(text); }

//  Q_INVOKABLE QIcon icon() const
//  Q_INVOKABLE void setIcon(const QIcon &icon);

  Q_INVOKABLE QString statusTip() const { return get_selfptr()->statusTip(); }
  Q_INVOKABLE void setStatusTip(const QString &statusTip) { get_selfptr()->setStatusTip(statusTip); }

#if QT_CONFIG(tooltip)
  // QString toolTip() const
  // void setToolTip(const QString &toolTip);
#endif

#if QT_CONFIG(whatsthis)
  // QString whatsThis() const
  // void setWhatsThis(const QString &whatsThis);
#endif

// QFont font() const

  Q_INVOKABLE Qt::Alignment textAlignment() const { return static_cast<Qt::Alignment>(get_selfptr()->textAlignment()); }
  Q_INVOKABLE void setTextAlignment(Qt::Alignment alignment) { get_selfptr()->setTextAlignment(alignment); }

//  Q_INVOKABLE QBrush background() const
//  Q_INVOKABLE void setBackground(const QBrush &brush)

//  Q_INVOKABLE QBrush foreground() const
//  Q_INVOKABLE void setForeground(const QBrush &brush)

//  Q_INVOKABLE Qt::CheckState checkState() const
//  Q_INVOKABLE void setCheckState(Qt::CheckState state)

  // QSize sizeHint() const
  Q_INVOKABLE QObject *sizeHint() const {
    QSize size = get_selfptr()->sizeHint();
    return new wrapper_QSize(new QSize(size));
  }

  // setSizeHint(const QSize &size)
  Q_INVOKABLE void setSizeHint(const wrapper_QSize &size) {
    get_selfptr()->setSizeHint(*size.get_selfptr());
  }

  // virtual QVariant data(int role) const;
  Q_INVOKABLE virtual QJSValue data(int role) const {
    QVariant value_variant = get_selfptr()->data(role);
    return variantToJSValue(value_variant);
  }

  // virtual void setData(int role, const QVariant &value);
  // QVariant может содержать QString, QColor, QIcon, QPixmap или QSize
  Q_INVOKABLE virtual void setData(int role, const QJSValue &value) {
    qDebug() << "QTableWidgetItem::setData(" << role << ", QJSValue)";
    QVariant variant = jsvalueToVariant(value);
    get_selfptr()->setData(role, variant);
  }

//  Q_INVOKABLE virtual bool operator<(const QTableWidgetItem &other) const { return get_selfptr()->operator<(other); }

//  Q_INVOKABLE virtual void read(QDataStream &in);
//  Q_INVOKABLE virtual void write(QDataStream &out) const;

//  Q_INVOKABLE QTableWidgetItem &operator=(const QTableWidgetItem &other);

  Q_INVOKABLE int type() const { return get_selfptr()->type(); }


public:

  // Конструктор из объекта
  wrapper_QTableWidgetItem(void *self) : wrapper_common(self) {
    qDebug() << "wrapper_QTableWidgetItem::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QTableWidgetItem() override {
    qDebug() << "wrapper_QTableWidgetItem::destructor";
  }

  // Получение константного указателя на объект
  const QTableWidgetItem* get_selfptr() const {
    return static_cast<const QTableWidgetItem*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QTableWidgetItem* get_selfptr() {
    return static_cast<QTableWidgetItem*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QTableWidgetItem)

#endif // WRAPPER_QTABLEWIDGETITEM_H
