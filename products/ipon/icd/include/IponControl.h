#ifndef IPON_CONTROL
#define IPON_CONTROL

/*
* IponControl.h
* 
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include <string>
#include <boost/thread.hpp> // boost::thread
#include "IponStructs.h"
#include "IICD.h"
#include "IponData.h"

class ICommunication;
class IponConfig;
class IponMessage;

class IponControl : public IICD<IponData> {
private:
    typedef std::pair<IponMessage*, ICommunication*> t_message;
    // configuration parser
    IponConfig* m_iponConf = nullptr;

	IponMessage* m_message = nullptr;
    //inner data
    IponData m_data;
    // holds thread method of send data
	std::vector<t_message> m_messages;
	std::vector<std::shared_ptr<boost::thread> > m_messagesThreads;
    mutable boost::mutex m_IponData_mutex;

    void SendThreadMethod(const t_message& message);

public:
	IponControl(const std::string& confFilePath);
	virtual ~IponControl();
	
	/**
	 * @param data - IponData object
	 */ 
	virtual void SetData(const IponData& data) override;

	virtual IponData GetData() override;

	/**
	 * Run send data thread
	 */ 
	virtual void Run() override;
};

#endif // IPON_CONTROL
