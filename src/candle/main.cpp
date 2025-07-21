// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifdef Q_OS_WINDOWS
  #include <windows.h> 
#endif

#include "frmmain.h"
#include "bootstrap.h"

int main(int argc, char *argv[]) {

    /**
     * Алгоритм:
     * * Создать экземпляр типа QApplication
     */
    QApplication a(argc, argv);

    a.setAttribute(Qt::AA_ForceRasterWidgets, false);

    /**
     * * Установить для экземпляра QApplication версию и название программы
     */
    a.setApplicationDisplayName(quoting(PROJECT_NAME));
    a.setApplicationVersion(VERSION_STR);

    /**
     * * Выполнить начальные действия: настроить вывод отладочных сообщений, загрузить
     * шрифты, интегрированные в приложение, установить локализацию согласно файлу
     * конфигурации. 
     */
    bootstrap::init(argc, argv);



//  qDebug() << "Found system styles:" << QStyleFactory::keys();

#if 0 
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(204, 204, 254));
    palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0));
    a.setPalette(palette);

    a.setStyleSheet("QWidget {font-family: \"Ubuntu\";}\
                    QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white;}"
                    QMenuBar {background-color: #303030; padding-top: 2px; padding-bottom: 2px;}
                    QMenuBar::item {spacing: 3px; padding: 2px 8px; background: transparent; color: white;}
                    QMenuBar::item:pressed {border: 1px solid #505050; border-bottom: 1px; border-top-left-radius: 3px; border-top-right-radius: 3px; background: #404040; color: white;});
#endif


    /**
     * * Создать и отобразить главное окно приложения.
     */
    frmMain w;
    w.show();

    /**
     * * Передать управление обработчикам событий.
     */
    return a.exec();
}
