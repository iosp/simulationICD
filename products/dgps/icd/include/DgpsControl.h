#ifndef DGPS_CONTROL
#define DGPS_CONTROL

/*
* DgpsControl.h
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include <string>
#include <boost/thread.hpp> // boost::thread
#include <boost/lockfree/queue.hpp>
#include "IICD.h"
#include "DgpsData.h"
#include "DgpsStructs.h"

static const int BUFFER_SIZE = 1000;

class ICommunication; // forward declaration
class DgpsConfig; // forward declaration

class DgpsControl : public IICD<DgpsData> {
private:
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    DgpsConfig* m_dgpsConf = nullptr;
    // time to sleep between every packet send
    int m_sleepTimeBetweenEverySend;
    // holds thread method of send data
    boost::thread m_sendDataThread;
    mutable boost::mutex m_dgpsData_mutex;
    
    // Data
    char m_BestVelBuffer[BUFFER_SIZE]{};
    char m_BestPosBuffer[BUFFER_SIZE]{}; // TODO separate messages from this class
    boost::lockfree::queue<DgpsData, boost::lockfree::capacity<1> > m_dgpsDataCollection;

    void SendThreadMethod();

    void SendBestVelData(const DgpsData& data);

    void SendBestPosData(const DgpsData& data);

    void SendBuffer(const char* buffer, int sizeOfData) const;

    void FillBestVel(const DgpsData& data);

    void FillBestPos(const DgpsData& data);

    void FillDefaultHeader(HEADER_STRUCT& HEADER, E_MESSAGE_ID_INPUT_DGPS_DLV3 msgID, int sizeOfMsg) const;

    void FillHeaderInBuffer(HEADER_STRUCT HEADER, char* buffer) const;

    char ExtractSolState(const PHS_BESTPOS& msg) const;

    char ExtractSigMask(const PHS_BESTPOS& msg) const;

    unsigned int CRC32Value(int i) const;

    unsigned int CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const;

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
    virtual DgpsData* GetData() override;

    /**
     * Run send data thread
     */ 
    virtual void Run() override;

};

#endif // DGPS_CONTROL