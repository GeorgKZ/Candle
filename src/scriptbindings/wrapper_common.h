#ifndef WRAPPER_COMMON_H
#define WRAPPER_COMMON_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtQml/QJSValue>
#include <QtQml/QJSManagedValue>
#include <QtQml/QJSEngine>
#include <QtWidgets/QStyledItemDelegate>

#include <QtCore/QString>
#include <string>
#include <typeinfo>
#if defined(__GNUC__) || defined(__DOXYGEN__)
  #include <cxxabi.h>
#endif

#include "wrapper_export.h"

//extern QJSEngine *globalEngine;

template<typename T>
QString getClassName() {
  const char* type_name = typeid(T).name();
#if defined(__GNUC__) || defined(__DOXYGEN__)
  // Для GCC выполнить преобразование имени класса Demangle
  int status;
  type_name = abi::__cxa_demangle(type_name, 0, 0, &status);
#endif
  return QString(type_name);
}

/**
 * \brief Преобразование объекта из контейнера QVariant в контейнер JSValue
 *
 */
__declspec(dllexport) QJSValue variantToJSValue(const QVariant& var, QJSEngine *engine);

/**
 * \brief Преобразование объекта из контейнера JSValue в контейнер QVariant с извлечением из прокси-класса
 *
 */
__declspec(dllexport) QVariant jsvalueToVariant(const QJSValue& value);

/**
 * \brief Базовый класс для прокси-классов
 *
 * В этом классе содержится указатель на хранимый объект. Этот класс не может создавать объект
 * прокси-класса, хранимый объект в нём не создаётся и не уничтожается, только хранится,
 * передаваемый из конструкторов классов-наследников.
 */
class WRAPPER_DLL_EXPORT wrapper_common : public QObject {

  Q_OBJECT

protected:

  // Конструктор по умолчанию отсутствует
  // wrapper_common() = 0; //: QObject(), selfptr_(nullptr) {}

  // Конструктор из объекта
  wrapper_common(void *self) : selfptr_(self) {
    qDebug() << "wrapper_common::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_common() {
    qDebug() << "wrapper_common::destructor";
  }

public:

  // Получение константного указателя на объект
  const void* get_selfptr() const {
    if (selfptr_ == nullptr) {
      qCritical() << "const wrapper_common::get_selfptr - got nullptr";
    }
    return selfptr_;
  }

  // Получение указателя на объект
  void* get_selfptr() {
    if (selfptr_ == nullptr) {
      qCritical() << "wrapper_common::get_selfptr - got nullptr";
    }
    return selfptr_;
  }

    /**
     * \brief Создание экземпляра прокси-класса указанного по имени типа, содержащего указатель
     * на объект, и помещённого в контейнер JSValue
     *
     */
    QJSValue wrapperFactory(const char *className, void *object) const;

    /**
     * \brief Преобразование объекта из контейнера QVariant в контейнер JSValue
     *
     */
    QJSValue variantToJSValue(const QVariant& var) const;

    private:

    //!!! Использовать QSharedPointer
    // Указатель на хранимый объект
    void* selfptr_;
};

void *jsvalueToObject_ptr(const char *waiting_className, const QJSValue value, QString *returnType = nullptr);

#endif // WRAPPER_COMMON_H
