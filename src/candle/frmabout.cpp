// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QtGui/QDesktopServices>
#include <QtCore/QFile>
#include "frmabout.h"
#include "ui_frmabout.h"

/**
 * \file
 *
 * \brief Файл с определениями функций-членов класса \ref frmAbout "frmAbout"
 *
 * <BR>
 * Функции, являющиеся методами класса \ref CameraWidget "frmAbout":
 * <BR>
 * * \copybrief frmAbout::frmAbout(QWidget *)
 */
frmAbout::frmAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmAbout)
{
    ui->setupUi(this);

    QFile file(qApp->applicationDirPath() + "/LICENSE");

    if (file.open(QIODevice::ReadOnly)) {
        ui->txtLicense->setPlainText(file.readAll());
    }
}

/**
 * \file
 * * \copybrief frmAbout::~frmAbout()
 */
frmAbout::~frmAbout()
{
    delete ui;
}

/**
 * \file
 * * \copybrief frmAbout::on_cmdOk_clicked()
 */
void frmAbout::on_cmdOk_clicked()
{
    this->hide();
}

/**
 * \file
 * * \copybrief frmAbout::on_lblAbout_linkActivated(const QString&)
 */
void frmAbout::on_lblAbout_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(link);
}

/**
 * \file
 * * \copybrief frmAbout::changeEvent(QEvent*)
 */
void frmAbout::changeEvent(QEvent *event)
{
    /** 
     * Алгоритм:
     *
     * 1 Вызвать обработчик событий по умолчанию для всех событий, кроме смены языка.
     */
    if (event->type() != QEvent::LanguageChange)
    {
        QDialog::changeEvent(event);
        return;
    }

    /** 
     * 2 Изменить язык строк из файла .ui.
     */
    ui->retranslateUi(this);


    /** 
     * 3 Изменить текст lblAbout, вставив параметр.
     */
    ui->lblAbout->setText(ui->lblAbout->text().arg( QString(
        qApp->applicationVersion() +
        ", Qt " +  QString(qVersion()) +
        ", " + QSysInfo::prettyProductName())));
}
