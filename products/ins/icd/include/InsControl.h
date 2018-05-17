#ifndef INSCONTROL_H
#define INSCONTROL_H

/*
* InsControl.h
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "IICD.h"
#include "InsData.h"
#include <vector>

// forward declarations
class InsMessage;
class InsConfig; 
class ICommunication;

class InsControl : public IICD<InsData> {
private:
	typedef std::pair<InsMessage*, ICommunication*> t_message;

	// holds the ICD messages
	std::vector<t_message> m_messages;
	// configuration of INS
	InsConfig* m_insConf = nullptr;

	bool m_initialized = false;

	void InitializeMessages();

	t_message GetMsgByType(InsMsgType msgType) const;

public:
	InsControl(const std::string& confFilePath);

	~InsControl();

	virtual void SendData(const InsData& data) override;

    virtual InsData ReceiveData() override;
};

#endif