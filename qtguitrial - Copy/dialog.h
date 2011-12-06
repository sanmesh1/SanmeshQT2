#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//
#include "ui_dialog.h"
//

namespace Ui {
    class GoToCellDialog;
}

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    explicit GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();
private slots:
    void on_lineEdit_textChanged();
//Might not need what's on bottom because not in pdf tu.
private:
    Ui::GoToCellDialog *ui;
};

#endif // DIALOG_H
