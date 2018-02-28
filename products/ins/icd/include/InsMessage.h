#ifndef INSMESSAGE_H
#define INSMESSAGE_H

/*
* InsMessage.h
* Ins message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "stdio.h" // size_t
#include <cmath> // pow
#include "InsStructs.h"

static const int BUFFER_SIZE = 1000;
static const int TIME_MULTIPLY = std::pow(2, 12);
static const int VEL_MULTIPLY = std::pow(2, 8);

class InsData;
class ICommunication; // forward declaration

class InsMessage {
protected:

	int m_sleepTimeBetweenEverySend;

	char m_buffer[BUFFER_SIZE]{0};

	virtual void FillHeader(/* out */ INS_HEADER& header) const = 0;

	virtual int GetMessageSize() const = 0;

	void GetDataValidityBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemStatusBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemAlertBitfield(char* buffer, size_t bufferSize) const;

public:
	InsMessage(int hertz);

	virtual ~InsMessage() = default;

	int GetSleepTimeBetweenEverySend() const {
		return m_sleepTimeBetweenEverySend;
	}

	virtual void FillMessage(const InsData& data) = 0;

	virtual void SendMessage(ICommunication* comm) const;
};

#endif // INSMESSAGE_H