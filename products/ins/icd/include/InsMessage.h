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
static const int TIME_MULTIPLY = std::pow(2, 12) * std::pow(10, -6);
static const int VEL_MULTIPLY = std::pow(2, 8);

class InsData;

class InsMessage {
protected:
	int m_sleepTimeBetweenEverySend;
	char m_buffer[BUFFER_SIZE]{0};

	virtual void FillHeader(/* out */ INS_HEADER& header) const = 0;

public:
	InsMessage(int sleepTimeBetweenEverySend);
	virtual ~InsMessage() = default;

	int GetSleepTimeBetweenEverySend() const {
		return m_sleepTimeBetweenEverySend;
	}

	virtual void FillMessage(const InsData& data) = 0;


	void GetDataValidityBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemStatusBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemAlertBitfield(char* buffer, size_t bufferSize) const;

};

#endif // INSMESSAGE_H