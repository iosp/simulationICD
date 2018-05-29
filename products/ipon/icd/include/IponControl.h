#ifndef IPON_CONTROL
#define IPON_CONTROL

/*
* IponControl.h
* 
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "IponStructs.h"
#include "IICD.h"
#include "IponData.h"
#include <vector>

class ICommunication;
class IponConfig;
class IponMessage;

class IponControl : public IICD<IponData> {
private:
    typedef std::pair<IponMessage*, ICommunication*> t_message;
	// holds the ICD messages
	std::vector<t_message> m_messages;
    // configuration parser
    IponConfig* m_iponConf = nullptr;

	t_message GetMsgByType(IponMsgType msgType) const;

public:
	IponControl(const std::string& confFilePath);
	virtual ~IponControl();
	
	/**
	 * @param data - IponData object
	 */ 
	virtual void SendData(const IponData& data) override;

	virtual IponData ReceiveData() override;

	virtual void InitCommunication() override;
};

#endif // IPON_CONTROL
