#ifndef WRAPPER_QSETTINGS_H
#define WRAPPER_QSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QJSValue>
#include <QJSManagedValue>
#include <QWidget>
#include "wrapper_QObject.h"
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QSettings : public wrapper_QObject {

  Q_OBJECT

  // Из файла qsettings.h

public:

  enum Status {
    NoError = 0,
    AccessError,
    FormatError
  };
#if !defined(__DOXYGEN__)
  Q_ENUM(Status)
#endif

  enum Format {
    NativeFormat,
    IniFormat,
#if defined(Q_OS_WIN) || defined(Q_CLANG_QDOC)
    Registry32Format,
    Registry64Format,
#endif
    InvalidFormat = 16,
    CustomFormat1,
    CustomFormat2,
    CustomFormat3,
    CustomFormat4,
    CustomFormat5,
    CustomFormat6,
    CustomFormat7,
    CustomFormat8,
    CustomFormat9,
    CustomFormat10,
    CustomFormat11,
    CustomFormat12,
    CustomFormat13,
    CustomFormat14,
    CustomFormat15,
    CustomFormat16
  };
#if !defined(__DOXYGEN__)
  Q_ENUM(Format)
#endif

  enum Scope {
    UserScope,
    SystemScope
  };
#if !defined(__DOXYGEN__)
  Q_ENUM(Scope)
#endif

  Q_INVOKABLE explicit wrapper_QSettings(const QString &organization, const QString &application = QString(), wrapper_QObject *parent = nullptr);
  Q_INVOKABLE wrapper_QSettings(Scope scope, const QString &organization, const QString &application = QString(), wrapper_QObject *parent = nullptr);
  Q_INVOKABLE wrapper_QSettings(Format format, Scope scope, const QString &organization, const QString &application = QString(), wrapper_QObject *parent = nullptr);
  Q_INVOKABLE wrapper_QSettings(const QString &fileName, Format format, wrapper_QObject *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QSettings(wrapper_QObject *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QSettings(Scope scope, wrapper_QObject *parent = nullptr);

  // void clear()
  Q_INVOKABLE void clear() {
    get_selfptr()->clear();
  }

  // void sync()
  Q_INVOKABLE void sync() {
    get_selfptr()->sync();
  }

  // Status status() const
  Q_INVOKABLE Status status() const {
    return (Status)(int)(get_selfptr()->status());
  }

  // bool isAtomicSyncRequired() const
  Q_INVOKABLE bool isAtomicSyncRequired() const {
    return get_selfptr()->isAtomicSyncRequired();
  }

  // void setAtomicSyncRequired(bool enable)
  Q_INVOKABLE void setAtomicSyncRequired(bool enable) {
    get_selfptr()->setAtomicSyncRequired(enable);
  }

  // void beginGroup(const QString &prefix)
  Q_INVOKABLE void beginGroup(const QString &prefix) {
    get_selfptr()->beginGroup(prefix);
  }

  // void endGroup()
  Q_INVOKABLE void endGroup() {
    get_selfptr()->endGroup();
  }

  // QString group() const
  Q_INVOKABLE QString group() const {
    return get_selfptr()->group();
  }

  // int beginReadArray(const QString &prefix)
  Q_INVOKABLE int beginReadArray(const QString &prefix) {
    return get_selfptr()->beginReadArray(prefix);
  }

  // void beginWriteArray(const QString &prefix, int size = -1)
  Q_INVOKABLE void beginWriteArray(const QString &prefix, int size = -1) {
    get_selfptr()->beginWriteArray(prefix, size);
  }

  // void endArray()
  Q_INVOKABLE void endArray() {
    get_selfptr()->endArray();
  }

  // void setArrayIndex(int i)
  Q_INVOKABLE void setArrayIndex(int i) {
    get_selfptr()->setArrayIndex(i);
  }

//  Q_INVOKABLE QStringList allKeys() const;
//  Q_INVOKABLE QStringList childKeys() const;
//  Q_INVOKABLE QStringList childGroups() const;

  // bool isWritable() const;
  Q_INVOKABLE bool isWritable() const {
    return get_selfptr()->isWritable();
  }

  // void setValue(QAnyStringView key, const QVariant &value)
  Q_INVOKABLE void setValue(const QString& key, const QJSValue &value) {
    QVariant variant = jsvalueToVariant(value);
    qDebug() << "wrapper_QSettings::setValue(" << key << "," << variant << ")";
    get_selfptr()->setValue(key, variant);
  }

  // QVariant value(QAnyStringView key, const QVariant &defaultValue) const;
  Q_INVOKABLE QJSValue value(const QString& key, const QString &defaultValue) const {
    qDebug() << "wrapper_QSettings::value(" << key << "," << defaultValue << ") const";
    return variantToJSValue(get_selfptr()->value(key, defaultValue));
  }

  // QVariant value(QAnyStringView key) const;
  Q_INVOKABLE QJSValue value(const QString& key) const {
    qDebug() << "wrapper_QSettings::value(" << key << ") const";
    return variantToJSValue(get_selfptr()->value(key));
  }

  // void remove(QAnyStringView key);
  Q_INVOKABLE void remove(const QString &key) {
    get_selfptr()->remove(key);
  }

  // bool contains(QAnyStringView key) const;
  Q_INVOKABLE bool contains(const QString &key) const {
    return get_selfptr()->contains(key);
  }

public:

  // Конструктор из объекта
  explicit wrapper_QSettings(void *self) : wrapper_QObject(self) {
    qDebug() << "wrapper_QSettings::constructor(self=" << get_selfvalue() << ")";
  }

  // Деструктор
  virtual ~wrapper_QSettings() override {
    qDebug() << "wrapper_QSettings::destructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QSettings* get_selfptr() const {
    return static_cast<const QSettings*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QSettings* get_selfptr() {
    return static_cast<QSettings*>(wrapper_common::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QSettings)

#endif // WRAPPER_QSETTINGS_H
