#ifndef IDAN_CONTROL
#define IDAN_CONTROL

/*
* IdanControl.h
* Manage communication between Idan sensor
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include <string>
#include <vector>
#include <boost/thread.hpp> // boost::thread
#include "IICD.h"
#include "IdanData.h"

class ICommunication; // forward declaration
class IdanConfig; // forward declaration
class IdanMessageGet;
class IdanMessageSend;

class IdanControl : public IICD<IdanData> {
private:
    std::vector<IdanMessageGet*> m_getMessages;
    std::vector<IdanMessageSend*> m_sendMessages;
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    IdanConfig* m_idanConf = nullptr;
    //inner data
    IdanData m_data;
    // holds thread method of send data
    boost::thread m_getDataThread;
    mutable boost::mutex m_idanData_mutex;
    std::vector<std::shared_ptr<boost::thread> > m_messagesThreads;

    void GetThreadMethod();

    void SendThreadMethod(IdanMessageSend* message);

    IdanMessageGet* GetMsgByID(const char* buffer);

public:
    IdanControl(const std::string& confFilePath);

    virtual ~IdanControl();

    /**
     * @param data - IdanData object
     */ 
    virtual void SetData(const IdanData& data) override;

    /**
     * 
     */ 
    virtual IdanData GetData() override;

    /**
     * Run send data thread
     */ 
    virtual void Run() override;

};

#endif // IDAN_CONTROL