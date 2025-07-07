// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class frmAbout; }
QT_END_NAMESPACE

/**
 * \brief Объявление класса \ref frmAbout "frmAbout"
 *
 * Этот класс предназначен для создания диалогового окна "О программе".
 */
class frmAbout : public QDialog
{
    Q_OBJECT

public:

    /**
     * \brief Конструктор
     * \param [in] parent Родительский объект
     */
    explicit frmAbout(QWidget *parent = nullptr);

    /**
     * \brief Деструктор
     */
    virtual ~frmAbout() override;

private slots:

    /**
     * \brief Обработчик события нажатия кнопки "OK"
     */
    void on_cmdOk_clicked();

    /**
     * \brief Обработчик события нажатия на ссылку
     * \param [in] link Строка, содержащая ссылку
     */
    void on_lblAbout_linkActivated(const QString &link);

protected:

    /**
     * \brief Обработчик события изменения состояния
     * \param [in] event Указатель на элемент класса QEvent,
     * содержащий описание происшедшего события
     */
    virtual void changeEvent(QEvent *event) override;

private:

    /**
     * Дескриптор интерфейса
     */
    Ui::frmAbout *ui;
};

#endif // FRMABOUT_H
