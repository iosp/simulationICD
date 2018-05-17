/*
* NavigationDataMessage.cpp
* INS navigation data message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "NavigationDataMessage.h"
#include "InsData.h"
#include <cstring>  // memset, memcpy

void NavigationDataMessage::FillMessage(const InsData& data) {
	INS_Navigation_Data_Message msg;
	
	FillHeader(msg.Header);
	msg.Time_From_Startup = data.GetSimTime() * TIME_MULTIPLY;
	msg.UTC_Time = data.GetUtcTime() * TIME_MULTIPLY;
	msg.Altitude = (data.GetInsNavAltitude() * 10); // other side multiply by 0.1
	msg.Geo_Latitude = (data.GetNavDataLatitude() * 1e7); // other side multiply by 0.0000001
	msg.Geo_Longitude = (data.GetNavDataLongitude() * 1e7); // other side multiply by 0.0000001
	msg.PD_Azimuth = (data.GetNavDataAzimuth() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.PD_Pitch = (data.GetNavDataPitch() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.PD_Roll = (data.GetNavDataRoll() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.Azimuth_Rate = (data.GetNavDataAzimuthRate() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.North_Velocity = (data.GetNavDataNorthVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.East_Velocity = (data.GetNavDataEastVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.Down_Velocity = (data.GetNavDataDownVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.Distance_Traveled = (data.GetNavDataDistanceTraveled() * 10); // other side multiply by 0.1
	msg.Odometer_Distance = (data.GetNavDataOdometerDistance() * 10); // other side multiply by 0.1
	msg.Motion_Detected = data.IsNavDataMotionDetected();

	// these fields are not parsed by the other side
	msg.GPS_Week = 0;
	memset(&msg.Data_Validity_Bitfield, 0, sizeof(msg.Data_Validity_Bitfield));
	msg.UTM_Northing = 0;
	msg.UTM_Easting = 0;
	msg.Zone = 0;
	msg.Zone_Type = ZONETYPE_NORMAL;
	msg.UTM_Datum = 0;
	msg.Geo_Datum = 0;
	msg.Geoid = GEOID_EGM96;
	msg.Reserved_Pulses = 0;
	msg.Reserved_Hull_Azimuth = 0;
	msg.Reserved_Hull_Pitch = 0;
	msg.Reserved_Hull_Roll = 0;
	memset(&msg.Spare, 0, sizeof(msg.Spare));

	memcpy(m_buffer, &msg, sizeof(msg));
}

void NavigationDataMessage::FillHeader(/* out */ INS_HEADER& header) const {
	header.Unit_Code = 0x3c;
	strncpy((char*)header.Operation_Code, "\x80\x3c", 2); // 0x3C80 - reverse from ICD 
	header.Length = sizeof(INS_Navigation_Data_Message) - sizeof(INS_HEADER);
}

int NavigationDataMessage::GetMessageSize() const {
	return sizeof(INS_Navigation_Data_Message);
}

InsMsgType NavigationDataMessage::GetMsgType() const {
	return INS_NAVIGATION_DATA_MSG;
}