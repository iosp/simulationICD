#ifndef DGPSWRAPPER_H
#define DGPSWRAPPER_H

/*
* DgpsWrapper.h
* Wrapper for DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsData.h"
#include "IWrapper.h"

/**

 * */
class DgpsWrapper : public IWrapper<DgpsData> {
private:
    DgpsData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    DgpsWrapper(const std::string& confFilePath);

    ~DgpsWrapper();

    /**
     * Take the temporary data and set it to vlp
     */ 
    virtual void SendData() override;

    void SetPosition(double latitude, double longitude, double altitude);

    void SetVelocities(double latSpeed, double longSpeed, double altSpeed);

    void SetTimeStamp(float timeStamp);

    void SetMsgType(DgpsMsgType msgType);

    virtual void ReceiveData() override {}
};

#endif // DGPSWRAPPER_H