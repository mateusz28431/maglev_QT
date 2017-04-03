#ifndef MEASURES
#define MEASURES
#include <stdint.h>

struct ADC_measures
{
    uint16_t Measure0;
    uint16_t Measure10;
    uint16_t Measure11;
    uint16_t Measure12;
    unsigned long int Count;

};

struct measures
{
    double input_voltage;
    double current_asc;
    double current;
    double displacement_vol;

};

enum cntr_src
{
    RTDAC = 0,
    NUCLEO = 1
};

struct config
{
    uint8_t disNofP;
    cntr_src cntr;
    uint8_t cntrNofP;
};

measures ADC2real( ADC_measures* adc );

#endif // MEASURES

