#ifndef INSWRAPPER_H
#define INSWRAPPER_H

/*
* InsWrapper.h
* Wrapper for INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "InsData.h"
#include "IWrapper.h"

/**

 * */
class InsWrapper : public IWrapper<InsData> {
private:
    InsData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    InsWrapper(const std::string& confFilePath);

    ~InsWrapper();
    
    /**
     * Take the temporary data and set it to icd
     */ 
    virtual void SendData() override;

    void SetTimeStamps(float simTime, float utcTime);

    // INS navigation data message
    void SetPose(float latitude, float longitude, float altitude);

    void SetOrientation(float azimuth, float pitch, float roll);

    void SetAzimuthRate(float azimuthRate);

    void SetVelocity(float northVelocity, float eastVelocity, float downVelocity);

    void SetDistances(float distanceTraveled, float odometerDistance);

    void SetMotionDetected(bool motionDetected);

    // INS internal GPS
    void SetInternalGpsFields(short gpsFom, short numOfSatelites);

    // INS Errors estimation message
    void SetDirectionErrors(float horizontalError, float verticalError, float northingError, float eastingError, float altitudeError);

    void SetVelocityErrors(float northVelocityError, float eastVelocityError, float downVelocityError);

    void SetOrientationErrors(float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);

    void SetMsgType(InsMsgType msgType);

    virtual void ReceiveData() override {}

};

#endif // INSWRAPPER_H