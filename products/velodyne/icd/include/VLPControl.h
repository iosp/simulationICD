#ifndef VLP_COMMUNICATION
#define VLP_COMMUNICATION

/*
* VLPControl.h
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
* VLP = Velodyne Lidar Puck
*/

#include "IICD.h"
#include "VelodyneData.h"
#include <string>
#include <vector>

class ICommunication;
class VLPConfig; // forward declaration

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

    /**
     * Check validation of VLP data
     * @param data - VLP data struct
     * @param numOfRowsInColumn - number of rows expected in every column
     * @return true if data is valid and false otherwise
    */
    bool CheckDataValidation(const VelodyneData& data) const;
    
public:

    VLPControl(const std::string& confFilePath);

    virtual ~VLPControl();

    /**
     * Set data on inner velodyne data vector
     * @param data - VelodyneData object
     */ 
    virtual void SendData(const VelodyneData& data) override;

    /**
     * This function is implemented with nullptr return
     */ 
    virtual VelodyneData ReceiveData() override;
};



#endif // VLP_COMMUNICATION