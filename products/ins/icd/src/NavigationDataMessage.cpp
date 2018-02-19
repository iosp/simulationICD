/*
* NavigationDataMessage.cpp
* INS navigation data message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "NavigationDataMessage.h"
#include "InsData.h"
#include "InsStructs.h"

NavigationDataMessage::NavigationDataMessage(int hertz) : InsMessage(hertz) {

}

void NavigationDataMessage::FillMessage(const InsData& data) {
	INS_Navigation_Data_Message msg;
	
	FillHeader(msg.Header);
	msg.Time_From_Startup = data.GetSimTime().total_microseconds() * TIME_MULTIPLY;
	msg.UTC_Time = data.GetUtcTime().total_microseconds() * TIME_MULTIPLY;
	msg.Altitude = (data.GetAltitude() * 10); // other side multiply by 0.1
	msg.Geo_Latitude = (data.GetLatitude() * 1e7); // other side multiply by 0.0000001
	msg.Geo_Longitude = (data.GetLongitude() * 1e7); // other side multiply by 0.0000001
	msg.PD_Azimuth = (data.GetAzimuth() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.PD_Pitch = (data.GetPitch() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.PD_Roll = (data.GetRoll() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.Azimuth_Rate = (data.GetAzimuthRate() * 10); // other side multiply by 0.1, divide by 6400 and multiply by 360 (degree convert)
	msg.North_Velocity = (data.GetNorthVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.East_Velocity = (data.GetEastVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.Down_Velocity = (data.GetDownVelocity() * VEL_MULTIPLY); // other side divide by 2^-8
	msg.Distance_Traveled = (data.GetDistanceTraveled() * 10); // other side multiply by 0.1
	msg.Odometer_Distance = (data.GetOdometerDistance() * 10); // other side multiply by 0.1
	msg.Motion_Detected = data.IsMotionDetected();

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
	header.Unit_Code = 0x3C;
	strncpy((char*)header.Operation_Code, "\x3C\x80", 2); // 0x3C80
	header.Length = sizeof(INS_Navigation_Data_Message) - sizeof(INS_HEADER);
}

int NavigationDataMessage::GetMessageSize() const {
	return sizeof(INS_Navigation_Data_Message);
}