// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT

public:

    explicit ComboBox(QWidget *parent = nullptr);
    virtual ~ComboBox() override;

    void storeText();

public slots:

    void addItems(const QStringList &texts) {QComboBox::addItems(texts);}
    void setItems(const QStringList &texts) {QComboBox::clear(); addItems(texts);}
    QStringList items() {QStringList l; for (int i = 0; i < count(); i++) l << itemText(i); return l;}

signals:

    void returnPressed();

protected:

    virtual void keyPressEvent(QKeyEvent *e) override;
};

#endif // COMBOBOX_H
