#ifndef NOVATELMESSAGE_H
#define NOVATELMESSAGE_H

/*
* NovatelMessage.h
* NOVATEL message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "NovatelStructs.h"
#include "Message.h"

static const int HEADER_LEN = 28;

class NovatelData;
class ICommunication; // forward declaration

class NovatelMessage : public Message<NovatelData>{
protected:

	virtual void FillHeader(/* out */ NOVATEL_HEADER& header) const;

	virtual void FillHeaderInBuffer(const NOVATEL_HEADER& header);

    unsigned int CRC32Value(int i) const;

    unsigned int CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const;

	virtual E_MESSAGE_ID_INPUT_NOVATEL_DLV3 GetMessageID() const = 0;

public:
	NovatelMessage() = default;

	virtual ~NovatelMessage() = default;
};

#endif // NOVATELMESSAGE_H