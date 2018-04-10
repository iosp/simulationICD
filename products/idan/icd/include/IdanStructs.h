#ifndef IDAN_STRUCTS_H
#define IDAN_STRUCTS_H

/*
* IdanStructs.h
* Holds structs that are in use with IdanControl
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#pragma once

#define NOT_APPLIED		0
#define APPLIED			1

#define PARKING_BRAKE_RELEASE	0x1
#define PARKING_BRAKE_ENGAGE	0x2
#define PARKING_BREAKE_PROGRESS	0xd
#define PARKING_BREAKE_UNKNOWN	0xe

#define GEAR_R			(char)0x2
#define GEAR_N			(char)0x3
#define GEAR_D			(char)0x4
#define GEAR_UP			(char)0xF1
#define GEAR_DN			(char)0xF2


#define REPORTED_GEAR_R			0x2
#define REPORTED_GEAR_N			0x3
#define REPORTED_GEAR_1			0x4
#define REPORTED_GEAR_2			0x5
#define REPORTED_GEAR_3			0x6
#define REPORTED_GEAR_4			0x7
#define REPORTED_GEAR_5			0x8
#define REPORTED_GEAR_IN_PROG	0xd
#define REPORTED_GEAR_UNKNOWN	0xe

#define BATT_MAIN_LOW	1
#define BATT_BACKUP_LOW	2

#define PrimaryControlMsgID		0x50 // 100Hz
#define SecondaryControlMsgID	0x70 // UponChange
#define PrimaryReportMsgID		0x60 // 100Hz
#define PrimaryReportMsg2ID		0x64 // 100Hz
#define SecondaryReportMsgID	0x80 // 10Hz
#define SecondarySensorsMsgID	0x81 // 1Hz

// CanView deffinitions
#define CAN_VIEW_SOF				0x43
#define CAN_VIEW_EOF				'\r'
#define CAN_VIEW_SEND_11_BIT		0
#define CAN_VIEW_SEND_29_BIT		2
#define CAN_VIEW_SEND_11_REMOTE_BIT	4
#define CAN_VIEW_SEND_29_REMOTE_BIT	6

#define MODE_INIT				1
#define MODE_INIT_FAIL			2
#define MODE_OPER				5
#define MODE_E_STOP				12
#define MODE_ONE_HALF_SILENT	8
#define MODE_EMERGENCY			9
#define MODE_SHUT_DOWN			13

#define SACS_ON_CMD				0xb
#define SHUT_DOWN_CMD			0xa
#define EMERGENCY_ON_CMD		0xc

typedef struct 
{
	unsigned char ShutDownCmd;
	unsigned char EmergencyCmd;
	unsigned char SteerCmdMsb;
	unsigned char SteerCmdLsb;
	unsigned char GasCmdMsb;
	unsigned char GasCmdLsb;
	unsigned char MsgID;
	unsigned char SteerAsCenter;
} HLC_PrimaryControlMsgType;

typedef struct 
{
	unsigned char ShutDown;
	struct W1_T
	{
		unsigned char RoadLight : 1;
		unsigned char HighBeam : 1;
		unsigned char LightCutoff : 1;
		unsigned char ParkingLight : 1;
		unsigned char Sp : 4;
	}W1;
	struct W2_T
	{
		unsigned char KeySwitch : 1;
		unsigned char MotorStarter : 1;
		unsigned char Horn : 1;
		unsigned char LeftTurnSig : 1;
		unsigned char RightTurnSig : 1;
		unsigned char Hazards : 1;
		unsigned char Sp : 2;
	}W2;
	unsigned char Gear;
	unsigned char ParkingBrake;
	unsigned char EmergencyCmd;
	unsigned char MsgID;
	unsigned char SacsOnCmd;
}HLC_SecondaryControlMsgType;

typedef struct 
{
	struct W1_T
	{
		unsigned char ModeOfSteeringSAC : 5;
		unsigned char Disc1 : 1;
		unsigned char Disc2 : 1;
		unsigned char Disc3 : 1;
	}W1;
	//	unsigned char ModeOfSteeringSAC;
	unsigned char SteeringErrorSAC;
	struct W3_T
	{
		unsigned char SteerPosMsb : 4;
		unsigned char Sp : 4;
	}W3;
	unsigned char SteerPosLsb;
	struct W5_T
	{
		unsigned char ModeOfGasBrakeSAC : 5;
		unsigned char Disc1 : 1;
		unsigned char Disc2 : 1;
		unsigned char Disc3 : 1;
	}W5;
	//	unsigned char ModeOfGasBrakeSAC;
	unsigned char GasBrakeErrorSAC;
	struct W7_T
	{
		unsigned char GasPosMsb : 4;
		unsigned char Disc1 : 1;
		unsigned char Disc2 : 1;
		unsigned char Disc3 : 1;
		unsigned char Sp : 1;
	}W7;
	unsigned char GasPosLsb;
}IDAN_PrimaryReportMsgType;

typedef struct 
{
	struct W0_T
	{
		unsigned char Disc1 : 1;
		unsigned char Disc2 : 1;
		unsigned char Disc3 : 1;
		unsigned char SACSactive : 1;
		unsigned char Sp2 : 1;
		unsigned char MotorBreakeEnable : 1;
		unsigned char Sp1 : 2;
	}W0;
	struct W1_T
	{
		unsigned char RoadLight : 1;
		unsigned char HighBeam : 1;
		unsigned char LightCutoff : 1;
		unsigned char ParkingLights : 1;
		//		unsigned char BlackOutLights:1;
		unsigned char Sp : 4;
	}W1;
	struct W2_T
	{
		unsigned char KeySwitch : 1;
		unsigned char MotorStarter : 1;
		unsigned char Horn : 1;
		unsigned char LeftTurn : 1;
		unsigned char RightTurn : 1;
		unsigned char Hazard : 1;
		//		unsigned char Diffrential:2;
		unsigned char Sp : 2;
	}W2;
	struct W3_T
	{
		unsigned char ActualGear : 4;// new
		unsigned char ReqGear : 4;// new
	}W3;
	unsigned char ParkingBreak;
	unsigned char RPMmsb;// new
	unsigned char RPMlsb;// new
	unsigned char Velocity;// new
}IDAN_SecondaryReportMsgType;

typedef struct 
{
	unsigned char EngineTemp;
	unsigned char OilPress;
	unsigned char FuelLevel;
	unsigned char AlternatorVoltage;// new
	unsigned char BackupBattVoltage;
	unsigned char BatterySumUp;
	unsigned char AirPressFront;// new
	unsigned char AirPressRear;// new
}IDAN_SecondarySensorsMsgType;

typedef struct
{
	unsigned char CAN_SOF;
	unsigned char Length;
	unsigned char Command;
	unsigned short Id;
	unsigned char Data[8];
	unsigned char ChackSum;
	unsigned char CAN_EOF;
}Can11ShellMsgType;

typedef struct
{
	unsigned char CAN_SOF;
	unsigned char Length;
	unsigned char Command;
	unsigned short Id;
	unsigned char Data[8];
	unsigned char ChackSum;
	unsigned char CAN_EOF;
}CanView11RcvShellMsgType;

typedef struct
{
	;
}Msg_42_Type;

typedef struct
{
	unsigned char ErrorType;
	unsigned char ErrorCode;
}Msg_43_Type;


#pragma pack()


#endif // IDAN_STRUCTS_H