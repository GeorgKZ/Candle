#include "wrapper_QSettings.h"

wrapper_QSettings::wrapper_QSettings(const QString &organization, const QString &application, wrapper_QObject *parent) :
  wrapper_QObject(new QSettings(organization, application, parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor(" << organization << "," << application << ", parent)";
}

wrapper_QSettings::wrapper_QSettings(wrapper_QSettings::Scope scope, const QString &organization, const QString &application, wrapper_QObject *parent) :
  wrapper_QObject(new QSettings((QSettings::Scope)(int)scope, organization, application, parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor - scope/org/app/parent" << scope << organization << application;
}

wrapper_QSettings::wrapper_QSettings(wrapper_QSettings::Format format, wrapper_QSettings::Scope scope, const QString &organization, const QString &application, wrapper_QObject *parent) :
  wrapper_QObject(new QSettings((QSettings::Format)(int)format, (QSettings::Scope)(int)scope, organization, application, parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor - format/scope/org/app/parent" << format << scope << organization << application;
}

wrapper_QSettings::wrapper_QSettings(const QString &fileName, wrapper_QSettings::Format format, wrapper_QObject *parent) :
  wrapper_QObject(new QSettings(fileName, (QSettings::Format)(int)format, parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor" << fileName << "," << format << ", parent)";
}

wrapper_QSettings::wrapper_QSettings(wrapper_QObject *parent) :
  wrapper_QObject(new QSettings(parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor(parent)";
}

wrapper_QSettings::wrapper_QSettings(wrapper_QSettings::Scope scope, wrapper_QObject *parent) :
  wrapper_QObject(new QSettings((QSettings::Scope)(int)scope, parent == nullptr ? nullptr : parent->get_selfptr())) {
  qDebug() << "wrapper_QSettings::constructor(" << scope << ", parent)";
}
