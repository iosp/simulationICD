#ifndef VLP_COMMUNICATION
#define VLP_COMMUNICATION

/*
* VLPControl.h
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
* VLP = Velodyne Lidar Puck
*/

#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::time_duration
#include <boost/thread.hpp> // boost::thread, mutex
#include "IICD.h"
#include "VelodyneData.h"

class ICommunication; // forward declaration
class VLPConfig; // forward declaration
class VLPMessage;

class VLPControl : public IICD<VelodyneData> {
protected:
    /**
     * connection protocol to use 
    */
    ICommunication* m_comm = nullptr;
    /**
     * VLP configuration values
     */ 
    VLPConfig* m_vlpConf = nullptr;

    VLPMessage* m_message = nullptr;
    /**
     * velodyne data to save on process  
    */
    std::vector<VelodyneData> m_velodyneData;
    /**
     * thread of data send
     */ 
    boost::thread m_sendDataThread;
    /**
     * mutex to save velodyne data
     */ 
    mutable boost::mutex m_velodyneDataMutex;
    
    /**
     * Send data via UDP socket
     */
    void SendThreadMethod();

    /**
     * Initialize inner velodyne data 
     */
    void InitVelodyneData();
    
    /**
     * Check validation of VLP data
     * @param data - VLP data struct
     * @param numOfRowsInColumn - number of rows expected in every column
     * @return true if data is valid and false otherwise
    */
    bool CheckDataValidation(const VelodyneData& data) const;

    /**
     * Check if the last duration enables us to add the next element to the packet
     * @param lastDuration - last duration that inserted
     * @param dataIndex - the index on velodyne data vector to get the data from
     * @return true if the next element can be added and false O.W
    */
    bool CanAddToPacket(float lastDuration, int dataIndex) const;

    /**
     * Check if the velodyne data in specific index is all zero values
     * @param dataIndex - the index on velodyne data vector to get the data from
     * @return true if the data is zeroed and false O.W
    */
    bool IsDataZeroed(int dataIndex) const;

    /**
     * Fill Message on packet message
     * @param dataIndex - the index on velodyne data vector to get the data from
    */
    void FillMessage(int dataIndex);

    /**
     * Print vector of veclodyne data. for debug only
     */ 
    void printVelData() const;

public:

    VLPControl(const std::string& confFilePath);

    virtual ~VLPControl();

    /**
     * Set data on inner velodyne data vector
     * @param data - VelodyneData object
     */ 
    virtual void SetData(const VelodyneData& data) override;

    /**
     * This function is implemented with nullptr return
     */ 
    virtual VelodyneData GetData() override;

    /**
     * Run VLP send data thread
     */ 
    virtual void Run() override;
};



#endif // VLP_COMMUNICATION