#ifndef DGPS_CONTROL
#define DGPS_CONTROL

/*
* DgpsControl.h
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "IICD.h"
#include "DgpsData.h"

template <class T>
class Message;
class DgpsConfig;
class ICommunication;

class DgpsControl : public IICD<DgpsData> {
private:
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    DgpsConfig* m_dgpsConf = nullptr;

    bool m_initialized = false;

    void SendMessage(Message<DgpsData>* message) const;

    Message<DgpsData>* GetMsgByType(DgpsMsgType msgType) const;

public:
    DgpsControl(const std::string& confFilePath);

    virtual ~DgpsControl();

    /**
     * Set data on Dgps
     * @param data - DgpsData object
     */ 
    virtual void SendData(const DgpsData& data) override;

    /**
     * This function is implemented with empty return
     */ 
    virtual DgpsData ReceiveData() override;

};

#endif // DGPS_CONTROL