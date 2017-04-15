#include "plotsdialog.h"
#include "ui_plotsdialog.h"

PlotsDialog::PlotsDialog( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::PlotsDialog )
{
    ui->setupUi( this );
}

PlotsDialog::~PlotsDialog( )
{
    delete ui;
}

void PlotsDialog::InitializePlots( )
{
    ui->plot1->legend->setVisible( true );
    ui->plot1->addGraph( );
    ui->plot1->xAxis->setLabel( "Nr próbki" );
    ui->plot1->yAxis->setLabel( "Prąd, Położenie (RTDAC ADC) [V]" );
    ui->plot1->yAxis->setRange( -12, 12 );
    ui->plot1->graph( 0 )->setLineStyle( QCPGraph::lsNone );
    ui->plot1->graph( 0 )->setScatterStyle( QCPScatterStyle(QCPScatterStyle::ssDisc, 3 ) );
    ui->plot1->graph( 0 )->setName( "Prąd" );

    ui->plot1->addGraph( );
    ui->plot1->graph( 1 )->setLineStyle( QCPGraph::lsNone );
    ui->plot1->graph( 1 )->setScatterStyle( QCPScatterStyle(QCPScatterStyle::ssDisc,3 ) );
    ui->plot1->graph( 1 )->setPen( QPen( Qt::red ) );
    ui->plot1->graph( 1 )->setName( "Położenie" );
    ui->plot1->replot( );

    ui->plot2->addGraph( );
    ui->plot2->xAxis->setLabel( "Numer Próbki" );
    ui->plot2->yAxis->setLabel( "Siła" );
    ui->plot2->yAxis->setRange( 8000000, 12000000 );
    ui->plot2->graph( 0 )->setLineStyle( QCPGraph::lsNone );
    ui->plot2->graph( 0 )->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssDisc, 3 ) );
    ui->plot2->replot( );

    ui->plot3->legend->setVisible( true );
    ui->plot3->addGraph( );
    ui->plot3->xAxis->setLabel( "Numer Próbki" );
    ui->plot3->yAxis->setLabel( "Prąd, Położenie (NUCLEO ADC) [V]" );
    ui->plot3->yAxis->setRange( -0.5, 3.3 );
    ui->plot3->graph( 0 )->setLineStyle( QCPGraph::lsNone );
    ui->plot3->graph( 0 )->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssDisc, 3 ) );
    ui->plot3->graph( 0 )->setName( "Prąd" );
    ui->plot3->addGraph( );
    ui->plot3->graph( 1 )->setLineStyle( QCPGraph::lsNone );
    ui->plot3->graph( 1 )->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssDisc, 3 ) );
    ui->plot3->graph( 1 )->setPen( QPen( Qt::red ) );
    ui->plot3->graph( 1 )->setName( "Położenie" );
    ui->plot3->replot( );

    ui->plot4->addGraph( );
    ui->plot4->xAxis->setLabel( "Numer Próbki" );
    ui->plot4->yAxis->setLabel( "Prąd (ASC712) [A]" );
    ui->plot4->yAxis->setRange( -0.5, 3 );
    ui->plot4->graph( 0 )->setLineStyle( QCPGraph::lsNone );
    ui->plot4->graph( 0 )->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssDisc, 3 ) );

}

void PlotsDialog::SetRange( int range )
{
    ui->plot1->xAxis->setRange( 0, range );
    ui->plot2->xAxis->setRange( 0, range );
    ui->plot3->xAxis->setRange( 0, range );
    ui->plot4->xAxis->setRange( 0, range );
}

void PlotsDialog::AddData2Plots( double current, double displacement, ADC_measures a, int no_sample )
{
    measures m = ADC2real( &a );
    ui->plot1->replot( );
    ui->plot1->graph( 0 )->addData(  no_sample, current );
    ui->plot1->graph( 1 )->addData(  no_sample, displacement );
    ui->plot1->replot( );

    ui->plot2->replot( );
    ui->plot2->graph( 0 )->addData(  no_sample, a.Count );
    ui->plot2->replot( );

    ui->plot3->replot( );
    ui->plot3->graph( 0 )->addData(  no_sample, m.current );
    ui->plot3->graph( 1 )->addData(  no_sample, m.displacement_vol );
    ui->plot3->replot( );

    ui->plot4->replot( );
    ui->plot4->graph( 0 )->addData(  no_sample,  m.current_asc );
    ui->plot4->replot( );



}

void PlotsDialog::ClearPlots( )
{
    ui->plot1->graph( 0 )->clearData( );
    ui->plot1->graph( 1 )->clearData( );
    ui->plot2->graph( 0 )->clearData( );
    ui->plot3->graph( 0 )->clearData( );
    ui->plot3->graph( 1 )->clearData( );
    ui->plot4->graph( 0 )->clearData( );

}
