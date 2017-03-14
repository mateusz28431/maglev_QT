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
    int Presc;
    int Mode;
    int Brake;
    int Dir;
    int CtrlByte;
public:
    RTDACInterface( );
    bool ConnectToBoard( );
    double GetADCValue( int channel );
    bool SetDAValue ( int channel, uint value );
    int GetNoOfBoard( );
    void InitializePWM( );
    void setBrake( int br );
    void setPWM( double PWMCtrl );
    void Clean( );

};

#endif // RTDACINTERFACE_H
