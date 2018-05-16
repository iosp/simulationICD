/*
* BestVelMessage.cpp
* BestVel message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "BestVelMessage.h"
#include "DgpsData.h"
#include "LoggerProxy.h"
#include <cstring> // memset, memcpy

void BestVelMessage::FillMessage(const DgpsData& data) {
	PHS_BESTVEL msg;

	FillHeader(msg.HEADER);

	msg.sol_stat = E_SOLUTION_STATUS::E_SOLUTION_STATUS_SOL_COMPUTED;
	msg.vel_type = E_POSITION_OR_VELOCITY_TYPE::E_POSITION_OR_VELOCITY_TYPE_OMNISTAR_HP;
	msg.latency = 0.250;
	msg.age = 4.000;
	msg.hor_spd = data.GetBestVelLatitude();
	msg.trk_gnd = data.GetBestVelLongitude();

	msg.vert_spd = data.GetBestVelAltitude();
	msg.Four_Float_Reserved = 0;

	//CRC will calculate after copy data to the buffer
	msg.CRC = 0;

	bzero(m_buffer, BUFFER_SIZE);

	//HEADER
	FillHeaderInBuffer(msg.HEADER);

	//MESSAGE
	//sol_stat
	memcpy(m_buffer + HEADER_LEN, (char*)&msg.sol_stat, 4);

	//vel_type
	memcpy(m_buffer + HEADER_LEN + 4, (char*)&msg.vel_type, 4);

	//latency
	memcpy(m_buffer + HEADER_LEN + 8, (char*)&msg.latency, 4);

	//age
	memcpy(m_buffer + HEADER_LEN + 12, (char*)&msg.age, 4);

	//hor_spd
	memcpy(m_buffer + HEADER_LEN + 16, (char*)&msg.hor_spd, 8);

	//trk_gnd
	memcpy(m_buffer + HEADER_LEN + 24, (char*)&msg.trk_gnd, 8);

	//vert_spd
	memcpy(m_buffer + HEADER_LEN + 32, (char*)&msg.vert_spd, 8);

	//Four_Float_Reserved
	memcpy(m_buffer + HEADER_LEN + 40, (char*)&msg.Four_Float_Reserved, 4);


	//calculate CRC and insert it to the struct
	msg.CRC = CalcBlockCRC32(sizeof(msg) - sizeof(int), (unsigned char*)m_buffer);

	//CRC
	memcpy(m_buffer + sizeof(msg) - sizeof(int), ((char*)&msg.CRC), sizeof(unsigned int));
}

int BestVelMessage::GetMessageSize() const {
	return sizeof(PHS_BESTVEL);
}

E_MESSAGE_ID_INPUT_DGPS_DLV3 BestVelMessage::GetMessageID() const {
	return E_MESSAGE_ID_INPUT_DGPS_DLV3::E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTVEL;
}