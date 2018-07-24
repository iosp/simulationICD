#ifndef VELODYNE_CONTROL
#define VELODYNE_CONTROL

/*
* VelodyneControl.h
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
* Velodyne = Velodyne Lidar Puck
*/

#include "IICD.h"
#include "VelodyneData.h"
#include <string>
#include <vector>

class ICommunication;
class VelodyneConfig; // forward declaration

class VelodyneControl : public IICD<VelodyneData> {
private:
    /**
     * connection protocol to use 
    */
    ICommunication* m_comm = nullptr;
    /**
     * Velodyne configuration values
     */ 
    VelodyneConfig* m_velodyneConf = nullptr;

    /**
     * Check validation of Velodyne data
     * @param data - Velodyne data struct
     * @param numOfRowsInColumn - number of rows expected in every column
     * @return true if data is valid and false otherwise
    */
    bool CheckDataValidation(const VelodyneData& data) const;

protected:
    virtual void InitCommunication() override;
    
public:

    VelodyneControl(const std::string& confFilePath);

    virtual ~VelodyneControl();

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



#endif // VELODYNE_CONTROL