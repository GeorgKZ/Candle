#ifndef WRAPPER_QGRIDLAYOUT_H
#define WRAPPER_QGRIDLAYOUT_H

#include <QtCore/QObject>
#include <QtWidgets/QGridLayout>
#include "wrapper_QLayout.h"
#include "wrapper_QWidget.h"

class wrapper_QGridLayout : public wrapper_QLayout {

  Q_OBJECT
  // Из файла QGridLayout.h

public:

  Q_INVOKABLE explicit wrapper_QGridLayout(wrapper_QWidget *parent = nullptr) :
    wrapper_QLayout(new QGridLayout(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QGridLayout::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // QSize sizeHint() const override;

  // QSize minimumSize() const override;

  // QSize maximumSize() const override;

  // void setHorizontalSpacing(int spacing);

  // int horizontalSpacing() const;

  // void setVerticalSpacing(int spacing);

  // int verticalSpacing() const;

  // void setSpacing(int spacing) override;

  // int spacing() const override;

  // void setRowStretch(int row, int stretch);

  // void setColumnStretch(int column, int stretch);

  // int rowStretch(int row) const;

  // int columnStretch(int column) const;

  // void setRowMinimumHeight(int row, int minSize);

  // void setColumnMinimumWidth(int column, int minSize);

  // int rowMinimumHeight(int row) const;

  // int columnMinimumWidth(int column) const;

  // int columnCount() const;

  // int rowCount() const;

  // QRect cellRect(int row, int column) const;

  // bool hasHeightForWidth() const override;

  // int heightForWidth(int) const override;

  // int minimumHeightForWidth(int) const override;

  // Qt::Orientations expandingDirections() const override;

  // void invalidate() override;

  // void addWidget(QWidget *w)
  Q_INVOKABLE void addWidget(const QJSValue &widget) {
    QWidget *w = (QWidget*)jsvalueToObject_ptr("QWidget", widget);
    get_selfptr()->addWidget(w);
  }

  // void addWidget(QWidget *, int row, int column, Qt::Alignment = Qt::Alignment());
  Q_INVOKABLE void addWidget(const QJSValue &widget, int row, int column, Qt::Alignment alignment = Qt::Alignment()) {
    QWidget *w = (QWidget*)jsvalueToObject_ptr("QWidget", widget);
    get_selfptr()->addWidget(w, row, column, alignment);
  }

  // void addWidget(QWidget *, int row, int column, int rowSpan, int columnSpan, Qt::Alignment = Qt::Alignment());
  Q_INVOKABLE void addWidget(const QJSValue &widget, int row, int column, int rowSpan, Qt::Alignment alignment = Qt::Alignment()) {
    QWidget *w = (QWidget*)jsvalueToObject_ptr("QWidget", widget);
    get_selfptr()->addWidget(w, row, column, rowSpan, alignment);
  }

  // void addLayout(QLayout *, int row, int column, Qt::Alignment = Qt::Alignment());
  Q_INVOKABLE void addLayout(const QJSValue &layout, int row, int column, Qt::Alignment alignment = Qt::Alignment()) {
    QLayout *l = (QLayout*)jsvalueToObject_ptr("QLayout", layout);
    get_selfptr()->addLayout(l, row, column, alignment);
  }

  // void addLayout(QLayout *, int row, int column, int rowSpan, int columnSpan, Qt::Alignment = Qt::Alignment());
  Q_INVOKABLE void addLayout(const QJSValue &layout, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment()) {
    QLayout *l = (QLayout*)jsvalueToObject_ptr("QLayout", layout);
    get_selfptr()->addLayout(l, row, column, rowSpan, columnSpan, alignment);
  }

  // void setOriginCorner(Qt::Corner);

  // Qt::Corner originCorner() const;

  // QLayoutItem *itemAt(int index) const override;

  // QLayoutItem *itemAtPosition(int row, int column) const;

  // QLayoutItem *takeAt(int index) override;

  // int count() const override;

  // void setGeometry(const QRect&) override;

  // void addItem(QLayoutItem *item, int row, int column, int rowSpan = 1, int columnSpan = 1, Qt::Alignment = Qt::Alignment());

  // void setDefaultPositioning(int n, Qt::Orientation orient);

  // void getItemPosition(int idx, int *row, int *column, int *rowSpan, int *columnSpan) const;

public:

  // Конструктор из объекта
  explicit wrapper_QGridLayout(QGridLayout* self) :
    wrapper_QLayout(self) {
    qDebug() << "wrapper_QGridLayout::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QGridLayout() {
    delete static_cast<QGridLayout*>(wrapper_QLayout::get_selfptr());
  }

  // Получение константного указателя на объект
  const QGridLayout* get_selfptr() const {
    if (wrapper_QLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QGridLayout::get_selfptr - got nullptr";
    }
    return static_cast<const QGridLayout*>(wrapper_QLayout::get_selfptr());
  }

  // Получение указателя на объект
  QGridLayout* get_selfptr() {
    if (wrapper_QLayout::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QGridLayout::get_selfptr - got nullptr";
    }
    return static_cast<QGridLayout*>(wrapper_QLayout::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QGridLayout);

#endif // WRAPPER_QGRIDLAYOUT_H
