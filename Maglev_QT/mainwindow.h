#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"
#include "rtdacinterface.h"
#include "rtdacdialog.h"
#include "measures.h"
#include "jsonclass.h"
#include "settingsdialog.h"
#include "terminaldialog.h"
#include "plotsdialog.h"
#include "LED.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow( );
     void Save2File( QString path );
     void LED_Green( LED* l );
     void LED_Red( LED* l );
private:
    Ui::MainWindow* ui;
    SerialPort* serial;
    RTDACDialog* rtdacDialog;
    RTDACInterface* rtdac;
    SettingsDialog* settingsDialog;
    TerminalDialog* terminalDialog;
    PlotsDialog* plotsDialog;
    QByteArray r_data;
    ADC_measures adc;
    config settings;
    int indeks;
    bool started;
    bool serial_connected;
    bool rtdac_connected;
    bool force_out_of_range;
    QVector<uint16_t> vector1;
    QVector<uint16_t> vector2;
    QVector<uint16_t> vector3;
    QVector<uint16_t> vector4;
    QVector<unsigned long int> vector5;
    QVector<double> current;
    QVector<double> displacement;
    int licznik;
private slots:
    void Connect2RTDAC( );
    void OpenSettings( );
    void OpenTerminal( );
    void RecievedData( QChar d );
    void OpenRTDAC( );
    void OpenPlots( );
    void Connect2Serial ( );
    void UpdateConfig( config c);
    void About( );
    void RefreshPorts( );
    void SaveData( );
    void Start( );
    void Stop( );
signals:
    void Data2Terminal( QString );
    void Data2Plots( double, double, ADC_measures a, int no_sample );

};

#endif // MAINWINDOW_H
