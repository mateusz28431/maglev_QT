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
    ui->pwmDisp->setReadOnly( true );
    ui->pwmDisp->setText( "0" );
    brake = false;

    //SIGNALs to SLOT connections
    connect( ui->exitButton, SIGNAL( clicked(bool) ), this, SLOT( accept() ) );
    connect( ui->connectButton, SIGNAL( clicked(bool) ), this, SLOT( connect2RTDAC( ) ) );
    connect( ui->currentButton, SIGNAL( clicked(bool) ), this, SLOT( measureCurrent() ) );
    connect( ui->displacementButton, SIGNAL( clicked(bool) ), this, SLOT( measureDisplacement() ) );
    connect( ui->pwmSlider, SIGNAL( valueChanged(int) ), this, SLOT( dacSliderChanged(int) ) );
    connect( ui->pwmButton, SIGNAL( clicked(bool) ), this, SLOT( PWMSet( ) ) );
    connect( ui->brakeButton, SIGNAL( clicked(bool) ), this, SLOT( Brake( ) ) );
}

RTDACDialog::~RTDACDialog()
{
    delete ui;
    if (connected)
        rtdac->Clean( );
    delete rtdac;
}

void RTDACDialog::connect2RTDAC( )
{
    if ( rtdac->ConnectToBoard( ) )
    {
        connected = true;
        ui->statusLabel->setText( tr( "Połączony" ) );
        rtdac->InitializePWM( );
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
    pwm_value = val;
    ui->pwmDisp->setText( QString::number( val ));
}

void RTDACDialog::PWMSet( )
{
    if( connected )
    {
        rtdac->setPWM( pwm_value );
    }
}

void RTDACDialog::Brake( )
{
    if (brake)
    {
        rtdac->setBrake(1);
        brake = true;
    }
    else
    {
        rtdac->setBrake(0);
        brake = false;
    }
}

