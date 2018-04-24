#ifndef DGPSMESSAGE_H
#define DGPSMESSAGE_H

/*
* DgpsMessage.h
* DGPS message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "DgpsStructs.h"
#include "IMessage.h"

static const int HEADER_LEN = 28;

class DgpsData;
class ICommunication; // forward declaration

class DgpsMessage : public IMessage<DgpsData>{
protected:

	virtual void FillHeader(/* out */ DGPS_HEADER& header) const;

	virtual void FillHeaderInBuffer(const DGPS_HEADER& header);

    unsigned int CRC32Value(int i) const;

    unsigned int CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const;

	virtual E_MESSAGE_ID_INPUT_DGPS_DLV3 GetMessageID() const = 0;

public:
	DgpsMessage(float hertz);

	virtual ~DgpsMessage() = default;

	virtual void FillMessage(const DgpsData& data) = 0;

	virtual int SendMessage(ICommunication* comm) const override;
};

#endif // DGPSMESSAGE_H