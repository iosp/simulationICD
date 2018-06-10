/*
* NovatelMessage.cpp
* Novatel message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "NovatelMessage.h"
#include "LoggerProxy.h"
#include <algorithm> / std::fill

void NovatelMessage::FillHeader(/* out */ NOVATEL_HEADER& header) const {
	header.Sync = 170;
	header.Sync1 = 68;
	header.Sync2 = 18;
	header.Header_Lgth = HEADER_LEN;
	header.Message_ID = GetMessageID();

	header.Message_Type = 0;
	header.Message_Type |= 1 << 0;
	header.Message_Type |= 1 << 6;

	header.Port_Address = 64;														//? - COM2
	header.Message_Length = GetMessageSize() - header.Header_Lgth - sizeof(unsigned int);
	header.Sequence = 0;
	header.Idle_Time = 61;															// percentage of time that the processor is idle
	header.Time_Status = E_GPS_TIME_STATUS::E_GPS_TIME_STATUS_FINE;					//
	header.Week = (time(NULL) - 315964800) / (7*24*60*60);							// computer time, not UTM (the real GPS time is UTM).
	header.ms = ((time(NULL) - 315964800) % (7*24*60*60)) * 1000; 					// milliseconds
	header.Receiver_Status = 0;														// flags
	header.Receiver_SW_Version = 1;	
}

void NovatelMessage::FillHeaderInBuffer(const NOVATEL_HEADER& header) {
	//sync
	memcpy(m_buffer, &header.Sync, 1);
	memcpy(m_buffer+1, &header.Sync1, 1);
	memcpy(m_buffer+2, &header.Sync2, 1);

	//Header
	unsigned char ucTemp = HEADER_LEN;
	memcpy(m_buffer+3, &ucTemp, 1);

	//Message_ID
	unsigned short tShort = header.Message_ID;
	memcpy(m_buffer+4, &tShort, 2);

	//Message_Type
	memcpy(m_buffer+6, &header.Message_Type, 1);

	//Port_Address
	memcpy(m_buffer+7, &header.Port_Address, 1);

	//Message_Length
	ucTemp = header.Message_Length;
	memcpy(m_buffer+8, &ucTemp, 1);

	//Sequence
	memcpy(m_buffer+10, &header.Sequence, 2);

	//Idle_Time
	memcpy(m_buffer+12, &header.Idle_Time, 1);

	//Time_Status
	memcpy(m_buffer+13, &header.Time_Status, 1);

	//Week
	memcpy(m_buffer+14, &header.Week, 2);

	//ms
	memcpy(m_buffer+16, &header.ms, 4);

	//Receiver_Status
	memcpy(m_buffer+20, &header.Receiver_Status, 4);

	//Reserved
	std::fill(m_buffer + 24, m_buffer + 26, 0);

	//Receiver_SW_Version
	memcpy(m_buffer+26, &header.Receiver_SW_Version, 2);
}

unsigned int NovatelMessage::CRC32Value(int i) const{
	int j;
	unsigned int ulCRC;

	ulCRC = i;
	for(j = 8 ; j > 0 ; j--) {
		if(ulCRC & 1) {
			ulCRC = (ulCRC >> 1) ^ CRC32_POLYNOMIAL;
		}
		else {
			ulCRC >>= 1;
		}
	}

	return ulCRC;
}
    
unsigned int NovatelMessage::CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const{
	unsigned int ulTemp1;
	unsigned int ulTemp2;
	unsigned int ulCRC = 0;

	while(ulCount-- != 0) {
		ulTemp1 = (ulCRC >> 8) & 0x00FFFFFFL;
		ulTemp2 = CRC32Value(((int)ulCRC ^ *data++) & 0xFF);
		ulCRC = ulTemp1 ^ ulTemp2;
	}
	return ulCRC;
}