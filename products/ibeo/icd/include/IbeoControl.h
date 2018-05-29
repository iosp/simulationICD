#ifndef IBEO_CONTROL
#define IBEO_CONTROL

/*
* IbeoControl.h
* 
* Author: Binyamin Appelbaum
* Date: 22.04.18
*/

#include "IICD.h"
#include <string>

class ICommunication;
class IbeoConfig;
class IbeoData;

class IbeoControl : public IICD<IbeoData> {
private:
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    IbeoConfig* m_ibeoConf = nullptr;
	
	virtual void InitCommunication() override;

public:
	IbeoControl(const std::string& confFilePath);
	virtual ~IbeoControl();
	
	/**
	 * @param data - IdanData object
	 */ 
	virtual void SendData(const IbeoData& data) override;

	/**
	 * 
	 */ 
	virtual IbeoData ReceiveData() override;
};

#endif // IBEO_CONTROL
