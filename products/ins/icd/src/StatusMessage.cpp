/*InsMesssage
* StatusMessage.cpp
* INS status message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "StatusMessage.h"
#include "InsData.h"
#include "InsStructs.h"

static const int TTS_STATUS_MESSAGE = 1e7;

StatusMessage::StatusMessage() : InsMessage(TTS_STATUS_MESSAGE) {

}

void StatusMessage::FillMessage(const InsData& data) {
	char tmpBuffer[10]{0};
	INS_Status_Message msg;
	FillHeader(msg.Header);
	msg.Time_From_Startup = data.GetSimTime().total_microseconds() * TIME_MULTIPLY;
	msg.UTC_Time = data.GetUtcTime().total_microseconds() * TIME_MULTIPLY;
	msg.Align_Time_CountDown = 60;
	
	GetDataValidityBitfield(tmpBuffer, 10);
	strncpy((char*)msg.Data_Validity_Bitfield, tmpBuffer, sizeof(msg.Data_Validity_Bitfield));
	memset(&tmpBuffer, 0, sizeof(tmpBuffer));

	GetSystemStatusBitfield(tmpBuffer, 10);
	strncpy((char*)msg.System_Status_Bitfield, tmpBuffer, sizeof(msg.System_Status_Bitfield));
	memset(&tmpBuffer, 0, sizeof(tmpBuffer));

	GetSystemAlertBitfield(tmpBuffer, 10);
	strncpy((char*)msg.System_Alert_Bitfield, tmpBuffer, sizeof(msg.System_Alert_Bitfield));
	memset(&tmpBuffer, 0, sizeof(tmpBuffer));

	// these fields are not parsed by the real system
	msg.GPS_Week = 0;
	msg.GPS_Leap_Time = 0;
	msg.Zone = 0;
	msg.Zone_Type = ZONETYPE_NORMAL;
	msg.Datum = 0;
	msg.Geoid = GEOID_EGM96;
	memset(&msg.Error_Table_Bitfield, 0, sizeof(msg.Error_Table_Bitfield));
	memset(&msg.System_Internal_Bits_Bitfield, 0, sizeof(msg.System_Internal_Bits_Bitfield));
	memset(&msg.Spare, 0, sizeof(msg.Spare));

	memcpy(m_buffer, &msg, sizeof(msg));
}

void StatusMessage::FillHeader(/* out */ INS_HEADER& header) const {
	header.Unit_Code = 0x3C;
	strncpy((char*)header.Operation_Code, "\x3C\x09", 2);
	header.Length = sizeof(INS_Status_Message) - sizeof(INS_HEADER);
}