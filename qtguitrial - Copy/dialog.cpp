#include "dialog.h"
#include "ui_dialog.h"

//might not need "ui(new Ui::GoToCellDialog)" because not in pdf tu.

GoToCellDialog::GoToCellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToCellDialog)
{
       ui->setupUi(this);
       QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
       lineEdit->setValidator(new QRegExpValidator(regExp, this));
       connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
       connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
//don't know if it should be before or after destructor
void GoToCellDialog::on_lineEdit_textChanged()
{
okButton->setEnabled(lineEdit->hasAcceptableInput());
}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}
