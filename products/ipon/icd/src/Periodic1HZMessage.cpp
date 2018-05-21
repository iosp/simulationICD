/*
* Periodic1HZMessage.cpp
* Ipon 1 HZ sensor message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "Periodic1HZMessage.h"
#include "IponData.h"
#include "IponStructs.h"
#include "LoggerProxy.h"
#include "Helper.h"

int Periodic1HZMessage::GetMessageSize() const {
    return sizeof(PHSPERIODIC1HZMESSAGE);
}

void Periodic1HZMessage::FillMessage(const IponData& data) {
	PHSPERIODIC1HZMESSAGE msg;
	
	msg.SOM														= 42405; 		// defiantly not used in SAHAR (value is the default by the ICD)
	msg.Message_ID_Accepted_From_EGI							= E_MESSAGE_ID_ACCEPTED_FROM_EGI::E_MESSAGE_ID_ACCEPTED_FROM_EGI_PERIODIC_1HZ; // ID for 1Hz message
	msg.blockLength												= 60;
	msg.INS_Time_Of_Nav_Data									= data.Get1HZInsTime();
	msg.GPS_TINE_EGI											= data.Get1HZGpsTime();
	msg.INS_DISTANCE_TRAVELED									= 0;	// defiantly not used in SAHAR
	msg.GPS_LAT_Egi												= data.Get1HZLatitude();	// defiantly not used in SAHAR
	msg.GPS_LONG_Egi											= data.Get1HZLongitude(); // defiantly not used in SAHAR
	msg.GPS_Altitude_Egi										= data.Get1HZAltitude(); // defiantly not used in SAHAR
	msg.Alignment_Countdown										= 0;

	msg.Status_word.s1_status.INS_in_Exclusive_ZUPT_mode		= 0;
	msg.Status_word.s1_status.INS_in_startup_mode				= 0;
	msg.Status_word.s1_status.INS_in_survey_mode				= 1;
	msg.Status_word.s1_status.INS_normal_or_SH_or_move_align	= 0;
	msg.Status_word.s1_status.INS_ready_for_Align_on_the_move	= 0;
	msg.Status_word.s1_status.Position_update_request			= 0;
	msg.Status_word.s1_status.Startup_Complete					= 1;
	msg.Status_word.s1_status.Zero_velocity_stop_request		= 0;

	msg.Status_word.s2_status.Zero_Velocity_update_in_progress	= 1;
	msg.Status_word.s2_status.Travel_Lock_status				= 1;
	msg.Status_word.s2_status.NA_Egi							= 0;
	msg.Status_word.s2_status.NA1_Egi							= 0;
	msg.Status_word.s2_status.INS_or_ODO_or_GPS_malfunction		= 1;
	msg.Status_word.s2_status.INS_in_align_on_the_move			= 0;
	msg.Status_word.s2_status.INS_in_SH_align_mode				= 0;
	msg.Status_word.s2_status.INS_alert							= 0;

	msg.Status_word.s3_status.Degraded_Survey					= 0;
	msg.Status_word.s3_status.INS_in_motion						= 0;
	msg.Status_word.s3_status.NA1_Egi							= 0;
	msg.Status_word.s3_status.NA_Egi							= 0;
	msg.Status_word.s3_status.Odo_calibration_completed			= 0;
	msg.Status_word.s3_status.Odo_calibration_in_process		= 0;
	msg.Status_word.s3_status.Odo_damping_in_process			= 0;
	msg.Status_word.s3_status.Orientation_attitude_data_valid	= 1;

	msg.Status_word.s4_status.INS_SH_Shutdown_failed			= 0;
	msg.Status_word.s4_status.INS_Shutdown_complete_successful	= 0;
	msg.Status_word.s4_status.INS_in_standby_mode				= 0;
	msg.Status_word.s4_status.INS_wait_for_gps					= 0;
	msg.Status_word.s4_status.Integrated_mode_of_operation		= 1;
	msg.Status_word.s4_status.NA1_Egi							= 0;
	msg.Status_word.s4_status.NA_Egi							= 0;
	msg.Status_word.s4_status.SH_Shutdown_test_completed		= 0;
	msg.Azimuth_Error_RMS										= 26;										// value by the real IPON
	msg.Velocity_error_RMS										= 0.0099999998;
	msg.INS_Horizontal_Position_Error							= 1;
	msg.INS_Altitude_Error										= 1;
	msg.Roll_Error_RMS											= 0.1;
	msg.Pitch_Error_RMS											= 0.1;
	msg.Number_Of_Satellites									= 0;
	msg.Figure_Of_Merit											= E_FOM::E_FOM_SMALLER_THAN_25M;			// position error < 25m (1 sigma)
	msg.week													= data.Get1HZWeek();							// computer time, not UTM (the real GPS time is UTM).
	msg.GPS_UTC_offset											= 17;
	bzero(&msg.Bytes_2_reserved, 2);									// defiantly not used in SAHAR
	msg.Checksum_Egi											= 0;// defiantly not used in SAHAR
	
	int offset = 0;
	//SUM
	CopyDataToBuffer(&msg.SOM, sizeof(msg.SOM), offset);

	//Message_ID_Accepted_From_EGI
	int iTemp = Utilities::LittleEndianToBig<E_MESSAGE_ID_ACCEPTED_FROM_EGI>(msg.Message_ID_Accepted_From_EGI);
	CopyDataToBuffer((char*)&iTemp + 3, 1, offset); 

	//blockLength
	unsigned short ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.blockLength);
	CopyDataToBuffer((char*)&ushTemp + 1, 1, offset); 

	//INS_Time_Of_Nav_Data
	unsigned int uiTemp = Utilities::LittleEndianToBig<unsigned int>(msg.INS_Time_Of_Nav_Data);
	CopyDataToBuffer((char*)&uiTemp, sizeof(uiTemp), offset);

	//GPS_TINE_EGI
	iTemp = Utilities::LittleEndianToBig<int>(msg.GPS_TINE_EGI);
	CopyDataToBuffer((char*)&uiTemp, sizeof(iTemp), offset);

	//INS_DISTANCE_TRAVELED
	uiTemp = Utilities::LittleEndianToBig<unsigned int>(msg.INS_DISTANCE_TRAVELED);
	CopyDataToBuffer((char*)&uiTemp, sizeof(uiTemp), offset);

	//GPS_LAT_Egi
	iTemp = Utilities::LittleEndianToBig<int>(msg.GPS_LAT_Egi);
	CopyDataToBuffer((char*)&iTemp, sizeof(iTemp), offset);

	//GPS_LONG_Egi
	iTemp = Utilities::LittleEndianToBig<int>(msg.GPS_LONG_Egi);
	CopyDataToBuffer((char*)&iTemp, sizeof(iTemp), offset);

	//GPS_Altitude_Egi
	short shTemp = Utilities::LittleEndianToBig<short>( msg.GPS_Altitude_Egi);
	CopyDataToBuffer((char*)&shTemp, sizeof(shTemp), offset);

	//Alignment_Countdown
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Alignment_Countdown);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//structs
	char chTemp = msg.Status_word.s2_status.Zero_Velocity_update_in_progress << 7;
	chTemp |= msg.Status_word.s2_status.NA_Egi << 6;
	chTemp |= msg.Status_word.s2_status.INS_or_ODO_or_GPS_malfunction << 5;
	chTemp |= msg.Status_word.s2_status.Travel_Lock_status << 4;
	chTemp |= msg.Status_word.s2_status.NA1_Egi << 3;
	chTemp |= msg.Status_word.s2_status.INS_in_SH_align_mode << 2;
	chTemp |= msg.Status_word.s2_status.INS_alert << 1;
	chTemp |= msg.Status_word.s2_status.INS_in_align_on_the_move << 0;
	chTemp = msg.Figure_Of_Merit; // <----------------------------------------------------------??
	CopyDataToBuffer((char*)&chTemp, sizeof(chTemp), offset);

	chTemp |= msg.Status_word.s1_status.INS_in_startup_mode << 7;
	chTemp |= msg.Status_word.s1_status.Startup_Complete << 6;
	chTemp |= msg.Status_word.s1_status.INS_normal_or_SH_or_move_align << 5;
	chTemp |= msg.Status_word.s1_status.INS_in_survey_mode << 4;
	chTemp |= msg.Status_word.s1_status.INS_in_Exclusive_ZUPT_mode << 3;
	chTemp |= msg.Status_word.s1_status.Zero_velocity_stop_request << 2;
	chTemp |= msg.Status_word.s1_status.Position_update_request << 1;
	chTemp |= msg.Status_word.s1_status.INS_ready_for_Align_on_the_move << 0;
	CopyDataToBuffer((char*)&chTemp, sizeof(chTemp), offset);

	chTemp |= msg.Status_word.s4_status.SH_Shutdown_test_completed << 7;
	chTemp |= msg.Status_word.s4_status.Integrated_mode_of_operation << 6;
	chTemp |= msg.Status_word.s4_status.INS_SH_Shutdown_failed << 5;
	chTemp |= msg.Status_word.s4_status.INS_Shutdown_complete_successful << 4;
	chTemp |= msg.Status_word.s4_status.NA_Egi << 3;
	chTemp |= msg.Status_word.s4_status.INS_in_standby_mode << 2;
	chTemp |= msg.Status_word.s4_status.INS_wait_for_gps << 1;
	chTemp |= msg.Status_word.s4_status.NA1_Egi << 0;
	CopyDataToBuffer((char*)&chTemp, sizeof(chTemp), offset);

	chTemp |= msg.Status_word.s3_status.Odo_calibration_in_process << 7;
	chTemp |= msg.Status_word.s3_status.Odo_damping_in_process << 6;
	chTemp |= msg.Status_word.s3_status.Odo_calibration_completed << 5;
	chTemp |= msg.Status_word.s3_status.NA_Egi << 4;
	chTemp |= msg.Status_word.s3_status.NA1_Egi << 3;
	chTemp |= msg.Status_word.s3_status.INS_in_motion << 2;
	chTemp |= msg.Status_word.s3_status.Orientation_attitude_data_valid << 1;
	chTemp |= msg.Status_word.s3_status.Degraded_Survey << 0;
	CopyDataToBuffer((char*)&chTemp, sizeof(chTemp), offset);

	//Alert Structures
	offset += 8;

	//Azimuth_Error_RMS
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Azimuth_Error_RMS);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Velocity_error_RMS
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Velocity_error_RMS);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//INS_Horizontal_Position_Error
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.INS_Horizontal_Position_Error);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//INS_Altitude_Error
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.INS_Altitude_Error);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Roll_Error_RMS
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Roll_Error_RMS);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Pitch_Error_RMS
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Pitch_Error_RMS);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Number_Of_Satellites
	CopyDataToBuffer((char*)&msg.Number_Of_Satellites, sizeof(msg.Number_Of_Satellites), offset);

	//Figure_Of_Merit
	CopyDataToBuffer((char*)&msg.Figure_Of_Merit, sizeof(msg.Figure_Of_Merit), offset);

	//week
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.week);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//GPS_UTC_offset
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.GPS_UTC_offset);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Bytes_2_reserved
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Bytes_2_reserved);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);

	//Checksum_Egi
	ushTemp = Utilities::LittleEndianToBig<unsigned short>(msg.Checksum_Egi);
	CopyDataToBuffer((char*)&ushTemp, sizeof(ushTemp), offset);
}

IponMsgType Periodic1HZMessage::GetMsgType() const {
	return IPON_PERIODIC_1HZ;
}