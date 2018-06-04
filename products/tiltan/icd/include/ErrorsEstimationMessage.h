#ifndef ERRORSESTIMATIONMESSAGE_H
#define ERRORSESTIMATIONMESSAGE_H

/*
* ErrorsEstimationMessage.h
* Tiltan errors estimation message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "TiltanMessage.h"

class ErrorsEstimationMessage : public TiltanMessage {
protected:

	virtual void FillHeader(/* out */ TILTAN_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	ErrorsEstimationMessage() = default;

	virtual ~ErrorsEstimationMessage() = default;

	virtual void FillMessage(const TiltanData& data) override;

	virtual TiltanMsgType GetMsgType() const override;
};

#endif // ERRORSESTIMATIONMESSAGE_H