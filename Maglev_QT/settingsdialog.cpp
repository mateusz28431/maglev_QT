#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect( ui->saveButton, SIGNAL(clicked(bool)), this, SLOT( SaveButtonClicked( ) ) );
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::SaveButtonClicked( )
{
    config c;
    QString temp;

    temp = ui->controlNofP->currentText( );
    c.cntrNofP = temp.toUInt( );

    temp = ui->displacementNofP->currentText( );
    c.disNofP = temp.toUInt( );

    temp = ui->controlSource->currentText( );
    c.cntr = (temp == "RTDAC" ? RTDAC : NUCLEO);

    emit SaveConfig( c ) ;

    this->close( );
}
