#ifndef INSTRUCTS_H
#define INSTRUCTS_H

/*
* InsStructs.h
* Holds structs of Ins ICD
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

// basic types
typedef unsigned char 	Byte;
typedef char			SByte;
typedef short 			Int16;
typedef unsigned short	UInt16;
typedef int				Int32;
typedef unsigned int	UInt32;
typedef float			Single;

struct INS_HEADER {
	Byte 		Unit_Code;
	Byte		Operation_Code[2];
	UInt16		Length;
} __attribute__((packed));

typedef enum  : char {
	ZONETYPE_EXTENDED = 0x00,	// IDF extended zone type
	ZONETYPE_NORMAL =	0x01	// Normal zone type
} E_INS_ZoneType; // determining the zone type

typedef enum : char {
	GEOID_EGM96 = 	0x01,
	GEOID_EGM08 = 	0x02
} E_INS_Geoid;

struct INS_Echo_Message {
	INS_HEADER		Header;
} __attribute__((packed)); 

struct INS_Status_Message {
	INS_HEADER		Header;
	UInt32			Time_From_Startup;		// mission time. Units: seconds
	UInt32			UTC_Time;				// in seconds
	UInt16			GPS_Week;				// Units: week
	Byte			Data_Validity_Bitfield[2];
	UInt16			Align_Time_CountDown;	// second
	UInt16			GPS_Leap_Time;			// second
	SByte			Zone;
	E_INS_ZoneType	Zone_Type;
	Byte			Datum;						// E_INS_Datum
	E_INS_Geoid		Geoid;
	Byte			System_Status_Bitfield[8];
	Byte			System_Alert_Bitfield[10];
	Byte			Error_Table_Bitfield[4];
	UInt16			System_Internal_Bits_Bitfield[20];
	Byte			Spare[12]; 					// NULLS
} __attribute__((packed));

struct INS_Navigation_Data_Message {
	INS_HEADER		Header;
	UInt32			Time_From_Startup;		// mission time. Units: seconds
	UInt32			UTC_Time;				// in seconds
	UInt16			GPS_Week;				// Units: week
	Byte			Data_Validity_Bitfield[2];
	UInt32			UTM_Northing;			// meters
	UInt32			UTM_Easting;			// meters
	Int32			Altitude;				// meters
	SByte			Zone;
	E_INS_ZoneType	Zone_Type;
	Int32			Geo_Latitude;			// Degrees
	Int32			Geo_Longitude;			// Degrees
	Byte			UTM_Datum;
	Byte			Geo_Datum;
	E_INS_Geoid		Geoid;					//
	UInt16			PD_Azimuth;				// mils
	Int16			PD_Pitch;				// mils
	Int16 			PD_Roll;				// mils
	UInt16			Azimuth_Rate; 			// mils
	Int32 			North_Velocity;			// Meter/sec
	Int32			East_Velocity; 			// Meter/sec
	Int32			Down_Velocity;			// Meter/sec
	UInt32			Distance_Traveled;		// Meter
	UInt32			Odometer_Distance;		// Meter
	UInt32			Reserved_Pulses;		// Odo pulses
	Byte			Motion_Detected;
	UInt16			Reserved_Hull_Azimuth; 	// mils
	Int16			Reserved_Hull_Pitch; 	// mils
	Int16			Reserved_Hull_Roll;		// mils
	Byte			Spare[6];				// nulls
} __attribute__((packed));


struct S_INS_GPSStatus {
	Byte 			dummy; 					// maintenance purpose only
} __attribute__((packed)); // Used to indicate on the status of the GPS card

struct S_INS_GPSNav{
	Byte			dummy[2]; 				// maintenance purpose only
}  __attribute__((packed)); // Used to indicate on the operation models of the GPS card

struct S_INS_GPSErrorBITs{
	Byte			dummy[4]; 				// maintenance purpose only
}  __attribute__((packed)); // Used to indicate on the BITs(Built in Test) of the GPS card

struct INS_Internal_GPS {
	INS_HEADER			Header;
	UInt32				Time_From_Startup;		// mission time. Units: seconds
	UInt32				UTC_Time;				// in seconds
	UInt16				GPS_Week;				// Units: week
	Byte				Data_Validity_Bitfield[2];
	UInt32				GPS_UTM_Northing;		// meters
	UInt32				GPS_UTM_Easting;		// meters
	Int32				GPS_Altitude;			// meters
	Int32 				North_Velocity;			// Meter/sec
	Int32				East_Velocity; 			// Meter/sec
	Int32				Down_Velocity;			// Meter/sec
	S_INS_GPSStatus		GPS_Status;
	S_INS_GPSNav		GPS_Navigation_Mode;
	Byte				RESIDUAL[2];
	S_INS_GPSErrorBITs	GPS_Error_Bits;
	Byte				Signals_SNRs[12];
	Byte				GPS_FOM;
	UInt16				GPS_EHE;				// meters
	UInt16				GPS_EVE;				// meters
	Byte				GPS_HDOP;
	Byte				GPS_VDOP;
	Byte				GPS_TDOP;
	Byte				Num_Of_Satelites_In_Nav_Sol;
	SByte				GPS_Zone;
	E_INS_ZoneType		Zone_Type;
	Byte				Datum;
	E_INS_Geoid			Geoid;
	UInt16				Reserved_A2DLevel;
	UInt16				Reserved_RFImmun;
	Byte				Spare[12];				// nulls
} __attribute__((packed));


struct INS_Error_Estimation_Message {
	INS_HEADER			Header;
	UInt32				Time_From_Startup;		// mission time. Units: seconds
	UInt32				UTC_Time;				// in seconds
	UInt16				GPS_Week;				// Units: week
	Byte				Data_Validity_Bitfield[2];
	UInt16				Horizontal_Error_CEP;	// Meters
	UInt16				Vertical_Error_PE;		// Meters	
	UInt16				Northing_Error;			// Meters	
	UInt16				Easting_Error;			// Meters	
	UInt16				Altitude_Error;			// Meters	
	UInt16				North_Velocity_Error;	// Meter/sec
	UInt16				East_Velocity_Error;	// Meter/sec
	UInt16				Down_Velocity_Error;	// Meter/sec
	UInt16				Azimuth_Error_Estimation;	// Mils
	UInt16				Pitch_Error_Estimation;	// Mils
	UInt16				Roll_Error_Estimation;	// Mils
	UInt16				Reserved1;
	Byte				Reserved2[4];
	UInt32				Reserved3;
	UInt16				Drift_Gyro_X_Error;		// Deg/h
	UInt16				Drift_Gyro_Y_Error;		// Deg/h
	UInt16				Drift_Gyro_Z_Error;		// Deg/h
	UInt16				Bias_Acc_X_Error;		//
	UInt16				Bias_Acc_Y_Error;		// 
	UInt16				Bias_Acc_Z_Error;		//
}  __attribute__((packed));

#endif // INSTRUCTS_H