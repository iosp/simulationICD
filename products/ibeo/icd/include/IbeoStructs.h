#ifndef IBEO_STRUCTS_H
#define IBEO_STRUCTS_H

/*
* IbeoStructs.h
* Holds structs that are in use with IbeoControl
* Author: Binyamin Appelbaum
* Date: 22.04.18
*/

#pragma pack(1)

typedef struct
{
	 unsigned int   	MagicWord;
	 unsigned int       SizePreviousMessage;
	 unsigned int	    SizeCurrentMessage;
	 unsigned char		Reserved;
	 unsigned char	    DeviceID;
	 unsigned short		DataType;
	 unsigned int      	time_up;	// NTP64    in seconds
	 unsigned int      	time_down;  // NTP64   after the floathing point

} ibeoScanDataHeader;

typedef struct
{
	unsigned char   	Layer_Echo;
	unsigned char   	Flags;
	short           	HorizontalAngel;
	unsigned short  	RadialDistance;
	unsigned short  	EchoPulseWidth;
	unsigned short  	Reserved;
} IbeoScanPoint;

typedef struct
{
	 unsigned short   	ScanNumber;
	 unsigned short   	ScannerStatus;
	 unsigned short	  	SyncPhaseOffset;
	 unsigned int    	ScanStratTimeDOWN;	// NTP64   after the floathing point
	 unsigned int    	ScanStratTimeUP;		// NTP64   in seconds
	 unsigned int    	ScanEndTimeDOWN;
	 unsigned int    	ScanEndTimeUP;
	 unsigned short   	AnglesTicks;
	 short			  	StartAngle;
	 short		      	EndAngle;
	 unsigned short   	ScanPoints;
	 short			  	PositionYaw;
	 short			  	PositionPitch;
	 short            	PositionRoll;
	 short			  	PositionX;
	 short			  	PositionY;
	 short			  	PositionZ;
	 unsigned short   	Reserved;
} IbeoScanHeader;

typedef struct
{
	ibeoScanDataHeader  Header;
	IbeoScanHeader		Scan;
	IbeoScanPoint*		Point;
} SibeoScanData;

typedef struct
{
	ibeoScanDataHeader  Header;
	unsigned short commandID;
//	unsigned short reserved;
} ReplayMSG;

#endif
