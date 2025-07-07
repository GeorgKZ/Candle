#ifndef COMBOBOXKEY_H
#define COMBOBOXKEY_H

#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

class ComboBoxKey : public QComboBox
{
public:

    explicit ComboBoxKey(QWidget *parent = nullptr);

    void setEditable(bool editable);

    void setCurrentNext();
    void setCurrentPrevious();

    void setItems(QStringList items);
    QStringList items();

protected:

    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent *e) override;

private:

    bool isBlockedKey(int key);
};

#endif // COMBOBOXKEY_H
