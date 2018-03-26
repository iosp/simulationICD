#ifndef DGPS_CONTROL
#define DGPS_CONTROL

/*
* DgpsControl.h
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include <string>
#include <vector>
#include <boost/thread.hpp> // boost::thread
#include <boost/lockfree/queue.hpp>
#include "IICD.h"
#include "DgpsData.h"
#include "IMessage.h"

class ICommunication; // forward declaration
class DgpsConfig; // forward declaration

class DgpsControl : public IICD<DgpsData> {
private:
    std::vector<IMessage<DgpsData> *> m_messages;
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    DgpsConfig* m_dgpsConf = nullptr;
    // holds thread method of send data
    boost::thread m_sendDataThread;
    mutable boost::mutex m_dgpsData_mutex;
    
    boost::lockfree::queue<DgpsData, boost::lockfree::capacity<1> > m_dgpsDataCollection;

    void SendThreadMethod();

    void SendMessage(IMessage<DgpsData>* message) const;

public:
    DgpsControl(const std::string& confFilePath);

    virtual ~DgpsControl();

    /**
     * Set data on Dgps
     * @param data - DgpsData object
     */ 
    virtual void SetData(const DgpsData& data) override;

    /**
     * This function is implemented with nullptr return
     */ 
    virtual DgpsData GetData() override;

    /**
     * Run send data thread
     */ 
    virtual void Run() override;

};

#endif // DGPS_CONTROL