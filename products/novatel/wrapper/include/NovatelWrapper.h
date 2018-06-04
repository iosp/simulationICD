#ifndef NOVATELWRAPPER_H
#define NOVATELWRAPPER_H

/*
* NovatelWrapper.h
* Wrapper for Novatel
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "NovatelData.h"
#include "IWrapper.h"

/**

 * */
class NovatelWrapper : public IWrapper<NovatelData> {
private:
    NovatelData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    NovatelWrapper(const std::string& confFilePath);

    ~NovatelWrapper();

    /**
     * Take the temporary data and set it to vlp
     */ 
    virtual void SendData() override;

    void SetPosition(double latitude, double longitude, double altitude);

    void SetVelocities(double latSpeed, double longSpeed, double altSpeed);

    void SetTimeStamp(float timeStamp);

    void SetMsgType(NovatelMsgType msgType);

    virtual void ReceiveData() override {}
};

#endif // NOVATELWRAPPER_H