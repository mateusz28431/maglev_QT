#include "terminaldialog.h"
#include "ui_terminaldialog.h"

TerminalDialog::TerminalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TerminalDialog)
{
    ui->setupUi(this);
}

TerminalDialog::~TerminalDialog()
{
    delete ui;
}

void TerminalDialog::ShowData( QString data )
{
    ui->terminal->appendPlainText( data );
}
