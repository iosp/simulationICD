#ifndef IBEO_MESSAGE_H
#define IBEO_MESSAGE_H

/*
* IbeoMessage.h
* Ibeo message to send
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "Message.h"
#include "IbeoData.h"
#include "IbeoStructs.h"

class IbeoMessage : public Message<IbeoData>{
private:
	int m_pointCounter = 0;

	double m_tStartAngle;
	double m_tEndAngle;
	double m_bStartAngle;
	double m_bEndAngle;
	double m_angleIncrement;

	void FillPoints(SibeoScanData& msg, unsigned char layerEcho,  double startAngle, const std::vector<double>& ranges);

public:
	IbeoMessage(double tStartAngle, double tEndAngle, double bStartAngle, double bEndAngle, double angleIncrement);

	virtual ~IbeoMessage() = default;

	virtual void FillMessage(const IbeoData& data) override;

	virtual int GetMessageSize() const override;
};

#endif // IBEO_MESSAGE_H