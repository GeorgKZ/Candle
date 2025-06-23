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
    qDebug() << "Script::constructor(parent =" << (unsigned long long)parent << ")";
  }

// path()

  Q_INVOKABLE static void importExtension(const QString &name) {
    Q_UNUSED(name);
  }
};

#endif // WRAPPER_SCRIPT_H
