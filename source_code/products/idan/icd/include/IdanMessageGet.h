#ifndef IDANMESSAGEGET_H
#define IDANMESSAGEGET_H

/*
* IdanMessageGet.h
* IDAN message to get
* Author: Binyamin Appelbaum
* Date: 27.03.18
*/

#include "IdanMessage.h"

static const int CAN_REG_DATA_OFFSET = 8;
static const int CAN_VIEW_DATA_OFFSET = 5;
static const unsigned char SHUTDOWN_VAL = 0x0A;
static const unsigned char EMERGENCY_VAL = 0x0C;

class IdanMessageGet : public IdanMessage {
private:
	int m_sleepTimeBetweenEverySend;
public:
	IdanMessageGet(float hertz);

	virtual ~IdanMessageGet() = default;

	virtual int GetMessageSize() const override {return 0;}

	virtual void FillMessage(const IdanData& data) override {}

	virtual int SendMessage(ICommunication* comm) const override {return 0;}

	virtual void ParseMessage(const char* buffer) = 0;

	virtual void UpdateData(IdanData& data) const = 0;

	int GetSleepTimeBetweenEverySend() const {
		return m_sleepTimeBetweenEverySend;
	}
};

#endif // IDANMESSAGEGET_H