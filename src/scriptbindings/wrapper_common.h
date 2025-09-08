#ifndef WRAPPER_COMMON_H
#define WRAPPER_COMMON_H

#include <QObject>
#include <QVariant>
#include <QJSValue>
#include <QJSManagedValue>
#include <QJSEngine>
#include <QStyledItemDelegate>

#include <QString>
#include <string>
#include <typeinfo>
#if defined(__GNUC__) || defined(__DOXYGEN__)
  #include <cxxabi.h>
#endif

/**
 * В этом файле определены экспортируемые функции:
 * * register_wrappers
 * * variantToJSValue
 * * jsvalueToVariant
 * * newScript
 * * jsvalueToPointer
 */
#include "wrapper_extern.h"

/**
 * \brief Получить строковое представление имени класса
 * \retval строковое представление имени класса
 */
template<typename T>
QString getClassName() {
  const char* type_name = typeid(T).name();
#if defined(__GNUC__) || defined(__DOXYGEN__)
  // Для GCC выполнить преобразование имени класса Demangle
  int status;
  type_name = abi::__cxa_demangle(type_name, nullptr, nullptr, &status);
#endif
  return QString(type_name);
}

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

    /**
     * \brief Конструктор из объекта, который будет храниться в экземпляре прокси-класса
     * \param [in] self указатель на объект, который будет храниться в экземпляре прокси-класса
     */
    explicit wrapper_common(void *self);

    /**
     * \brief Деструктор
     */
    virtual ~wrapper_common() override;

public:

    /**
     * \brief Получение константного указателя на объект, который хранится в экземпляре прокси-класса
     * \retval константный указатель на объект, который хранится в экземпляре прокси-класса
     */
    const void *get_selfptr() const;

    /**
     * \brief Получение указателя на объект, который хранится в экземпляре прокси-класса
     * \retval указатель на объект, который хранится в экземпляре прокси-класса
     */
    void *get_selfptr();

    /**
     * \brief Создание экземпляра прокси-класса указанного по имени типа, содержащего указатель
     * на объект, и помещённого в контейнер JSValue
     * \param [in] class имя класса, которому принадлежит объект
     * \param [in] object указатель на объект, который будет храниться в контейнере JSValue
     */
    #define PointerToJsvalueMacro(class, object) \
        qjsEngine(this)->toScriptValue< wrapper_##class *>( new wrapper_##class ( object ) )

    /**
     * \brief Создание экземпляра прокси-класса по имени метаобъекта, содержащегося в объекте,
     * и помещённого в контейнер JSValue
     * \param [in] object указатель на объект, который будет храниться в контейнере JSValue
     */
    QJSValue PointerToJsvalue(QObject *object) const;

    /**
     * \brief Создание экземпляра прокси-класса указанного по имени типа, содержащего указатель
     * на объект, и помещённого в контейнер JSValue
     * \param [in] className имя класса, которому принадлежит объект
     * \param [in] object указатель на объект, который будет храниться в контейнере JSValue
     */
    QJSValue PointerToJsvalue(const char *className, void *object) const;

    /**
     * \brief Преобразование объекта из контейнера QVariant в контейнер JSValue
     *
     */
    QJSValue variantToJSValue(const QVariant& var) const;

    /**
     * \brief Получение указателя на объект, который хранится в экземпляре прокси-класса,
     * в числовом выражении (для отладки)
     * \retval указатель на объект, который хранится в экземпляре прокси-класса, в числовом выражении
     */
    unsigned long long get_selfvalue() const;

private:

    /**
     * Указатель на хранимый объект
     */
    void* selfptr_;
};

#endif // WRAPPER_COMMON_H
