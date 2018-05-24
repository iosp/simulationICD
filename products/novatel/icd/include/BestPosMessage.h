#ifndef BESTPOSMESSAGE_H
#define BESTPOSMESSAGE_H

/*
* BestPosMessage.h
* BestPos message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "NovatelMessage.h"

class BestPosMessage : public NovatelMessage {
private:

	char ExtractSolState(const PHS_BESTPOS& msg) const;

    char ExtractSigMask(const PHS_BESTPOS& msg) const;

protected:
	E_MESSAGE_ID_INPUT_NOVATEL_DLV3 GetMessageID() const override;

public:
	BestPosMessage() = default;

	virtual ~BestPosMessage() = default;

	virtual void FillMessage(const NovatelData& data) override;

	virtual int GetMessageSize() const override;
};

#endif // BESTPOSMESSAGE_H