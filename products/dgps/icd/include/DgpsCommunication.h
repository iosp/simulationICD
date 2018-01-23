#ifndef DGPS_COMMUNICATION
#define DGPS_COMMUNICATION

/*
* DgpsCommunication.h
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include <string>
#include <boost/thread.hpp> // boost::thread
#include <boost/lockfree/queue.hpp>
#include <termios.h>
#include "IICD.h"
#include "DgpsData.h"
#include "DgpsStructs.h"

 
class DgpsCommunication : public IICD<DgpsData> {
private:

    int SendData(char* buffer, int sizeOfData) const;

    void SendThreadMethod();

    void SendBestVelData(const DgpsData& data);

    void SendBestPosData(const DgpsData& data);

    void SendBuffer(char* buffer, size_t sizeOfBuffer) const;

    void FillBestVel(const DgpsData& data);

    void FillBestPos(const DgpsData& data);

    void FillDefaultHeader(HEADER_STRUCT& HEADER, E_MESSAGE_ID_INPUT_DGPS_DLV3 msgID, int sizeOfMsg) const;

    void FillHeaderInBuffer(HEADER_STRUCT HEADER, char* buffer) const;

    char ExtractSolState(const PHS_BESTPOS& msg) const;

    char ExtractSigMask(const PHS_BESTPOS& msg) const;

    bool InitRS232Connection();

    unsigned int CRC32Value(int i) const;

    unsigned int CalcBlockCRC32(unsigned int ulCount, unsigned char* data) const;

    //RS interface
    int m_cport;
    struct termios m_newPortSettings, m_oldPortSettings;

    /**
     * time to sleep between every packet send
    */
    int m_sleepTimeBetweenEverySend;
    boost::thread m_sendDataThread;
    mutable boost::mutex m_dgpsData_mutex;
    
    //RS Data
    char m_BestVelBuffer[1000]{};
    char m_BestPosBuffer[1000]{};
    boost::lockfree::queue<DgpsData> m_dgpsDataCollection;

public:
    DgpsCommunication();

    virtual ~DgpsCommunication() = default;

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

#endif // DGPS_COMMUNICATION