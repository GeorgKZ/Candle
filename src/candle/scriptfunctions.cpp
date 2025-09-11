#include <QAction>
#include "scriptfunctions.h"
#include "frmmain.h"
#include "wrapper_extern.h"

ScriptFunctions::ScriptFunctions(QObject *parent): QObject(parent), m_frmMain(nullptr)
{
}

void ScriptFunctions::setFrmMain(frmMain *f)
{
    m_frmMain = f;
}

frmMain* ScriptFunctions::getFrmMain()
{
    return m_frmMain;
}

void ScriptFunctions::sendCommands(QString commands, int index)
{
    m_frmMain->sendCommands(commands, index);
}

void ScriptFunctions::sendCommand(QString command, int index, bool showInConsole)
{
    m_frmMain->sendCommand(command, index, showInConsole);
}

void ScriptFunctions::newFile()
{
    m_frmMain->newFile();
}

void ScriptFunctions::loadFile(QString fileName)
{
    m_frmMain->loadFile(fileName);
}

void ScriptFunctions::loadFile(QVariantList data)
{
    QList<QString> l;
    foreach (QVariant v, data) l << v.toString();
    m_frmMain->loadFile(l);
}

bool ScriptFunctions::saveFile()
{
    return m_frmMain->saveChanges(false);
}

void ScriptFunctions::saveFile(QString fileName)
{
    if (m_frmMain->saveProgramToFile(fileName, &m_frmMain->m_programModel)) {
        m_frmMain->m_programFileName = fileName;
        m_frmMain->m_fileChanged = false;

        m_frmMain->addRecentFile(fileName);
        m_frmMain->updateRecentFilesMenu();

        m_frmMain->updateControlsState();
    }
}

int ScriptFunctions::bufferLength()
{
    return m_frmMain->bufferLength();
}

int ScriptFunctions::commandsLength()
{
    return m_frmMain->m_commands.length();
}

int ScriptFunctions::queueLength()
{
    return m_frmMain->m_queue.length();
}

int ScriptFunctions::buttonSize()
{
    return m_frmMain->buttonSize();
}

void ScriptFunctions::addAction(QJSValue action)
{
    m_frmMain->addAction(jsvalueToPointer(QAction, action));
}

void ScriptFunctions::removeAction(QJSValue action)
{
    m_frmMain->removeAction(jsvalueToPointer(QAction, action));
}

void ScriptFunctions::registerType(QString name )
{
    QString wrapper_name = QString("wrapper_") + name;
    qDebug() << "Checking " + wrapper_name;
    QMetaType mtype = QMetaType::fromName(wrapper_name.toUtf8().constData());
    if (mtype.isValid())
    {
        void *classptr = mtype.create();
        qDebug() << "Registered" + wrapper_name;
        mtype.destroy(classptr);
    }

    qDebug() << "Checking " + name;
    mtype = QMetaType::fromName(name.toUtf8().constData());
    if (mtype.isValid())
    {
        void *classptr = mtype.create();
        qDebug() << "Registered" + name;
        mtype.destroy(classptr);
    }



//    int typeId = QMetaType::type(wrapper_name.toUtf8().constData()); //!!! Deprecated!
//    const QMetaObject *metaObject = QMetaType::metaObjectForType(typeId); //!!! Deprecated!
//    QObject &o = *metaObject->newInstance();

//    qjsEngine(this)->globalObject().setProperty( name, qjsEngine(this)->newQMetaObject(&o.staticMetaObject) );
}