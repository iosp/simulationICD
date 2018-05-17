#ifndef ERRORSESTIMATIONMESSAGE_H
#define ERRORSESTIMATIONMESSAGE_H

/*
* ErrorsEstimationMessage.h
* INS errors estimation message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"

class ErrorsEstimationMessage : public InsMessage {
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	ErrorsEstimationMessage() = default;

	virtual ~ErrorsEstimationMessage() = default;

	virtual void FillMessage(const InsData& data) override;

	virtual InsMsgType GetMsgType() const override;
};

#endif // ERRORSESTIMATIONMESSAGE_H