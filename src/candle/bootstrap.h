/**
 * \file
 * \brief Файл с объявлением класса \ref bootstrap "bootstrap"
 */

#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QTranslator>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QApplication>

/**
 * \brief Объявление класса \ref bootstrap "bootstrap"
 *
 * Этот статический (нужен только один экземпляр членов класса) класс
 * предназначен для выполнения действий, предшествующих созданию основного
 * окна приложения.
 */
class bootstrap {

public:

    /**
     * \brief Выполнить начальные действия
     */
    static void init(int &argc, char **argv);

    /**
     * \brief Установить локализацию интерфейса согласно языковому файлу
     * \param [in] translationFileName имя файла локализации с путём.
     * \param [in,out] translator указатель на дескриптор локализации.
     */
    static void setTranslator(const QString &translationFileName, QTranslator **translator);

    /**
     * \brief Установить локализацию интерфейса согласно указанному языку
     */
    static void setAllTranslators(const QString &language);

    /**
     * \brief Обработчик отладочных/информационных/предупреждающих/аварийных
     * сообщений [qDebug()](https://doc.qt.io/qt-6/qtlogging.html#qDebug),
     * [qInfo()](https://doc.qt.io/qt-6/qtlogging.html#qInfo),
     * [qWarning()](https://doc.qt.io/qt-6/qtlogging.html#qWarning),
     * [qCritical()](https://doc.qt.io/qt-6/qtlogging.html#qCritical),
     * [qFatal()](https://doc.qt.io/qt-6/qtlogging.html#qFatal)
     */
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    /**
     * \brief Получить названия семейств (имена) загруженных шрифтов
     */
    static const QList<QString> &getLoadedFonts();

private:

    /**
     * \brief Дескриптор обработчика отладочных/информационных/предупреждающих/аварийных
     * сообщений [qDebug()](https://doc.qt.io/qt-6/qtlogging.html#qDebug),
     * [qInfo()](https://doc.qt.io/qt-6/qtlogging.html#qInfo),
     * [qWarning()](https://doc.qt.io/qt-6/qtlogging.html#qWarning),
     * [qCritical()](https://doc.qt.io/qt-6/qtlogging.html#qCritical),
     * [qFatal()](https://doc.qt.io/qt-6/qtlogging.html#qFatal)
     */
    static QtMessageHandler m_originalMessageHandler;

    /**
     * \brief Флаг, разрешающий выводить отладочные/информационные/предупреждающие/аварийные
     * сообщения [qDebug()](https://doc.qt.io/qt-6/qtlogging.html#qDebug),
     * [qInfo()](https://doc.qt.io/qt-6/qtlogging.html#qInfo),
     * [qWarning()](https://doc.qt.io/qt-6/qtlogging.html#qWarning),
     * [qCritical()](https://doc.qt.io/qt-6/qtlogging.html#qCritical),
     * [qFatal()](https://doc.qt.io/qt-6/qtlogging.html#qFatal)
     * в консоль
     */
    static bool m_debugOutput;

    /**
     * \brief Дескриптор локализации приложения
     */
    static QTranslator *m_candleTranslator;

    /**
     * \brief Дескриптор локализации [Qt](https://doc.qt.io/qt-6/)
     */
    static QTranslator *m_qtTranslator;

    /**
     * \brief Связный список путей к плюгинам и дескрипторов локализации плюгинов
     */
    static QMap<QString, QTranslator*> m_pluginTranslators;

    /**
     * \brief Список названий семейств (имён) загруженных шрифтов
     */
    static QList<QString> m_loadedFonts;
};

#endif // BOOTSTRAP_H
