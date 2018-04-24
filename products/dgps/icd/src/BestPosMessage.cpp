/*
* BestPosMessage.cpp
* BestPos message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "BestPosMessage.h"
#include "DgpsData.h"
#include "DgpsStructs.h"
#include "LoggerProxy.h"
#include <cstring> // memset, memcpy

BestPosMessage::BestPosMessage(float hertz) : DgpsMessage(hertz) {
	
}

void BestPosMessage::FillMessage(const DgpsData& data) {
	PHS_BESTPOS msg;

	FillHeader(msg.HEADER);

	msg.sol_stat = E_SOLUTION_STATUS::E_SOLUTION_STATUS_SOL_COMPUTED;
	msg.pos_type = E_POSITION_OR_VELOCITY_TYPE::E_POSITION_OR_VELOCITY_TYPE_OMNISTAR_HP;

	msg.lat_Dgps = data.GetLatitude();
	msg.lon_Dgps = data.GetLongitude();
	msg.hgt_Dgps = data.GetAltitude();

	msg.undulation = 0;
	msg.datum_id = E_DATUM_DGPS::E_DATUM_DGPS_WGS84;
	msg.lat_sd = 0.05;
	msg.lon_sd = 0.05;
	msg.hgt_sd = 0.5;
	msg.stn_id = 1;
	msg.diff_age = 0.001;
	msg.sol_age = 0.001;
	msg.N_SVs = 8;
	msg.N_solnSVs = 8;
	msg.N_ggL1 = 8;
	msg.N_ggL1L2 = 8;
	msg.Byte_Reserved = 0;
	msg.ext_sol_state.Bit_AdVance_RTK_Verified = E_ADVANCE_RTK_VERIFIED::E_ADVANCE_RTK_VERIFIED_VERIFIED;
	msg.ext_sol_state.BITS_Pseudorange_lono_Correction = E_PSEUDORANGE_LONO_CORRECTION::E_PSEUDORANGE_LONO_CORRECTION_NOVATEL_BLENDED_LONO_VALUE;
	msg.ext_sol_state.BIT_Antena_Status = E_ANTENA_STATUS::NO_ANTENA_WARNING;
	msg.Byte_Reserved1 = 0;
	msg.sig_mask.Bit_GPS_L1_used_in_Solution = 1;
	msg.sig_mask.Bit_GPS_L2_used_in_Solution = 0;
	msg.sig_mask.Bit_GPS_L5_used_in_Solution = 0;
	msg.sig_mask.Bit_Reserved = 0;
	msg.sig_mask.Bit_GLONASS_L1_used_in_Solution = 0;
	msg.sig_mask.Bit_GLONASS_L2_used_in_Solution = 0;
	msg.sig_mask.TWO_BIT_RESERVED = 0;

	//CRC will calculate after copy data to the buffer
	msg.CRC = 0;

	bzero(m_buffer, BUFFER_SIZE);

	//HEADER
	FillHeaderInBuffer(msg.HEADER);

	//MESSAGE

	//sol_stat
	memcpy(m_buffer + HEADER_LEN, &msg.sol_stat, 4);

	//pos_type
	memcpy(m_buffer + HEADER_LEN + 4, &msg.pos_type, 4);

	//lat_Dgps
	memcpy(m_buffer + HEADER_LEN + 8 , &msg.lat_Dgps, 8);

	//lon_Dgps
	memcpy(m_buffer + HEADER_LEN + 16 , &msg.lon_Dgps, 8);

	//hgt_Dgps
	memcpy(m_buffer + HEADER_LEN + 24 , &msg.hgt_Dgps, 8);

	//undulation
	memcpy(m_buffer + HEADER_LEN + 32, &msg.undulation, 4);

	//datum_id
	memcpy(m_buffer + HEADER_LEN + 36, &msg.datum_id, 4);

	//lat_sd
	memcpy(m_buffer + HEADER_LEN + 40 , &msg.lat_sd, 4);

	//lon_sd
	memcpy(m_buffer + HEADER_LEN + 44, &msg.lon_sd, 4);

	//hgt_sd
	memcpy(m_buffer + HEADER_LEN + 48, &msg.hgt_sd, 4);

	//stn_id
	memcpy(m_buffer + HEADER_LEN + 52, &msg.stn_id, 4);

	//diff_age
	memcpy(m_buffer + HEADER_LEN + 56, &msg.diff_age, 4);

	//sol_age
	memcpy(m_buffer + HEADER_LEN + 60, &msg.sol_age, 4);

	//N_SVs
	memcpy(m_buffer + HEADER_LEN + 64, &msg.N_SVs, 1);

	//N_solnSVs
	memcpy(m_buffer + HEADER_LEN + 65 , &msg.N_solnSVs, 1);

	//N_ggL1
	memcpy(m_buffer + HEADER_LEN + 66, &msg.N_ggL1, 1);

	//N_ggL1L2
	memcpy(m_buffer + HEADER_LEN + 67, &msg.N_ggL1L2, 1);

	//Byte_Reserved
	memcpy(m_buffer + HEADER_LEN + 68, &msg.Byte_Reserved, 1);

	//ext_sol_state
	char solState = ExtractSolState(msg);
	memcpy(m_buffer + HEADER_LEN + 69, &solState, 1);

	//Byte_Reserved1
	memcpy(m_buffer + HEADER_LEN + 70, &msg.Byte_Reserved1, 1);

	//sig_mask
	char sigMask = ExtractSigMask(msg);
	memcpy(m_buffer + HEADER_LEN + 71, &sigMask, 1);

	//calculate CRC and insert it to the struct
	msg.CRC = CalcBlockCRC32(sizeof(msg) - sizeof(int), (unsigned char*)m_buffer);

	//CRC
	memcpy(m_buffer + sizeof(msg) - sizeof(int), ((char*)&msg.CRC), sizeof(unsigned int));
}

int BestPosMessage::GetMessageSize() const {
	return sizeof(PHS_BESTPOS);
}

E_MESSAGE_ID_INPUT_DGPS_DLV3 BestPosMessage::GetMessageID() const {
	return E_MESSAGE_ID_INPUT_DGPS_DLV3::E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTPOS;
}

char BestPosMessage::ExtractSolState(const PHS_BESTPOS& msg) const{
	char solState;
	bzero(&solState, 1);
	solState |= msg.ext_sol_state.Bit_AdVance_RTK_Verified << 0;
	solState |= msg.ext_sol_state.BITS_Pseudorange_lono_Correction << 1;
	solState |= msg.ext_sol_state.BIT_Antena_Status << 5;
	return solState;
}

char BestPosMessage::ExtractSigMask(const PHS_BESTPOS& msg) const{
	char sigMask;
	bzero(&sigMask, 1);
	sigMask |= msg.sig_mask.Bit_GPS_L1_used_in_Solution << 0;
	sigMask |= msg.sig_mask.Bit_GPS_L2_used_in_Solution << 1;
	sigMask |= msg.sig_mask.Bit_GPS_L5_used_in_Solution << 2;
	sigMask |= msg.sig_mask.Bit_Reserved << 3;
	sigMask |= msg.sig_mask.Bit_GLONASS_L1_used_in_Solution << 4;
	sigMask |= msg.sig_mask.Bit_GLONASS_L2_used_in_Solution << 5;
	sigMask |= msg.sig_mask.TWO_BIT_RESERVED << 6;
	sigMask |= msg.sig_mask.TWO_BIT_RESERVED << 7;
	return sigMask;
}
