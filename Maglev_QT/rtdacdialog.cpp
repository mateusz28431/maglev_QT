#include "rtdacdialog.h"
#include "ui_rtdacdialog.h"

RTDACDialog::RTDACDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RTDACDialog)
{
    ui->setupUi(this);
    rtdac = new RTDACInterface( );
    connected = false;
    ui->currentDisp->setReadOnly( true );
    ui->displacementDisp->setReadOnly( true );
    ui->dacDisp->setReadOnly( true );
    ui->dacDisp->setText( "0" );

    //SIGNALs to SLOT connections
    connect( ui->exitButton, SIGNAL( clicked(bool) ), this, SLOT( accept() ) );
    connect( ui->connectButton, SIGNAL( clicked(bool) ), this, SLOT( connect2RTDAC( ) ) );
    connect( ui->currentButton, SIGNAL( clicked(bool) ), this, SLOT( measureCurrent() ) );
    connect( ui->displacementButton, SIGNAL( clicked(bool) ), this, SLOT( measureDisplacement() ) );
    connect( ui->dacSlider, SIGNAL( valueChanged(int) ), this, SLOT( dacSliderChanged(int) ) );
    connect( ui->dacButton, SIGNAL( clicked(bool) ), this, SLOT( dacSet() ) );
}

RTDACDialog::~RTDACDialog()
{
    delete ui;
    delete rtdac;
}

void RTDACDialog::connect2RTDAC( )
{
    if ( rtdac->ConnectToBoard( ) )
    {
        connected = true;
        ui->statusLabel->setText( tr( "Połączony" ) );
    }
}

void RTDACDialog::measureCurrent( )
{
    if( connected )
    {
        current_value = rtdac->GetADCValue( CURRENT_CHANNEL );
        ui->currentDisp->setText( QString::number( current_value ) );
    }
}
void RTDACDialog::measureDisplacement( )
{
    if( connected )
    {
        displacement_value = rtdac->GetADCValue( DISPLACEMENT_CHANNEL );
        ui->displacementDisp->setText( QString::number( displacement_value ) );
    }
}

void RTDACDialog::dacSliderChanged( int val )
{
    dac_value = val;
    ui->dacDisp->setText( QString::number( val ));
}

void RTDACDialog::dacSet( )
{
    if( connected )
    {
        rtdac->SetDAValue( PWM_CHANNEL, dac_value );
    }
}
