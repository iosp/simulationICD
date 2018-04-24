/*
* ErrorsEstimationMessage.cpp
* INS status message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "ErrorsEstimationMessage.h"
#include "InsData.h"
#include <cstring>  // memset, memcpy

ErrorsEstimationMessage::ErrorsEstimationMessage(float hertz) : InsMessage(hertz) {

}

void ErrorsEstimationMessage::FillMessage(const InsData& data) {
	INS_Error_Estimation_Message msg;

	FillHeader(msg.Header);
	msg.Time_From_Startup = data.GetSimTime() * TIME_MULTIPLY;
	msg.UTC_Time = data.GetUtcTime() * TIME_MULTIPLY;
	msg.Horizontal_Error_CEP = data.GetHorizontalError() * 10;
	msg.Vertical_Error_PE = data.GetVerticalError() * 10;
	msg.Northing_Error = data.GetNorthingError() * 10;
	msg.Easting_Error =data.GetEastingError() * 10;
	msg.Altitude_Error = data.GetAltitudeError() * 10;
	msg.North_Velocity_Error = data.GetNorthVelocityError() * VEL_MULTIPLY;
	msg.East_Velocity_Error = data.GetEastVelocityError() * VEL_MULTIPLY;
	msg.Down_Velocity_Error = data.GetDownVelocityError() * VEL_MULTIPLY;
	msg.Azimuth_Error_Estimation = data.GetAzimuthErrorEstimation() * 10;
	msg.Pitch_Error_Estimation = data.GetPitchErrorEstimation() * 10;
	msg.Roll_Error_Estimation = data.GetRollErrorEstimation() * 10;

	// these fields are not parsed by the other side
	msg.GPS_Week = 0;
	memset(&msg.Data_Validity_Bitfield, 0, sizeof(msg.Data_Validity_Bitfield));
	msg.Reserved1 = 0;
	memset(&msg.Reserved2, 0, sizeof(msg.Reserved2));
	msg.Reserved3 = 0;
	msg.Drift_Gyro_X_Error = 0;
	msg.Drift_Gyro_Y_Error = 0;
	msg.Drift_Gyro_Z_Error = 0;
	msg.Bias_Acc_X_Error = 0;
	msg.Bias_Acc_Y_Error = 0;
	msg.Bias_Acc_Z_Error = 0;

	memcpy(m_buffer, &msg, sizeof(msg));
}

void ErrorsEstimationMessage::FillHeader(/* out */ INS_HEADER& header) const {
	header.Unit_Code = 0x3c;
	strncpy((char*)header.Operation_Code, "\x83\x3c", 2); // 0x3C80 - reverse from ICD 
	header.Length = sizeof(INS_Error_Estimation_Message) - sizeof(INS_HEADER);
}

int ErrorsEstimationMessage::GetMessageSize() const {
	return sizeof(INS_Error_Estimation_Message);
}