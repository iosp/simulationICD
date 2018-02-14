#ifndef INSCONTROL_H
#define INSCONTROL_H

/*
* InsControl.h
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include <boost/bind.hpp>
#include <boost/thread.hpp> // boost::thread
#include "IICD.h"
#include "InsData.h"
// #include "InsStructs.h"

class InsConfig;
class InsMessage; // forward declaration

class InsControl : public IICD<InsData>
{
private:
	InsConfig* m_insConf;
	InsData m_data;

	// holds thread method of send data
    boost::thread m_sendDataThread;
    mutable boost::mutex m_insData_mutex;

	void SendThreadMethod(InsMessage* message);

public:
	InsControl(const std::string& confFilePath);

	~InsControl();

	virtual void SetData(const InsData& data) override;

    virtual InsData* GetData() override;

    virtual void Run() override;
};
#endif