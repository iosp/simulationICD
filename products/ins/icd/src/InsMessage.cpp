/*m_buffer
* InsMessage.cpp
* Ins message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"
#include "InsStructs.h"
#include "ICommunication.h"
#include "LoggerProxy.h"

InsMessage::InsMessage(int hertz) {
	if (hertz == 0) {
		ERRLOG << "Invalid hertz argument for INS message\n";
		return;
	}
	m_sleepTimeBetweenEverySend = 1e6 / hertz;
}

void InsMessage::GetDataValidityBitfield(char* buffer, size_t bufferSize) const {
	static const char D1 =	1 << 7 | // position validity
							1 << 6 | // azimuth validity
							1 << 5 | // pitch/roll validity
							0 << 4 | // hull azimuth validity - always not valid
							1 << 3 | // velocity validity
							1 << 2 | // angular rate validity - NOT IN USE!
							1 << 1 | // Acceleration validity - NOT IN USE!
							1 << 0;  // UTC time validity - NOT IN USE!

	static const char D2 =	1 << 7 | // IPPS Validity - NOT IN USE!
							1 << 6 | // odo distance validity
							1 << 5 | // GPS solution validity
							1 << 4 | // motion detected validity - NOT IN USE!
							0 << 3 | // spare
							0 << 2 | // spare
							0 << 1 | // spare
							0 << 0;  // spare

	snprintf(buffer, bufferSize, "%c%c", D1, D2);
}

void InsMessage::GetSystemStatusBitfield(char* buffer, size_t bufferSize) const {
	static const unsigned char S3 = 0, S5 = 0, S6 = 0, S7 = 0, S8 = 0;

	static const char  S1 =	1 << 7 | // initialization mode
							1 << 6 | // initialization complete
							0 << 5 | // align mode
							1 << 4 | // survey mode
							0 << 3 | // spare
							0 << 2 | // azimuth update request
							0 << 1 | // position update request
							0 << 0;  // ready for align on the move mode

	static const char S2 =	0 << 7 | // zero-velocity update in progress
							1 << 6 | // GPS data valid
							0 << 5 | // less than 4 satelites
							0 << 4 | // reserved
							0 << 3 | // reserved
							0 << 2 | // SH align mode
							0 << 1 | // ADNAV alert
							0 << 0;  // align on the move mode

	static const char S4 =	0 << 7 | // GPS alone
							1 << 6 | // integrated mode
							0 << 5 | // reserved
							0 << 4 | // reserved
							0 << 3 | // reserved
							0 << 2 | // restart required mode
							0 << 1 | // GPS is unavailable for AOM
							0 << 0;  // stanby mode
	
	snprintf(buffer, bufferSize, "%c%c%c%c%c%c%c%c", S1, S2, S3, S4, S5, S6, S7, S8);
}

void InsMessage::GetSystemAlertBitfield(char* buffer, size_t bufferSize) const {
	static const unsigned char A1 = 0, A2 = 0, A3 = 0, A4 = 0, A5 = 0, A6 = 0, A7 = 0, A8 = 0, A9 = 0, A10 = 0;

	snprintf(buffer, bufferSize, "%c%c%c%c%c%c%c%c%c%c", A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
}

void InsMessage::SendMessage(ICommunication* comm) const {
	comm->SendData(m_buffer, GetMessageSize());
}