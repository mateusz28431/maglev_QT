#include "rtdacinterface.h"
#include "RTDACAPI.h"
RTDACInterface::RTDACInterface( )
{

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
