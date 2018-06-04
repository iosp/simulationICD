#ifndef TILTANMESSAGE_H
#define TILTANMESSAGE_H

/*
* TiltanMessage.h
* Tiltan message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/


#include "TiltanStructs.h"
#include "Message.h"
#include <stdio.h> // size_t
#include <cmath> // pow

static const int TIME_MULTIPLY = std::pow(2, 12);
static const int VEL_MULTIPLY = std::pow(2, 8);

// forward declarations
class TiltanData;
enum TiltanMsgType : unsigned int; // forward declaration of enum must specify underlying type (c++0x)

class TiltanMessage : public Message<TiltanData>{
protected:

	virtual void FillHeader(/* out */ TILTAN_HEADER& header) const = 0;

	void GetDataValidityBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemStatusBitfield(char* buffer, size_t bufferSize) const;

	void GetSystemAlertBitfield(char* buffer, size_t bufferSize) const;

public:
	TiltanMessage() = default;

	virtual ~TiltanMessage() = default;

	virtual void FillMessage(const TiltanData& data) = 0;

	virtual TiltanMsgType GetMsgType() const = 0;
};

#endif // TILTANMESSAGE_H