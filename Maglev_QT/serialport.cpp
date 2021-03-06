#include "serialport.h"

SerialPort::SerialPort( )
{
    portname = "";
    r_data = "";
    port = new QSerialPort( );
    QObject::connect( port, SIGNAL(readyRead()), this, SLOT(RecievedData()) );
    //port = nullptr;
}

SerialPort::~SerialPort( )
{
    if ( port != nullptr )
    {
        delete port;
        port = nullptr;
    }

}

SerialPort::SerialPort( QString pname )
{
    portname = pname;
    r_data = "";
    port = new QSerialPort( );
    QObject::connect( port, SIGNAL(readyRead()), this, SLOT(RecievedData()) );
}


bool SerialPort::OpenConnection( )
{
    if ( port == nullptr )
        return false;
    port->setBaudRate( QSerialPort::Baud115200 );
    port->setDataBits( QSerialPort::Data8 );
    port->setFlowControl( QSerialPort::NoFlowControl );
    port->setParity( QSerialPort::NoParity );
    port->setStopBits( QSerialPort::OneStop );
    port->setPortName( portname );

    port->open( QIODevice::ReadWrite );
    if ( this->isOpen() )
        return true;
    else return false;
}

bool SerialPort::isOpen( )
{
    return port->isOpen( ) ? true : false;
}

bool SerialPort::CloseConnection( )
{
    if ( isOpen( ) )
        port->close( );

    return isOpen() ? false : true;
}

void SerialPort::RecievedData( )
{
    r_data = port->readAll( );
    QString temp = r_data;
    r_data.clear();
    int i = 0;
    while (i <temp.size() )
    {
        QChar t = temp.at(i);
        emit RxData( t );
        i++;
    }

}

bool SerialPort::SendData( QString data )
{
    if ( !isOpen() )
        return false;
    port->write( data.toStdString().c_str() );
    return true;
}

void SerialPort::SetPortName( QString pname )
{
    portname = pname;
}
