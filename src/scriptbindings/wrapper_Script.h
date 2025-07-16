#ifndef WRAPPER_SCRIPT_H
#define WRAPPER_SCRIPT_H

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtCore/QString>

class Script: public QObject {

  Q_OBJECT

public:
//!!! без враппера?
  Q_INVOKABLE Script(QObject* parent = nullptr) : QObject(parent) {
    qDebug() << "Script::constructor(parent =" << reinterpret_cast<unsigned long long>(parent) << ")";
  }

// path()

};

#endif // WRAPPER_SCRIPT_H
