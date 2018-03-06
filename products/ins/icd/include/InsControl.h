#ifndef INSCONTROL_H
#define INSCONTROL_H

/*
* InsControl.h
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

// #include <boost/bind.hpp>
#include <boost/thread.hpp> // boost::thread
#include "IICD.h"
#include "InsData.h"
#include "IMessage.h"

class InsConfig; // forward declaration
class ICommunication; // forward declaration

class InsControl : public IICD<InsData>
{
private:
	typedef std::pair<IMessage<InsData> *, ICommunication*> t_message;

	InsConfig* m_insConf = nullptr;
	InsData m_data;

	// holds thread method of send data
	std::vector<t_message> m_messages;
	std::vector<std::shared_ptr<boost::thread> > m_messagesThreads;
    mutable boost::mutex m_insData_mutex;

	void SendThreadMethod(const t_message& message);

public:
	InsControl(const std::string& confFilePath);

	~InsControl();

	virtual void SetData(const InsData& data) override;

    virtual InsData* GetData() override;

    virtual void Run() override;
};

#endif