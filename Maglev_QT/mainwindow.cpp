#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QDir>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    //Dialogs
    rtdacDialog = new RTDACDialog( this );
    settingsDialog = new SettingsDialog( this );
    terminalDialog = new TerminalDialog( this );
    plotsDialog = new PlotsDialog( this );
    serial = new SerialPort( );
    rtdac = new RTDACInterface( );

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->COMBox->addItem( info.portName( ) );
    }
    statusBar( )->showMessage( tr("Aplikacja została uruchomiona"), 5000 );

    indeks = 1;
    started = false;
    settings.cntr = RTDAC;
    settings.cntrNofP = 14;
    settings.disNofP = 7;
    plotsDialog->InitializePlots( );
    rtdac_connected = false;
    serial_connected = false;

    // Signals to slots connections
    connect( serial, SIGNAL(RxData(QChar)),this, SLOT(RecievedData(QChar)) );
    connect( ui->connectButton, SIGNAL(clicked(bool)), this, SLOT( Connect2Serial( ) ) );
    connect( ui->rtdacButton, SIGNAL(clicked(bool)), this, SLOT( Connect2RTDAC( ) ) );
    connect( settingsDialog, SIGNAL( SaveConfig(config) ), this, SLOT( UpdateConfig(config)) );
    connect( this, SIGNAL(Data2Terminal(QString)), terminalDialog, SLOT(ShowData(QString)));
    connect( ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(RefreshPorts()) );
    connect( ui->actionInfo,SIGNAL(triggered(bool)),this,SLOT(About()));
    connect( ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(OpenSettings()));
    connect( ui->actionExit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect( ui->actionTerminal, SIGNAL(triggered(bool)),this, SLOT(OpenTerminal( )));
    connect( ui->actionRTDAC, SIGNAL(triggered(bool)),this, SLOT(OpenRTDAC( )));
    connect( ui->actionSaveData, SIGNAL(triggered(bool)), this, SLOT(SaveData()) );
    connect( ui->actionStart, SIGNAL( triggered(bool) ), this, SLOT(Start( ) ) );
    connect( ui->actionStop, SIGNAL( triggered(bool) ), this, SLOT(Stop( ) ) );
    connect( ui->actionPlots, SIGNAL(triggered(bool)), this, SLOT(OpenPlots()) );
    connect( this, SIGNAL(Data2Plots(double,double,ADC_measures,int)), plotsDialog,
             SLOT(AddData2Plots(double,double,ADC_measures,int)) );

}

MainWindow::~MainWindow( )
{
    delete ui;
}
void MainWindow::RecievedData( QChar d )
{
    r_data += d;
    if (r_data.contains("}"))
    {
        QString temp = r_data;
        emit Data2Terminal( temp );
        r_data = "";
        JsonClass::JSon2ADC( temp, &adc );
        if ( started )
        {
            vector1.append(adc.Measure0);
            vector2.append(adc.Measure10);
            vector3.append(adc.Measure11);
            vector4.append(adc.Measure12);
            vector5.append(adc.Count);
            double curr = rtdac->GetADCValue( 2 );
            double disp = rtdac->GetADCValue( 4 );
            current.append( curr );
            displacement.append( disp );
            emit Data2Plots( curr, disp, adc,licznik );
            if ( indeks < settings.cntrNofP )
            {
                if ( adc.Count > 9200000 || force_out_of_range )
                {
                    force_out_of_range = true;
                    rtdac->setPWM( 0*4095/(settings.cntrNofP-1));
                }
                else
                    rtdac->setPWM( indeks*4095/(settings.cntrNofP-1));
                indeks++;
            }

            if( indeks == settings.cntrNofP)
            {
                indeks = 0;
                force_out_of_range = false;
            }
            ui->experimentProgress->setValue( int(licznik*100/(settings.cntrNofP * settings.disNofP-1)) );
            licznik++;
            if( licznik == (settings.cntrNofP * settings.disNofP) )
            {
                started = false;
                LED_Red( ui->led_3 );
            }

        }
    }
}

void MainWindow::Connect2RTDAC( )
{

    if ( !rtdac_connected )
    {
        if ( rtdac->ConnectToBoard( ) )
        {
            LED_Green( ui->led_2 );
            rtdac->InitializePWM( );
            rtdac->setBrake( 0 );
            rtdac_connected = true;
            statusBar( )->showMessage( tr("Nawiązano komunikację z kartą pomiarową") );
        }
        else
        {
            LED_Red( ui->led_2 );
            statusBar( )->showMessage( tr("Nie można połączyć się z kartą pomiarową") );
        }
    }

}

void MainWindow::OpenSettings( )
{
    settingsDialog->show( );
}
void MainWindow::Connect2Serial( )
{

    if ( serial->isOpen( ) )
    {
        if ( serial->CloseConnection( ) )
        {
            ui->connectButton->setText( tr("Połącz") );
            serial_connected = false;
            statusBar( )->showMessage( tr("Rozłączono z urządzeniem"), 5000 );
            LED_Red( ui->led );
        }
        else
        {
            ui->connectButton->setText( tr("Rozłącz") );
            serial_connected = true;
            LED_Green( ui->led );
            statusBar( )->showMessage( tr("Nie można zamknąć połączenia z urządzeniem"), 5000 );
        }
    }
    else
    {
        QString portName = ui->COMBox->currentText( );
        serial->SetPortName( portName );
        if( serial->OpenConnection( ) )
        {
            ui->connectButton->setText( tr("Rozłącz") );
            serial_connected = true;
            statusBar()->showMessage( tr("Połączono") );
            LED_Green( ui->led );
        }
        else
        {
            ui->connectButton->setText( tr("Połącz") );
            serial_connected = false;
            statusBar()->showMessage( tr("Nie można ustanowić połączenia") );
            LED_Red( ui->led );
        }
    }
}


void MainWindow::UpdateConfig( config c )
{
    settings = c;
    emit Data2Terminal( JsonClass::CreateJson(settings,false));
}

void MainWindow::Save2File( QString path )
{
   //vector1
    QFile fileout( path + "/vector1.txt" );
    if( fileout.open(QFile::ReadWrite | QFile::Text) )
    {
        QTextStream out( &fileout );
        for( QVector<uint16_t>::iterator iter = vector1.begin( ); iter != vector1.end( ); iter++ )
        {
           out << *iter << endl;
        }
        fileout.close( );
    }

    //vector2
     QFile fileout2( path + "/vector2.txt" );
     if( fileout2.open( QFile::ReadWrite | QFile::Text) )
     {
         QTextStream out2( &fileout2 );
         for( QVector<uint16_t>::iterator iter = vector2.begin( ); iter != vector2.end( ); iter++ )
         {
            out2 << *iter << endl;
         }
         fileout2.close( );
     }

     //vector3
      QFile fileout3( path + "/vector3.txt" );
      if( fileout3.open(QFile::ReadWrite | QFile::Text) )
      {
          QTextStream out3( &fileout3 );
          for( QVector<uint16_t>::iterator iter = vector3.begin( ); iter != vector3.end( ); iter++ )
          {
             out3 << *iter << endl;
          }
          fileout3.close( );
      }

      //vector4
       QFile fileout4( path + "/vector4.txt" );
       if( fileout4.open( QFile::ReadWrite | QFile::Text) )
       {
           QTextStream out4( &fileout4 );
           for( QVector<uint16_t>::iterator iter = vector4.begin( ); iter != vector4.end( ); iter++ )
           {
              out4 << *iter << endl;
           }
           fileout4.close( );
       }
       //vector5
        QFile fileout5( path + "/vector5.txt" );
        if( fileout5.open(QFile::ReadWrite | QFile::Text) )
        {
            QTextStream out5( &fileout5 );
            for( QVector<unsigned long int>::iterator iter = vector5.begin( ); iter != vector5.end( ); iter++ )
            {
               out5 << *iter << endl;
            }
            fileout5.close( );
        }
        //current

         QFile fileout6( path + "/current.txt" );
         if( fileout6.open(QFile::ReadWrite | QFile::Text) )
         {
             QTextStream out6( &fileout6 );
             for( QVector<double>::iterator iter = current.begin( ); iter != current.end( ); iter++ )
             {
                out6 << *iter << endl;
             }
             fileout6.close( );
         }
         //displacement
          QFile fileout7( path + "/displacement.txt" );
          if( fileout7.open(QFile::ReadWrite | QFile::Text) )
          {
              QTextStream out7( &fileout7 );
              for( QVector<double>::iterator iter = displacement.begin( ); iter != displacement.end( ); iter++ )
              {
                 out7 << *iter << endl;
              }
              fileout7.close( );
          }
}

void MainWindow::About( )
{
    QMessageBox::about( this, tr("O programie"), tr("Mateusz Łubiarz, 2017\nSystem autmatycznego przeprowadzania eksyperymentów"
                                                    " identyfikacyjnych układu magnetycznej lewitacji \nAplikacja napisana w"
                                                    " ramach pracy magisterskiej") );
}

void MainWindow::OpenTerminal( )
{
    terminalDialog->show( );
}

void MainWindow::OpenRTDAC( )
{
    if( !started )
        rtdacDialog->show( );
    else
        ui->statusBar->showMessage( tr("Nie można otworzyć okna - algorytm w trakcie działania"), 5000 );
}

void MainWindow::RefreshPorts( )
{
    ui->COMBox->clear( );
    foreach( const QSerialPortInfo &info, QSerialPortInfo::availablePorts( ) )
    {
        ui->COMBox->addItem( info.portName( ) );
    }
}

void MainWindow::OpenPlots( )
{
    plotsDialog->show( );
}

void MainWindow::SaveData( )
{
    QString filePath = QFileDialog::getExistingDirectory( this, tr( "Wybierz ścieżkę do zapisu" ), "C:\\");
    QDir dir(filePath);
    if( dir.mkdir( QDateTime::currentDateTime( ).date( ).toString( ) ) )
    {
        Save2File( filePath + "/" +QDateTime::currentDateTime( ).date( ).toString( ) );
    }
    else
        statusBar( )->showMessage( tr( "Nie można utworzyć katalogu" ), 5000 );
    Save2File( filePath + "/"+ QDateTime::currentDateTime( ).date( ).toString( ) );
}
void MainWindow::Start( )
{
    if ( serial_connected && rtdac_connected )
    {
        if ( !started )
        {
            QString temp = JsonClass::CreateJson( settings, true );
            started = true;
            emit Data2Terminal( temp );
            plotsDialog->ClearPlots( );
            plotsDialog->SetRange( settings.cntrNofP * settings.disNofP );
            licznik = 0;
            statusBar()->showMessage( tr("Eksperyment został uruchoimiony"), 5000 );
            LED_Green( ui->led_3 );
            serial->SendData( temp.toStdString( ).c_str( ) );
            if ( rtdacDialog->isVisible( ) )
                rtdacDialog->hide( );
            ui->actionRTDAC->setDisabled( true );
        }
        else
        {
            statusBar( )->showMessage( tr("Eksperyment w trakcie działania"), 5000 );
        }
    }
    else
        statusBar( )->showMessage( tr("Nie można uruchomić algorytmu"), 5000 );
}
void MainWindow::Stop( )
{
    if ( serial_connected && rtdac_connected )
    {
        if ( !started )
        {
            statusBar( )->showMessage( tr("Eksperyment nie jest uruchomiony "), 5000 );
        }
        else
        {
            QString temp = JsonClass::CreateJson(settings, false );
            started = false;
            emit Data2Terminal( temp );
            statusBar()->showMessage( tr("Eksperyment zatrzymano"), 5000 );
            LED_Red( ui->led_3 );
            serial->SendData( temp.toStdString().c_str());
            ui->actionRTDAC->setEnabled( true );
        }
    }
}

void MainWindow::LED_Green( LED* l )
{
    l->setColor( QColor( Qt::green ));
}

void MainWindow::LED_Red( LED* l )
{
    l->setColor( QColor( Qt::red ));
}
