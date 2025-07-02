// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifdef _WIN32
  #include <windows.h> 
#endif

#include <QtCore/QDebug>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QMessageBox>
#include <QtQuick/QSGRendererInterface>
#include <QtQuick/QQuickWindow>

#include "parser/gcodepreprocessorutils.h"
#include "parser/gcodeparser.h"
#include "parser/gcodeviewparse.h"

#include "frmmain.h"

static QtMessageHandler originalHandler = nullptr;
static bool debugOutput = false;

static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

    if (!debugOutput) {
        return;
    }

    QFile fMessFile(qApp->applicationDirPath() + "/Candle.log");

    if (!fMessFile.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream tsTextStream(&fMessFile);

    /**
     * Вывести информацию о сообщении. Она может быть дополнительно оформлена
     * шаблоном, указанном в переменной окружения QT_MESSAGE_PATTERN.
     */
    tsTextStream << qFormatLogMessage(type, context, msg) << "\n";
    fMessFile.flush();
    fMessFile.close();
}

void setTranslator(const QString &translationFileName, QTranslator **translator) {
    QTranslator* new_translator = new QTranslator();
    if (new_translator->load(translationFileName)) {
        qApp->removeTranslator(*translator);
        delete *translator;
        *translator = new_translator;
        qApp->installTranslator(*translator);
        qInfo() << "Translation" << translationFileName << "loaded abd installed";
    } else {
        qCritical() << "Error loading" << translationFileName << "translation";
        delete new_translator;
    }
}

void setAllTranslators(const QString &language) {
    QString translationFileName;

    /**
     * Связный список путей к плюгинам и дескрипторов переводов 
     */
    static QMap<QString, QTranslator*> plugin_translators;

    QString pluginsDir = qApp->applicationDirPath() + "/plugins/";
    QStringList pl = QDir(pluginsDir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QString p, pl) {
        translationFileName = pluginsDir + p + "/" + p + "_" + language + ".qm";
        if(QFile::exists(translationFileName)) {
            QTranslator* translator = plugin_translators[p];
            setTranslator(translationFileName, &translator);
            plugin_translators[p] = translator;
        }
    }

    /**
     * Дескриптор перевода приложения
     */
    static QTranslator *candle_translator = nullptr;

    translationFileName = ":/translations/candle_" + language + ".qm";
    if (QFile::exists(translationFileName)) {
        setTranslator(translationFileName, &candle_translator);
    } else {
        qCritical() << "Error loading translation file" << translationFileName;
    }

    /**
     * Дескриптор системного перевода
     */
    static QTranslator *qt_translator = nullptr;

    translationFileName = ":/system_translations/qtbase_" + language + ".qm";
    if (QFile::exists(translationFileName)) {
        setTranslator(translationFileName, &qt_translator);
    }

}

int main(int argc, char *argv[]) {

#ifdef _WIN32
    /**
     * Если программа запущена в консоли, разрешить консольный вывод.
     */
    auto stdout_type = GetFileType(GetStdHandle(STD_OUTPUT_HANDLE));
    if (stdout_type == FILE_TYPE_UNKNOWN) {
        if (AttachConsole(ATTACH_PARENT_PROCESS)) {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
        }
    }
#endif

   /**
    * Установить свой обработчик отладочных/информационных/предупреждающих/аварийных сообщений
    * qDebug(), qInfo(), qWarning(), qCritical(), qFatal()
    */
    originalHandler = qInstallMessageHandler(myMessageOutput);

    /**
     * При наличии в командной строке ключа -DEBUG включить вывод отладочной информации
     */
    for (auto i = 0; i < argc; i++) {
        if (QString(argv[i]).toUpper() == "-DEBUG") {
            debugOutput = true;
            break;
        }
    }


    QApplication a(argc, argv);

    a.setAttribute(Qt::AA_ForceRasterWidgets, false);

    a.setApplicationDisplayName(quoting(PROJECT_NAME));
    a.setApplicationVersion(VERSION_STR);

    qDebug() << "Version:" << a.applicationVersion();

    /**
     * Установить перевод согласно выбранному в настройках языку
     */
    QSettings set(a.applicationDirPath() + "/settings.ini", QSettings::IniFormat);
//!!! По умолчанию нет???
    QString loc = set.value("language", "en").toString();
    if (loc.isEmpty()) {
        qDebug() << "Set defaule language 'en'";
        loc = "en";
    }
    setAllTranslators(loc);

    qDebug() << "Found system styles:" << QStyleFactory::keys();


#if 0 

//    a.setStyle(QStyleFactory::create("Fusion"));


    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(204, 204, 254));
    palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0));
    a.setPalette(palette);

    a.setStyleSheet("QWidget {font-family: \"Ubuntu\";}\
                    QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white;}");

#if 0
                    QMenuBar {background-color: #303030; padding-top: 2px; padding-bottom: 2px;}
                    QMenuBar::item {spacing: 3px; padding: 2px 8px; background: transparent; color: white;}
                    QMenuBar::item:pressed {border: 1px solid #505050; border-bottom: 1px; border-top-left-radius: 3px; border-top-right-radius: 3px; background: #404040; color: white;}
#endif


#endif


#if 0
    /**
     * Дополнить стиль приложения указанием размера размера бордюра, размера шрифта,
     * шрифта шрифта
     */
    a.setStyleSheet(QString("QDialog {border: 1px solid palette(mid);}") +
        QString(" QWidget {font-family: \"" quoting(DEFAULT_FONT_TYPE) "\";}") +
        QString(" QWidget {font-size: " quoting(DEFAULT_FONT_SIZE) "pt}"));
#endif

    frmMain w;
    w.show();

    return a.exec();
}
