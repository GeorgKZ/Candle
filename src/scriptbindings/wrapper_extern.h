#ifndef WRAPPER_EXTERN_H
#define WRAPPER_EXTERN_H

#include "wrapper_export.h"

WRAPPER_DLL_EXPORT void register_wrappers(QJSEngine *se);

/**
 * \brief Преобразование объекта из контейнера QVariant в контейнер JSValue
 *
 */
WRAPPER_DLL_EXPORT QJSValue variantToJSValue(const QVariant& var, QJSEngine *engine);

/**
 * \brief Преобразование объекта из контейнера JSValue в контейнер QVariant с извлечением из прокси-класса
 *
 */
WRAPPER_DLL_EXPORT QVariant jsvalueToVariant(const QJSValue& value);

WRAPPER_DLL_EXPORT QJSValue newScript(QJSEngine *se, QObject* parent);

/**
 * \brief Преобразование объекта из контейнера JSValue в указатель на класс, возможно с извлечением из прокси-класса
 *
 */
WRAPPER_DLL_EXPORT void *jsvalueToObject_ptr(const char *waiting_className, const QJSValue value, QString *returnType = nullptr);

#endif // WRAPPER_EXTERN_H