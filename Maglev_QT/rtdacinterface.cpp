#include "rtdacinterface.h"
#include "RTDACAPI.h"
RTDACInterface::RTDACInterface( )
{
    Mode = 1;
    Presc = 0;
    Brake = 0;
    Dir = 1;
}

bool RTDACInterface::ConnectToBoard( )
{
    NoOfBoards = NoOfDetectedBoards( );
    SelectBoard( 0 );
    if( NoOfBoards != 0 )
    {
        BoardLocation( 0,  &BusNo, &SlotNo, &VendorID, &DeviceID, &BaseAddress );
        char BitstreamVer[16];
        RtdacPCI_BitstreamVersion( BaseAddress, BitstreamVer );
        BitStreamVer = QString( BitstreamVer );
        return true;
    }
    else
        return false;
}

double RTDACInterface::GetADCValue( int channel )
{
    if( NoOfBoards != 0 )
    {
        int ADChan;
        double ADVolt;
        ADChan = RtdacPCI_AD( BaseAddress, channel, 1 );
        if( ADChan > 2047 )
            ADVolt = -10.0-10.0*(2048-ADChan)/2047;
        else
            ADVolt =  10.0*( ADChan )/2047;
        return ADVolt;
    }
    else return -99;

}

bool RTDACInterface::SetDAValue ( int channel, uint value )
{
    if ( NoOfBoards > 0 )
    {
        if (  value <= 4095 )
        {
            RtdacPCI_DA( BaseAddress, channel, value );
            return true;
        }
        else
            return false;
    }
    else
        return false;

}

int RTDACInterface::GetNoOfBoard( )
{
    return NoOfBoards;
}

void RTDACInterface::InitializePWM( )
{
    WriteWord( BaseAddress + 0x44, Presc );
    CtrlByte=(4*Brake + 2*Dir+ 1*Mode);
}

void RTDACInterface::setBrake( int br )
{
    Brake = (br>=1)? 1 : 0;
    if ( NoOfBoards > 0 )
    {
        CtrlByte=(4*Brake + 2*Dir+ 1*Mode);
        WriteByte ( BaseAddress + 0x40, (int) CtrlByte );
    }
}

void RTDACInterface::Clean( )
{
    WriteByte ( BaseAddress + 0x40, (int) 0x00 );
    WriteWord ( BaseAddress + 0x48, (int) 0x00 );
}
void RTDACInterface::setPWM( double PWMCtrl )
{
    if ( NoOfBoards > 0 )
    {
        if ( PWMCtrl > 4095.0 ) PWMCtrl = 4095.0;
        if ( PWMCtrl < 0 ) PWMCtrl = 0.0;
        WriteWord ( BaseAddress + 0x48, (int)(fabs( (PWMCtrl )) ) );
    }
}
