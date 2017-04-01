#ifndef JSONCLASS_H
#define JSONCLASS_H
#include "measures.h"
#include <QString>
class JsonClass
{
public:
    JsonClass();
    static void JSon2ADC( QString jsonstring, ADC_measures* m );

};

#endif // JSONCLASS_H
