// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QtCore/QDebug>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QFile>
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

QTranslator* candle_translator = nullptr;

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
     * Вывести информацию о сообщении без перевода строки - его необходимо добавить в шаблоне,
     * указанном в переменной окружения QT_MESSAGE_PATTERN.
     */
    tsTextStream << qFormatLogMessage(type, context, msg);
    fMessFile.flush();
    fMessFile.close();
}


int main(int argc, char *argv[]) {

  // Установить свой обработчик отладочных/информационных/предупреждающих/аварийных сообщений
  // qDebug(), qInfo(), qWarning(), qCritical(), qFatal()
  originalHandler = qInstallMessageHandler(myMessageOutput);

  for (auto i = 0; i < argc; i++) {
      if (QString(argv[i]).toUpper() == "-DEBUG") {
          debugOutput = true;
          break;
      }
  }


//#ifdef UNIX
//    bool styleOverrided = false;
//    for (int i = 0; i < argc; i++) if (QString(argv[i]).toUpper() == "-STYLE") {
//        styleOverrided = true;
//        break;
//    }
//#endif

    QApplication a(argc, argv);

    a.setAttribute(Qt::AA_ForceRasterWidgets, false);

    a.setApplicationDisplayName(PROJECT_NAME);
    a.setApplicationVersion(VERSION_STR);

    int fontID = QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    if (fontID == -1) {
        qCritical() << "Adding font error";
    } else {
        qInfo() << "Installed fonts:" << QFontDatabase::applicationFontFamilies(fontID);
        a.setFont(QFont(QFontDatabase::applicationFontFamilies(fontID).at(0), 9));
    }

    QSettings set(a.applicationDirPath() + "/settings.ini", QSettings::IniFormat);
    QString loc = set.value("language", "en").toString();

    QString translationsFolder = qApp->applicationDirPath() + "/translations/";
    QString translationFileName = translationsFolder + "candle_" + loc + ".qm";

    if(QFile::exists(translationFileName)) {
        qInfo() << "Loading Candle translation from" << translationFileName << "...";
        candle_translator = new QTranslator();
        if (candle_translator->load(translationFileName)) {
            qInfo() << "Candle translation" << translationFileName << "loaded";
            a.installTranslator(candle_translator);
        } else {
            qCritical() << "Error loading Candle translation";
            delete candle_translator;
        }
    }

    QString baseTranslationFileName = translationsFolder + "qtbase_" + loc + ".qm";
    if(QFile::exists(baseTranslationFileName)) {
        qInfo() << "Loading Qt translation from" << baseTranslationFileName << "...";
        QTranslator* baseTranslator = new QTranslator();
        if (baseTranslator->load(baseTranslationFileName)) {
            qInfo() << "Qt translation" << baseTranslationFileName << "loaded";
            a.installTranslator(baseTranslator);
        } else {
            qCritical() << "Error loading Qt translation";
            delete baseTranslator;
        }
    }


#ifdef UNIX
//    if (!styleOverrided) {
//            foreach (QString str, QStyleFactory::keys()) {
//            qInfo() << "found style" << str;
//            if (str.contains("GTK+")) {
//                qInfo() << "setting style:" << str;
//                a.setStyle(QStyleFactory::create(str));
//                break;
//            }
//        }
//    }
#endif

#if 0 

//    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(204, 204, 254));
    palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0));
    a.setPalette(palette);

    a.setStyleSheet("QWidget {font-family: \"Ubuntu\";}\
                    QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white;}\
                    QDialog {border: 1px solid palette(mid);}");
#if 0
                    QMenuBar {background-color: #303030; padding-top: 2px; padding-bottom: 2px;}
                    QMenuBar::item {spacing: 3px; padding: 2px 8px; background: transparent; color: white;}
                    QMenuBar::item:pressed {border: 1px solid #505050; border-bottom: 1px; border-top-left-radius: 3px; border-top-right-radius: 3px; background: #404040; color: white;}
#endif


#endif

    a.setStyleSheet(a.styleSheet() + "QWidget {font-size: 8pt}");

    frmMain w;
    w.show();

    return a.exec();
}
