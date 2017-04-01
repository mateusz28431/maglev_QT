#include "measures.h"

measures ADC2real( ADC_measures* adc )
{
    measures m;
    m.input_voltage = (adc->Measure0 *3.3*1.532)/4095;
    m.current_asc =  -5.0 +(adc->Measure10*3.3*1.468*5)/(4095*1.65);
    m.current = 1.49 + (adc->Measure11*3.3*0.096)/4095;
    m.displacement_vol = 1.49 + (adc->Measure12*3.3*0.096)/4095;

    return m;
}
