#ifndef MEASURES
#define MEASURES
#include <stdint.h>

struct ADC_measures
{
    uint16_t Measure0;
    uint16_t Measure10;
    uint16_t Measure11;
    uint16_t Measure12;

};

struct measures
{
    double input_voltage;
    double current_asc;
    double current;
    double displacement_vol;

};

measures ADC2real( ADC_measures* adc );

#endif // MEASURES

