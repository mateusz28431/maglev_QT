#ifndef RTDACINTERFACE_H
#define RTDACINTERFACE_H
#include <QString>

class RTDACInterface
{
private:
    int NoOfBoards;
    int BaseAddress;
    int BusNo;
    int SlotNo;
    int VendorID;
    int DeviceID;
    QString BitStreamVer;
public:
    RTDACInterface( );
    bool ConnectToBoard( );
    double GetADCValue( int channel );
    bool SetDAValue ( int channel, uint value );
    int GetNoOfBoard( );

};

#endif // RTDACINTERFACE_H
