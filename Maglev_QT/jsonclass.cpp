#include "jsonclass.h"
#include <QJsonDocument>
#include <QJsonObject>
JsonClass::JsonClass()
{

}


void JsonClass::JSon2ADC( QString jsonstring, ADC_measures* m )
{
    QJsonDocument doc(QJsonDocument::fromJson(jsonstring.toUtf8()));

    // Get JSON object
    QJsonObject json = doc.object();
    QString temp;

    temp  =  json["voltage1"].toString( );
    m->Measure0 = temp.toUInt( );

    temp =  json["voltage2"].toString( );
    m->Measure10 = temp.toUInt( );

    temp =  json["voltage3"].toString( ) ;
    m->Measure11 = temp.toUInt( );

    temp =  json["voltage4"].toString( ) ;
    m->Measure12 = temp.toUInt( );

    temp =  json["count"].toString( ) ;
    m->Count = temp.toULong( );

}

QString JsonClass::CreateJson(config c, bool start)
{
    QJsonObject jsonObj;

    jsonObj.insert( "disNofP", c.disNofP );
    jsonObj.insert( "cntrlSource", c.cntr );
    jsonObj.insert( "cntrlNofP", c.cntrNofP );

    if ( start )
        jsonObj.insert( "start", 1 );
    else
        jsonObj.insert( "start", 0 );
    QJsonDocument doc(jsonObj);
    return doc.toJson( QJsonDocument::Compact );
}
