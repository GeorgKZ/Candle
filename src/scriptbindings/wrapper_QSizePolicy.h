#ifndef WRAPPER_QSIZEPOLICY_H
#define WRAPPER_QSIZEPOLICY_H

#include <QObject>
#include <QSizePolicy>
#include "wrapper_common.h"


class WRAPPER_DLL_EXPORT wrapper_QSizePolicy : public wrapper_common {

  Q_OBJECT

  // Из файла qsizepolicy.h

public:

  enum Policy {
    Fixed = 0,
    Minimum = QSizePolicy::GrowFlag,
    Maximum = QSizePolicy::ShrinkFlag,
    Preferred = QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag,
    MinimumExpanding = QSizePolicy::GrowFlag | QSizePolicy::ExpandFlag,
    Expanding = QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag | QSizePolicy::ExpandFlag,
    Ignored = QSizePolicy::ShrinkFlag | QSizePolicy::GrowFlag | QSizePolicy::IgnoreFlag
  };
  Q_ENUM(Policy)

  enum ControlType {
    DefaultType      = 0x00000001,
    ButtonBox        = 0x00000002,
    CheckBox         = 0x00000004,
    ComboBox         = 0x00000008,
    Frame            = 0x00000010,
    GroupBox         = 0x00000020,
    Label            = 0x00000040,
    Line             = 0x00000080,
    LineEdit         = 0x00000100,
    PushButton       = 0x00000200,
    RadioButton      = 0x00000400,
    Slider           = 0x00000800,
    SpinBox          = 0x00001000,
    TabWidget        = 0x00002000,
    ToolButton       = 0x00004000
  };
  Q_DECLARE_FLAGS(ControlTypes, ControlType)
  Q_FLAG(ControlTypes)

  // QSizePolicy()
  Q_INVOKABLE wrapper_QSizePolicy() :
    wrapper_common(new QSizePolicy()) {
    qDebug() << "wrapper_QSizePolicy::constructor()";
  }

  // QSizePolicy(Policy horizontal, Policy vertical, ControlType type = DefaultType)
  Q_INVOKABLE wrapper_QSizePolicy(Policy horizontal, Policy vertical, ControlType type = DefaultType) :
    wrapper_common(new QSizePolicy((QSizePolicy::Policy)(int)horizontal, (QSizePolicy::Policy)(int)vertical, (QSizePolicy::ControlType)(int)type)) {
    qDebug() << "wrapper_QSizePolicy::constructor(" << horizontal << "," << vertical << "," << type << ")";
  }

  // Policy horizontalPolicy() const
  // Policy verticalPolicy() const
  // ControlType controlType() const

  // void setHorizontalPolicy(Policy d)
  // void setVerticalPolicy(Policy d)
  // void setControlType(ControlType type)

  // Qt::Orientations expandingDirections() const

  // void setHeightForWidth(bool b)
  // bool hasHeightForWidth() const
  // void setWidthForHeight(bool b)
  // bool hasWidthForHeight() const

  // bool operator==(const QSizePolicy& s) const
  // bool operator!=(const QSizePolicy& s) const

  // operator QVariant() const;

  // int horizontalStretch() const
  // int verticalStretch() const
  // void setHorizontalStretch(int stretchFactor)
  // void setVerticalStretch(int stretchFactor)

  // bool retainSizeWhenHidden() const
  // void setRetainSizeWhenHidden(bool retainSize)

  // void transpose()
  // QSizePolicy transposed() const

public:

  // Конструктор из объекта
  wrapper_QSizePolicy(void *self) : wrapper_common(self) {
    qDebug() << "wrapper_QSizePolicy::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QSizePolicy() override {
    qDebug() << "wrapper_QSizePolicy::destructor";
  }

  // Получение константного указателя на объект
  const QSizePolicy* get_selfptr() const {
    return static_cast<const QSizePolicy*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QSizePolicy* get_selfptr() {
    return static_cast<QSizePolicy*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QSizePolicy)

#endif // WRAPPER_QSIZEPOLICY_H
