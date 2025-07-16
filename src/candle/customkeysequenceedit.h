#ifndef CUSTOMKEYSEQUENCEEDIT_H
#define CUSTOMKEYSEQUENCEEDIT_H

#include <QtWidgets/QKeySequenceEdit>

class CustomKeySequenceEdit : public QKeySequenceEdit
{
public:

    explicit CustomKeySequenceEdit(QWidget *parent = nullptr);

    virtual ~CustomKeySequenceEdit() override;

protected:

    virtual void keyPressEvent(QKeyEvent *pEvent) override;

};

#endif // CUSTOMKEYSEQUENCEEDIT_H
