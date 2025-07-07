#ifndef SCRIPTFUNCTIONS_H
#define SCRIPTFUNCTIONS_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtGui/QAction>

class frmMain;
//class wrapper_QAction;

class ScriptFunctions: public QObject
{
    Q_OBJECT
public:
    ScriptFunctions(QObject *parent = nullptr);
    
    void setFrmMain(frmMain *f);
    frmMain *getFrmMain();

public slots:
    void sendCommands(QString commands, int index = -100);
    void sendCommand(QString command, int index = -100, bool showInConsole = true);
    
    void newFile();
    void loadFile(QString fileName);
    void loadFile(QVariantList data);
    bool saveFile();
    void saveFile(QString fileName);
    
    int bufferLength();
    int commandsLength();
    int queueLength();

    int buttonSize();
//    void addAction(wrapper_QAction *action);
//    void removeAction(wrapper_QAction *action);    

signals:
    void responseReceived(QString command, int tableIndex, QString response);
    void statusReceived(QString status);
    void senderStateChanged(int state);
    void deviceStateChanged(int state);
    void settingsAboutToLoad();
    void settingsLoaded();
    void settingsAboutToSave();
    void settingsSaved();
    void settingsAboutToShow();
    void settingsAccepted();
    void settingsRejected();
    void settingsSetByDefault();
    void pluginsLoaded();

private:
    frmMain *m_frmMain;
};

#endif // SCRIPTFUNCTIONS_H
