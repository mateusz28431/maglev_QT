#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QSerialPort>
#include <QObject>
class SerialPort : public QObject
{
    Q_OBJECT
private:
    QString portname;
    QSerialPort* port;
    QByteArray r_data;
public:
    SerialPort( );
    SerialPort( QString pname );
    ~SerialPort( );
    bool OpenConnection( );
    bool isOpen( );
    bool CloseConnection( );
    bool SendData( QString data );
    void SetPortName( QString pname );


signals:
    void RxData( QChar );
public slots:
    void RecievedData( );
};

#endif // SERIALPORT_H
