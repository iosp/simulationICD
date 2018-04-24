#ifndef IBEO_CONTROL
#define IBEO_CONTROL

/*
* IbeoControl.h
* 
* Author: Binyamin Appelbaum
* Date: 22.04.18
*/

#include <string>
#include <boost/thread.hpp> // boost::thread
#include "IbeoStructs.h"
#include "IICD.h"
#include "IbeoData.h"

class ICommunication;
class IbeoConfig;
class IbeoMessage;

class IbeoControl : public IICD<IbeoData> {
private:
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    IbeoConfig* m_ibeoConf = nullptr;

	IbeoMessage* m_message = nullptr;
    //inner data
    IbeoData m_data;
    // holds thread method of send data
    boost::thread m_sendDataThread;
    mutable boost::mutex m_ibeoData_mutex;

    void SendThreadMethod();

public:
	IbeoControl(const std::string& confFilePath);
	virtual ~IbeoControl();
	/**
	 * @param data - IdanData object
	 */ 
	virtual void SetData(const IbeoData& data) override;

	/**
	 * 
	 */ 
	virtual IbeoData GetData() override;

	/**
	 * Run send data thread
	 */ 
	virtual void Run() override;
};

#endif // IBEO_CONTROL
