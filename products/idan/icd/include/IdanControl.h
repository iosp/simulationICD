#ifndef IDAN_CONTROL
#define IDAN_CONTROL

/*
* IdanControl.h
* Manage communication between Idan sensor
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IICD.h"
#include "IdanData.h"
#include <vector>
#include <boost/thread.hpp> // boost::thread

// forward declarations
class ICommunication;
class IdanConfig;
class IdanMessageGet;
class IdanMessageSend;

class IdanControl : public IICD<IdanData> {
private:
    std::vector<IdanMessageGet*> m_getMessages;
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    IdanConfig* m_idanConf = nullptr;
    //inner data for Receive data
    IdanData m_data;
    // holds thread method of Receive data
    boost::thread m_getDataThread;
    mutable boost::mutex m_idanData_mutex;

    bool m_initialized = false;

    void GetThreadMethod();

    // called via constructor
    void InitGetMessages();

    IdanMessageGet* GetMsgByID(const char* buffer);
    
    IdanMessageSend* GetMsgByType(IdanMsgType msgType) const;

public:
    IdanControl(const std::string& confFilePath);

    virtual ~IdanControl();

    /**
     * @param data - IdanData object
     */ 
    virtual void SendData(const IdanData& data) override;

    virtual IdanData ReceiveData() override;
};

#endif // IDAN_CONTROL