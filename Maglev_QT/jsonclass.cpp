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

}
