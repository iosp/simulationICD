/*
* DgpsControl.cpp
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "DgpsControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "RSCommunication.h"
#include "DgpsConfig.h"

static const int HEADER_LEN = 28;

DgpsControl::DgpsControl(const std::string& confFilePath) {
	m_dgpsConf = new DgpsConfig(confFilePath);
	m_comm = new RSCommunication(m_dgpsConf->GetPortName(), m_dgpsConf->GetBaudRate());
	m_sleepTimeBetweenEverySend = (1e7 / m_dgpsConf->GetHertz()); // TODO - check this change!!
}

DgpsControl::~DgpsControl() {
	m_sendDataThread.interrupt();
	delete m_dgpsConf;
	delete m_comm;
}

void DgpsControl::Run() {
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}
	m_sendDataThread = boost::thread(&DgpsControl::SendThreadMethod, this);
}

DgpsData* DgpsControl::GetData() {
	ERRLOG << "This function is not implemented!\n";
    return nullptr;
}

void DgpsControl::SetData(const DgpsData& data) {
	m_dgpsData_mutex.lock();
	m_dgpsDataCollection.push(data);
	m_dgpsData_mutex.unlock();
}

void DgpsControl::SendThreadMethod() {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	
	while (true) {
		DgpsData data;
		m_dgpsData_mutex.lock();
		bool hasValue = m_dgpsDataCollection.pop(data);
		m_dgpsData_mutex.unlock();
		
		if (hasValue) {
			DBGLOG << "Going to send data: " << data.toString() << "\n";
			SendBestVelData(data);
			SendBestPosData(data);
		}

		Utilities::SleepForRestTime(startTime, m_sleepTimeBetweenEverySend);
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

void DgpsControl::SendBestVelData(const DgpsData& data) {
	FillBestVel(data);
	SendBuffer(m_BestVelBuffer, sizeof(m_BestVelBuffer));	
}

void DgpsControl::SendBestPosData(const DgpsData& data) {
	FillBestPos(data);
	SendBuffer(m_BestPosBuffer, sizeof(m_BestPosBuffer));
}

void DgpsControl::SendBuffer(const char* buffer, int sizeOfData) const {
	bool allSent = false;
	while (!allSent) {
		int bytesSent =	m_comm->SendData(buffer, sizeOfData);
		allSent = (bytesSent >= sizeof(buffer));
		if (!allSent) {
			ERRLOG << "Couldn't send all buffer data. Retrying...\n";
		}
	}
}

void DgpsControl::FillBestVel(const DgpsData& data) {
	PHS_BESTVEL msg;

	FillDefaultHeader(msg.HEADER, E_MESSAGE_ID_INPUT_DGPS_DLV3::E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTVEL, sizeof(PHS_BESTVEL));

	msg.sol_stat = E_SOLUTION_STATUS::E_SOLUTION_STATUS_SOL_COMPUTED;
	msg.vel_type = E_POSITION_OR_VELOCITY_TYPE::E_POSITION_OR_VELOCITY_TYPE_OMNISTAR_HP;
	msg.latency = 0.250;
	msg.age = 4.000;
	msg.hor_spd = data.GetLatSpeed();
	msg.trk_gnd = data.GetLongSpeed();

	msg.vert_spd = data.GetAltAzimuth();
	msg.Four_Float_Reserved = 0;

	//CRC will calculate after copy data to the buffer
	msg.CRC = 0;

	bzero(m_BestVelBuffer, BUFFER_SIZE);


	//HEADER
	FillHeaderInBuffer(msg.HEADER, m_BestVelBuffer);


	//MESSAGE
	//sol_stat
	memcpy(m_BestVelBuffer + HEADER_LEN, (char*)&msg.sol_stat, 4);

	//vel_type
	memcpy(m_BestVelBuffer + HEADER_LEN + 4, (char*)&msg.vel_type, 4);

	//latency
	memcpy(m_BestVelBuffer + HEADER_LEN + 8, (char*)&msg.latency, 4);

	//age
	memcpy(m_BestVelBuffer + HEADER_LEN + 12, (char*)&msg.age, 4);

	//hor_spd
	memcpy(m_BestVelBuffer + HEADER_LEN + 16, (char*)&msg.hor_spd, 8);

	//trk_gnd
	memcpy(m_BestVelBuffer + HEADER_LEN + 24, (char*)&msg.trk_gnd, 8);

	//vert_spd
	memcpy(m_BestVelBuffer + HEADER_LEN + 32, (char*)&msg.vert_spd, 8);

	//Four_Float_Reserved
	memcpy(m_BestVelBuffer + HEADER_LEN + 40, (char*)&msg.Four_Float_Reserved, 4);


	//calculate CRC and insert it to the struct
	msg.CRC = CalcBlockCRC32(sizeof(msg) - sizeof(int), (unsigned char*)m_BestVelBuffer);

	//CRC
	memcpy(m_BestVelBuffer + sizeof(msg) - sizeof(int), ((char*)&msg.CRC), sizeof(unsigned int));
}

void DgpsControl::FillBestPos(const DgpsData& data) {
	PHS_BESTPOS msg;

	FillDefaultHeader(msg.HEADER, E_MESSAGE_ID_INPUT_DGPS_DLV3::E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTPOS, sizeof(PHS_BESTPOS));


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

	bzero(m_BestPosBuffer, BUFFER_SIZE);


	//HEADER

	FillHeaderInBuffer(msg.HEADER, m_BestPosBuffer);

	//MESSAGE

	//sol_stat
	memcpy(m_BestPosBuffer + HEADER_LEN, &msg.sol_stat, 4);

	//pos_type
	memcpy(m_BestPosBuffer + HEADER_LEN + 4, &msg.pos_type, 4);

	//lat_Dgps
	memcpy(m_BestPosBuffer + HEADER_LEN + 8 , &msg.lat_Dgps, 8);

	//lon_Dgps
	memcpy(m_BestPosBuffer + HEADER_LEN + 16 , &msg.lon_Dgps, 8);

	//hgt_Dgps
	memcpy(m_BestPosBuffer + HEADER_LEN + 24 , &msg.hgt_Dgps, 8);

	//undulation
	memcpy(m_BestPosBuffer + HEADER_LEN + 32, &msg.undulation, 4);

	//datum_id
	memcpy(m_BestPosBuffer + HEADER_LEN + 36, &msg.datum_id, 4);

	//lat_sd
	memcpy(m_BestPosBuffer + HEADER_LEN + 40 , &msg.lat_sd, 4);

	//lon_sd
	memcpy(m_BestPosBuffer + HEADER_LEN + 44, &msg.lon_sd, 4);

	//hgt_sd
	memcpy(m_BestPosBuffer + HEADER_LEN + 48, &msg.hgt_sd, 4);

	//stn_id
	memcpy(m_BestPosBuffer + HEADER_LEN + 52, &msg.stn_id, 4);

	//diff_age
	memcpy(m_BestPosBuffer + HEADER_LEN + 56, &msg.diff_age, 4);

	//sol_age
	memcpy(m_BestPosBuffer + HEADER_LEN + 60, &msg.sol_age, 4);

	//N_SVs
	memcpy(m_BestPosBuffer + HEADER_LEN + 64, &msg.N_SVs, 1);

	//N_solnSVs
	memcpy(m_BestPosBuffer + HEADER_LEN + 65 , &msg.N_solnSVs, 1);

	//N_ggL1
	memcpy(m_BestPosBuffer + HEADER_LEN + 66, &msg.N_ggL1, 1);

	//N_ggL1L2
	memcpy(m_BestPosBuffer + HEADER_LEN + 67, &msg.N_ggL1L2, 1);

	//Byte_Reserved
	memcpy(m_BestPosBuffer + HEADER_LEN + 68, &msg.Byte_Reserved, 1);

	//ext_sol_state
	char solState = ExtractSolState(msg);
	memcpy(m_BestPosBuffer + HEADER_LEN + 69, &solState, 1);

	//Byte_Reserved1
	memcpy(m_BestPosBuffer + HEADER_LEN + 70, &msg.Byte_Reserved1, 1);

	//sig_mask
	char sigMask = ExtractSigMask(msg);
	memcpy(m_BestPosBuffer + HEADER_LEN + 71, &sigMask, 1);

	//calculate CRC and insert it to the struct
	msg.CRC = CalcBlockCRC32(sizeof(msg) - sizeof(int), (unsigned char*)m_BestPosBuffer);

	//CRC
	memcpy(m_BestPosBuffer + sizeof(msg) - sizeof(int), ((char*)&msg.CRC), sizeof(unsigned int));
}

void DgpsControl::FillDefaultHeader(HEADER_STRUCT& HEADER, E_MESSAGE_ID_INPUT_DGPS_DLV3 msgID, int sizeOfMsg) const{
	HEADER.Sync = 170;
	HEADER.Sync1 = 68;
	HEADER.Sync2 = 18;
	HEADER.Header_Lgth = HEADER_LEN;
	HEADER.Message_ID = msgID;

	HEADER.Message_Type = 0;
	HEADER.Message_Type |= 1 << 0;
	HEADER.Message_Type |= 1 << 6;

	HEADER.Port_Address = 64;														//? - COM2
	HEADER.Message_Length = sizeOfMsg - HEADER.Header_Lgth - sizeof(unsigned int);
	HEADER.Sequence = 0;
	HEADER.Idle_Time = 61;															// percentage of time that the processor is idle
	HEADER.Time_Status = E_GPS_TIME_STATUS::E_GPS_TIME_STATUS_FINE;					//
	HEADER.Week = (time(NULL) - 315964800) / (7*24*60*60);							// computer time, not UTM (the real GPS time is UTM).
	HEADER.ms = ((time(NULL) - 315964800) % (7*24*60*60)) * 1000; 					// milliseconds
	HEADER.Receiver_Status = 0;														// flags
	HEADER.Receiver_SW_Version = 1;													//
}

void DgpsControl::FillHeaderInBuffer(HEADER_STRUCT HEADER, char* buffer) const{
	//sync
	memcpy(buffer, &HEADER.Sync, 1);
	memcpy(buffer+1, &HEADER.Sync1, 1);
	memcpy(buffer+2, &HEADER.Sync2, 1);

	//Header
	unsigned char ucTemp = HEADER_LEN;
	memcpy(buffer+3, &ucTemp, 1);

	//Message_ID
	unsigned short tShort = HEADER.Message_ID;
	memcpy(buffer+4, &tShort, 2);

	//Message_Type
	memcpy(buffer+6, &HEADER.Message_Type, 1);

	//Port_Address
	memcpy(buffer+7, &HEADER.Port_Address, 1);

	//Message_Length
	ucTemp = HEADER.Message_Length;
	memcpy(buffer+8, &ucTemp, 1);

	//Sequence
	memcpy(buffer+10, &HEADER.Sequence, 2);

	//Idle_Time
	memcpy(buffer+12, &HEADER.Idle_Time, 1);

	//Time_Status
	memcpy(buffer+13, &HEADER.Time_Status, 1);

	//Week
	memcpy(buffer+14, &HEADER.Week, 2);

	//ms
	memcpy(buffer+16, &HEADER.ms, 4);

	//Receiver_Status
	memcpy(buffer+20, &HEADER.Receiver_Status, 4);

	//Reserved
	bzero(buffer+24, 2);

	//Receiver_SW_Version
	memcpy(buffer+26, &HEADER.Receiver_SW_Version, 2);
}

char DgpsControl::ExtractSolState(const PHS_BESTPOS& msg) const{
	char solState;
	bzero(&solState, 1);
	solState |= msg.ext_sol_state.Bit_AdVance_RTK_Verified << 0;
	solState |= msg.ext_sol_state.BITS_Pseudorange_lono_Correction << 1;
	solState |= msg.ext_sol_state.BIT_Antena_Status << 5;
	return solState;
}

char DgpsControl::ExtractSigMask(const PHS_BESTPOS& msg) const{
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

unsigned int DgpsControl::CRC32Value(int i) const{
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
    
unsigned int DgpsControl::CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const{
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
