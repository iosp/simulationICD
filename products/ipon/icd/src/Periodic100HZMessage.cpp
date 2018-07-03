/*
* Periodic100HZMessage.cpp
* Ipon 100 HZ sensor message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "Periodic100HZMessage.h"
#include "IponData.h"
#include "IponStructs.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include <algorithm>

int Periodic100HZMessage::GetMessageSize() const {
    return sizeof(PHSPERIODIC100HZMESSAGE);
}

void Periodic100HZMessage::FillMessage(const IponData& data) {
	PHSPERIODIC100HZMESSAGE msg;

	msg.Message_ID_Accepted_From_EGI		= E_MESSAGE_ID_ACCEPTED_FROM_EGI::E_MESSAGE_ID_ACCEPTED_FROM_EGI_PERIODIC_100HZ; // ID for 100Hz message

	msg.Azimuth_PD_geographic				= data.Get100HZAzimuthGeo();
	msg.Pitch_PD_Egi 						= data.Get100HZPitch();
	msg.Roll_PD_Egi							= data.Get100HZRoll();

	msg.Roll_rate_X_PD_Egi					= data.Get100HZRollRateX();
	msg.Pitch_rate_Y_PD_Egi					= data.Get100HZPitchRateY();
	msg.Azimuth_rate_Z_PD_Egi				= data.Get100HZAzimuthRateZ();
	
	msg.ECC_X_Egi							= data.Get100HZEccX();
	msg.ECC_Y_Egi							= data.Get100HZEccY();
	msg.ECC_Z_Egi							= data.Get100HZEccZ();

	msg.Alt_correction_Egi					= 18; // defiantly not used in SAHAR				//value from the real IPON
	msg.Checksum_Egi						= 0; // defiantly not used in SAHAR

	std::fill(msg.Eight_byte_Spare, msg.Eight_byte_Spare + 8, 0); // defiantly not used in SAHAR

	//INS_Time_Of_Nav_Data is the second count begins with "0" each Sunday morning at midnight, Zulu time (Greenwich time)
	//At start up until GPS is available, INS time stars from 0
	msg.INS_Time_Of_Nav_Data				= data.Get100HZInsTimeOfNavData();

	msg.Input_Message_Number_Echo_Egi		= 0; // defiantly not used in SAHAR

	msg.Altitude_MSL_EGI					= data.Get100HZAltitude();
	msg.LAT_Egi								= data.Get100HZLatitude();
	msg.LONG_Egi							= data.Get100HZLongitude();

	msg.SOM									= 42405; // defiantly not used in SAHAR (value is the default by the ICD)

	msg.Validity_Word.Antena_Fail_Egi		= 0;
	msg.Validity_Word.External_Voltage_Fail_Egi = 0;
	msg.Validity_Word.GPS_Data_Not_Valid_Egi = 1;
	msg.Validity_Word.GPS_Fail_Egi			= 0;
	msg.Validity_Word.IMU_Fail_Egi			= 0;
	msg.Validity_Word.INS_Fail_Egi			= 0;
	msg.Validity_Word.NA1_Egi				= 0;
	msg.Validity_Word.NA2_Egi				= 0;
	msg.Validity_Word.NA3_Egi				= 0;
	msg.Validity_Word.NA4_Egi				= 0;
	msg.Validity_Word.NA5_Egi				= 0;
	msg.Validity_Word.NA_Egi				= 0;
	msg.Validity_Word.ODO_Fail_Egi			= 0;
	msg.Validity_Word.ONE_PPS_Fail_Egi		= 0;
	msg.Validity_Word.Severe_INS_Fail_Egi	= 0;
	msg.Validity_Word.Temperature_Fail_Egi 	= 1;

	msg.Velocity_East_Egi					= data.Get100HZVelocityEast();
	msg.Velocity_north_Egi 					= data.Get100HZVelocityNorth();
	msg.Velocity_down_Egi 					= data.Get100HVelocityDown();
	msg.blockLength							= 60; // defiantly not used in SAHAR (value is the default by the ICD)

	int offset = 0;
	//SUM
	unsigned short ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.SOM);
	CopyDataToBuffer(&ushTemp, sizeof(ushTemp), offset);
	
	//Message_ID_Accepted_From_EGI
	int iTemp = Utilities::LittleEndianToBig<E_MESSAGE_ID_ACCEPTED_FROM_EGI>(msg.Message_ID_Accepted_From_EGI);
	CopyDataToBuffer((char*)&iTemp + 3, 1, offset);

	//blockLength
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.blockLength);
	CopyDataToBuffer((char*)&ushTemp + 1, 1, offset);

	//INS_Time_Of_Nav_Data
	unsigned int uiTemp = Utilities::LittleEndianToBig<unsigned int>(msg.INS_Time_Of_Nav_Data);
	CopyDataToBuffer((char*)&uiTemp, uiTemp, offset);

	//LAT_Egi
	iTemp = Utilities::LittleEndianToBig<int>(msg.LAT_Egi);
	CopyDataToBuffer((char*)&iTemp, iTemp, offset);

	//LONG_Egi
	iTemp = Utilities::LittleEndianToBig<int>(msg.LONG_Egi);
	CopyDataToBuffer((char*)&iTemp, iTemp, offset);

	//Altitude_MSL_EGI
	iTemp = Utilities::LittleEndianToBig<int>(msg.Altitude_MSL_EGI);
	CopyDataToBuffer((char*)&iTemp, iTemp, offset);

	//Pitch_PD_Egi
	short shTemp = Utilities::LittleEndianToBig<short>(msg.Pitch_PD_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Roll_PD_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Roll_PD_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Azimuth_PD_geographic
	shTemp = Utilities::LittleEndianToBig<short>(msg.Azimuth_PD_geographic);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Roll_rate_X_PD_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Roll_rate_X_PD_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Pitch_rate_Y_PD_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Pitch_rate_Y_PD_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Azimuth_rate_Z_PD_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Azimuth_rate_Z_PD_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//ECC_X_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.ECC_X_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//ECC_Y_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.ECC_Y_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//ECC_Z_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.ECC_Z_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Velocity_north_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Velocity_north_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Velocity_East_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Velocity_East_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Velocity_down_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Velocity_down_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Alt_correction_Egi
	shTemp = Utilities::LittleEndianToBig<short>(msg.Alt_correction_Egi);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Validity_Word
	shTemp = 0;
	shTemp |= msg.Validity_Word.GPS_Data_Not_Valid_Egi << 15;
	shTemp |= msg.Validity_Word.Temperature_Fail_Egi << 14;
	shTemp |= msg.Validity_Word.NA_Egi << 13;
	shTemp |= msg.Validity_Word.NA1_Egi << 12;
	shTemp |= msg.Validity_Word.NA2_Egi << 11;
	shTemp |= msg.Validity_Word.NA3_Egi << 10;
	shTemp |= msg.Validity_Word.NA4_Egi << 9;
	shTemp |= msg.Validity_Word.NA5_Egi << 8;
	shTemp |= msg.Validity_Word.Severe_INS_Fail_Egi << 7;
	shTemp |= msg.Validity_Word.External_Voltage_Fail_Egi << 6;
	shTemp |= msg.Validity_Word.Antena_Fail_Egi << 5;
	shTemp |= msg.Validity_Word.ONE_PPS_Fail_Egi << 4;
	shTemp |= msg.Validity_Word.IMU_Fail_Egi << 3;
	shTemp |= msg.Validity_Word.GPS_Fail_Egi << 2;
	shTemp |= msg.Validity_Word.ODO_Fail_Egi << 1;
	shTemp |= msg.Validity_Word.INS_Fail_Egi << 0;

	shTemp = Utilities::LittleEndianToBig<unsigned short>(shTemp);
	CopyDataToBuffer((char*)&shTemp, shTemp, offset);

	//Input_Message_Number_Echo_Egi
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Input_Message_Number_Echo_Egi);
	CopyDataToBuffer((char*)&ushTemp, ushTemp, offset);

	//Eight_byte_Spare
	offset += 8;

	//Checksum_Egi
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Checksum_Egi);
	CopyDataToBuffer((char*)&ushTemp, ushTemp, offset);
}

IponMsgType Periodic100HZMessage::GetMsgType() const {
	return IPON_PERIODIC_100HZ;
}