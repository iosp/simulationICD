#ifndef INSMESSAGE_H
#define INSMESSAGE_H

/*
* InsMessage.h
* Ins message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/


#include "InsStructs.h"
#include "Message.h"
#include <stdio.h> // size_t
#include <cmath> // pow

static const int TIME_MULTIPLY = std::pow(2, 12);
static const int VEL_MULTIPLY = std::pow(2, 8);

// forward declarations
class InsData;
enum InsMsgType : unsigned int; // forward declaration of enum must specify underlying type (c++0x)
class ICommunication; 

class InsMessage : public Message<InsData>{
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const = 0;

	void GetDataValidityBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemStatusBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemAlertBitfield(char* buffer, size_t bufferSize) const;

public:
	InsMessage() = default;

	virtual ~InsMessage() = default;

	virtual void FillMessage(const InsData& data) = 0;

	virtual InsMsgType GetMsgType() const = 0;
};

#endif // INSMESSAGE_H