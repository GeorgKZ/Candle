#ifndef WRAPPER_QUILOADER_H
#define WRAPPER_QUILOADER_H

#include <QtCore/QObject>
#include <QtQmlIntegration>
#include <QtUiTools/QUiLoader>
#include "wrapper_QDir.h"
#include "wrapper_QFile.h"
#include "wrapper_QWidget.h"
#include "wrapper_QObject.h"

class wrapper_QIODevice;

class WRAPPER_DLL_EXPORT wrapper_QUiLoader : public wrapper_QObject {

  Q_OBJECT
  // Из файла quiloader.h
public:

  // explicit QUiLoader(QObject *parent = nullptr);
  Q_INVOKABLE explicit wrapper_QUiLoader(const QJSValue &parent = QJSValue(QJSValue::UndefinedValue)) :
    wrapper_QObject(new QUiLoader(jsvalueToPointer(QObject, parent))) {}


//  QStringList pluginPaths() const;

//  void clearPluginPaths();

  //  void addPluginPath(const QString &path);
  Q_INVOKABLE void addPluginPath(const QString &path) {
    get_selfptr()->addPluginPath(path);
  }

  // QWidget *load(QIODevice *device, QWidget *parentWidget = nullptr);
  Q_INVOKABLE QJSValue load(const QJSValue &device, const QJSValue &parentWidget = QJSValue(QJSValue::UndefinedValue)) {
    QIODevice *_device = jsvalueToPointer(QIODevice, device);
    QWidget *_parentWidget = jsvalueToPointer(QWidget, parentWidget);


    qDebug() << "wrapper_QUiLoader::load(" << (unsigned long long)_device << ")...";

    QWidget *new_widget = get_selfptr()->load(_device, _parentWidget);

    qDebug() << "wrapper_QUiLoader::load(" << (unsigned long long)_device << ") -> " << (unsigned long long)new_widget;

    return wrapperFactory(new_widget->metaObject()->className(), new_widget);
  }

//  QStringList availableWidgets() const;

//  QStringList availableLayouts() const;

//  virtual QWidget *createWidget(const QString &className, QWidget *parent = nullptr, const QString &name = QString());

//  virtual QLayout *createLayout(const QString &className, QObject *parent = nullptr, const QString &name = QString());

//  virtual QActionGroup *createActionGroup(QObject *parent = nullptr, const QString &name = QString());

//  virtual QAction *createAction(QObject *parent = nullptr, const QString &name = QString());

  // void setWorkingDirectory(const QDir &dir);
  Q_INVOKABLE void setWorkingDirectory(const QJSValue& value) {
    QDir *dir = jsvalueToPointer(QDir, value);
    get_selfptr()->setWorkingDirectory(*dir);
  }

//  QDir workingDirectory() const;

//  void setLanguageChangeEnabled(bool enabled);
  Q_INVOKABLE void setLanguageChangeEnabled(bool enabled) {
    get_selfptr()->setLanguageChangeEnabled(enabled);
  }

//  bool isLanguageChangeEnabled() const;
  Q_INVOKABLE bool isLanguageChangeEnabled() const {
    return get_selfptr()->isLanguageChangeEnabled();
  }

//  void setTranslationEnabled(bool enabled);
  Q_INVOKABLE void setTranslationEnabled(bool enabled) {
    get_selfptr()->setTranslationEnabled(enabled);
  }

//  bool isTranslationEnabled() const;
  Q_INVOKABLE bool isTranslationEnabled() const {
    return get_selfptr()->isTranslationEnabled();
  }

//  QString errorString() const;
  Q_INVOKABLE QString errorString() const {
    return get_selfptr()->errorString();
  }

public:

  // Конструктор из объекта
  explicit wrapper_QUiLoader(QUiLoader* self) :
    wrapper_QObject(self) {
    qDebug() << "wrapper_QUiLoader::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QUiLoader() {
    qDebug() << "wrapper_QUiLoader::destructor(self=" << (unsigned long long)wrapper_QObject::get_selfptr() << ")";
    delete static_cast<QUiLoader*>(wrapper_QObject::get_selfptr());
  }

  // Получение константного указателя на объект
  const QUiLoader* get_selfptr() const {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "const wrapper_QUiLoader::get_selfptr - got nullptr";
    }
    return static_cast<const QUiLoader*>(wrapper_QObject::get_selfptr());
  }

  // Получение указателя на объект
  QUiLoader* get_selfptr() {
    if (wrapper_QObject::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QUiLoader::get_selfptr - got nullptr";
    }
    return static_cast<QUiLoader*>(wrapper_QObject::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QUiLoader);

#endif // WRAPPER_QUILOADER_H
