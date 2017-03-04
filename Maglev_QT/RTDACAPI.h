
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RTDACAPI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RTDACAPI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//#ifdef RTDACAPI_EXPORTS
#define RTDACAPI_API extern "C" __declspec(dllexport)
//#else
//#define RTDACAPI_API __declspec(dllimport)
//#endif

typedef unsigned char      UI8,  *PUI8;
typedef unsigned short int UI16, *PUI16;
typedef unsigned long  int UI32, *PUI32;


RTDACAPI_API void           RTDACAPIVersion( void );
RTDACAPI_API int            WriteByte( int port, int value );
RTDACAPI_API unsigned short WriteWord( int port, unsigned int value );
RTDACAPI_API unsigned long  WriteDWord( int port, unsigned int value );
RTDACAPI_API int            ReadByte( int port );
RTDACAPI_API unsigned int   ReadWord( int port );
RTDACAPI_API unsigned long  ReadDWord( int port );
RTDACAPI_API int            NoOfDetectedBoards( void );
RTDACAPI_API int            SelectBoard( int Idx );
RTDACAPI_API int            BoardLocation( int BoardIdx,  int *BusNo,    int *SlotNo,
							               int *VendorID, int *DeviceID, int *BaseAddress );
RTDACAPI_API int            BoardLocationEx( int BoardIdx,  int *BusNo,    int *SlotNo,
							                 int *VendorID, int *DeviceID, 
											 int *BaseAddress, int *PCIBAR1 );
RTDACAPI_API int            IntrInit( int BoardIdx );
//RTDACAPI_API int            IntrAttach( int BoardIdx, HANDLE *eventHandle );
RTDACAPI_API int            IntrResponse( int BoardIdx ); 
RTDACAPI_API int            IntrClose( int BoardIdx ); 

// Version management functions
RTDACAPI_API void  RtdacPCI_BitstreamVersion( UI16 BaseAddress, char BitstreamVer[] );
RTDACAPI_API char *RtdacPCI_AppName( UI16 BaseAddress );

// Counter/timer functions
RTDACAPI_API UI8  RtdacPCI_ReadNoOfCounters( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ReadCounter(      UI16 BaseAddress, UI8 ChanNo );
RTDACAPI_API UI32 RtdacPCI_ResetCounter(     UI16 BaseAddress, UI8 ChanNo );
RTDACAPI_API UI8  RtdacPCI_ReadNoOfTimers(   UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ReadTimer(        UI16 BaseAddress, UI8 ChanNo );
RTDACAPI_API UI32 RtdacPCI_ResetTimer(       UI16 BaseAddress, UI8 ChanNo );

// Digital I/O functions
RTDACAPI_API UI32 RtdacPCI_WriteDigIOConfig( UI16 BaseAddress, UI32 DIOConfValue );
RTDACAPI_API UI32 RtdacPCI_ReadDigIOConfig(  UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_WriteDigIO(       UI16 BaseAddress, UI32 DIOValue );
RTDACAPI_API UI32 RtdacPCI_ReadDigIO(        UI16 BaseAddress );
// RT-DAC4-PCI-D functions
RTDACAPI_API UI32 RtdacPCID_WriteDigIOConfig( UI16 BaseAddress, UI8 IOChan, UI32 DIOConfValue );
RTDACAPI_API UI32 RtdacPCID_ReadDigIOConfig(  UI16 BaseAddress, UI8 IOChan );
RTDACAPI_API UI32 RtdacPCID_WriteDigIO(       UI16 BaseAddress, UI8 IOChan, UI32 DIOValue );
RTDACAPI_API UI32 RtdacPCID_ReadDigIO(        UI16 BaseAddress, UI8 IOChan );

// PWM functions
RTDACAPI_API UI8  RtdacPCI_PWMNoOfChans( UI16 BaseAddress );
RTDACAPI_API UI8  RtdacPCI_PWMChannel(   UI16 BaseAddress, UI8  ChanNo );
RTDACAPI_API UI8  RtdacPCI_PWMMode(      UI16 BaseAddress, UI8  Mode );
RTDACAPI_API UI16 RtdacPCI_PWMPrescaler( UI16 BaseAddress, UI16 Presc );
RTDACAPI_API UI16 RtdacPCI_PWMWidth(     UI16 BaseAddress, UI16 Width );
RTDACAPI_API void RtdacPCI_PWMRead(      UI16 BaseAddress, 
							       PUI8 pChanNo, PUI8 pMode, 
								   PUI16 pPresc, PUI16 pWidth );
RTDACAPI_API void RtdacPCI_PWMWrite(     UI16 BaseAddress, 
							       UI8 ChanNo, UI8 Mode, UI16 Presc, UI16 Width );

// Generator functions
RTDACAPI_API UI8  RtdacPCI_ReadNoOfGenerators( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ReadGeneratorL( UI16 BaseAddress, UI8 ChanNo );
RTDACAPI_API UI32 RtdacPCI_ReadGeneratorH( UI16 BaseAddress, UI8 ChanNo );
RTDACAPI_API UI32 RtdacPCI_WriteGeneratorL( UI16 BaseAddress, UI8 ChanNo, UI32 Value);
RTDACAPI_API UI32 RtdacPCI_WriteGeneratorH( UI16 BaseAddress, UI8 ChanNo, UI32 Value);

// Encoder functions
RTDACAPI_API UI8  RtdacPCI_ReadNoOfEncoders( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ResetEncoder(     UI16 BaseAddress, UI8  ChanNo, UI16 ResetFlag );
RTDACAPI_API UI16 RtdacPCI_ReadResetEncoder( UI16 BaseAddress, UI8  ChanNo );
RTDACAPI_API UI32 RtdacPCI_ReadEncoder(      UI16 BaseAddress, UI8  ChanNo );

// A/D and D/A functions
RTDACAPI_API UI32 RtdacPCI_AD( UI16 BaseAddress, UI8 ChanNo, UI8  Gain );
RTDACAPI_API UI32 RtdacPCI_DA( UI16 BaseAddress, UI8 ChanNo, UI16 DAValue );

// Interrupt functions
RTDACAPI_API UI8  RtdacPCI_ReadIntrFlags( UI16 BaseAddress );
RTDACAPI_API UI8  RtdacPCI_WriteIntrFlags( UI16 BaseAddress, UI8 Flags );
RTDACAPI_API UI16 RtdacPCI_ReadIntrStatus( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ReadIntrPeriod( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_WriteIntrPeriod( UI16 BaseAddress, UI32 Period );
RTDACAPI_API UI32 RtdacPCI_ReadIntrCOSMask( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_WriteIntrCOSMask( UI16 BaseAddress, UI32 Mask );
RTDACAPI_API UI32 RtdacPCI_ReadIntrCOSBefore( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCI_ReadIntrCOSAfter( UI16 BaseAddress );
// RT-DAC4-PCI-D functions
RTDACAPI_API UI32 RtdacPCID_ReadIntrFlags( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCID_WriteIntrFlags( UI16 BaseAddress, UI32 Flags );
RTDACAPI_API UI32 RtdacPCID_ReadIntrStatus( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCID_ReadIntrPeriod( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCID_WriteIntrPeriod( UI16 BaseAddress, UI32 Period );
RTDACAPI_API UI32 RtdacPCID_ReadIntrCOSMask( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCID_WriteIntrCOSMask( UI16 BaseAddress, UI32 Mask );
RTDACAPI_API UI32 RtdacPCID_ReadIntrCOSBefore( UI16 BaseAddress );
RTDACAPI_API UI32 RtdacPCID_ReadIntrCOSAfter( UI16 BaseAddress );
// FIFO functions
RTDACAPI_API UI16 RtdacPCI_FIFOPutData( UI16 BaseAddress, UI16 DA3, UI16 DA2, UI16 DA1, UI16 DA0 );
RTDACAPI_API void RtdacPCI_FIFOSetStatus( UI16 BaseAddress, UI8 Start, UI8 Reset,
							              UI32 DAPeriod, UI16 IntrTheshold );
RTDACAPI_API void RtdacPCI_FIFOGetStatus( UI16 BaseAddress, UI8 *Start, UI8 *WR, UI8 *Reset,
							              UI8 *Intr, UI8 *RD, UI8 *Empty, UI8 *Full, UI16 *Length,
							              UI32 *DAPeriod, UI16 *IntrTheshold );
