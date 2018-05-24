#ifndef TILTANCONTROL_H
#define TILTANCONTROL_H

/*
* TiltanControl.h
* Manage communication of Tiltan sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "IICD.h"
#include "TiltanData.h"
#include <vector>

// forward declarations
class TiltanMessage;
class TiltanConfig; 
class ICommunication;

class TiltanControl : public IICD<TiltanData> {
private:
	typedef std::pair<TiltanMessage*, ICommunication*> t_message;

	// holds the ICD messages
	std::vector<t_message> m_messages;
	// configuration of Tiltan
	TiltanConfig* m_tiltanConf = nullptr;

	bool m_initialized = false;

	void InitializeMessages();

	t_message GetMsgByType(TiltanMsgType msgType) const;

public:
	TiltanControl(const std::string& confFilePath);

	~TiltanControl();

	virtual void SendData(const TiltanData& data) override;

    virtual TiltanData ReceiveData() override;
};

#endif // TILTANCONTROL_H