

#define NOT_APPLIED		0
#define APPLIED			1

#define PARKING_BREAKE_RELEASED	0x1
#define PARKING_BREAKE_ENGAGED	0x2
#define PARKING_BREAKE_PROGRESS	0xd
#define PARKING_BREAKE_UNKNOWN	0xe

#define GEAR_R			0x2
#define GEAR_N			0x3
#define GEAR_D			0x4
#define GEAR_UP			0xF1
#define GEAR_DN			0xF2
//#define GEAR_IN_PROS	0xa
//#define GEAR_UNKNOWN	0xb

#define REPORTED_GEAR_R			0x2
#define REPORTED_GEAR_N			0x3
#define REPORTED_GEAR_1			0x4
#define REPORTED_GEAR_2			0x5
#define REPORTED_GEAR_3			0x6
#define REPORTED_GEAR_4			0x7
#define REPORTED_GEAR_5			0x8
#define REPORTED_GEAR_IN_PROG	0xd
#define REPORTED_GEAR_UNKNOWN	0xe

#define PARKING_BRAKE_RELEASE	0x1
#define PARKING_BRAKE_ENGAGE	0x2
#define PARKING_BRAKE_IN_PROS	0xd
#define PARKING_BRAKE_UNKNOWN	0xe

#define BATT_MAIN_LOW	1
#define BATT_BACKUP_LOW	2

#define PrimaryControlMsgID		0x50 // 100Hz
#define SecondaryControlMsgID	0x70 // UponChange
#define PrimaryReportMsgID		0x60 // 100Hz // 0x60
#define PrimaryReportMsg2ID		0x64 // 100Hz // 0x64
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


