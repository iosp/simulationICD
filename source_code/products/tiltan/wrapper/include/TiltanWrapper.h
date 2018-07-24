#ifndef TILTANWRAPPER_H
#define TILTANWRAPPER_H

/*
* TiltanWrapper.h
* Wrapper for Tiltan
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "TiltanData.h"
#include "IWrapper.h"

/**

 * */
class TiltanWrapper : public IWrapper<TiltanData> {
private:
    TiltanData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    TiltanWrapper(const std::string& confFilePath);

    ~TiltanWrapper();
    
    /**
     * Take the temporary data and set it to icd
     */ 
    virtual void SendData() override;

    void SetTimeStamps(float simTime, float utcTime);

    // Tiltan navigation data message
    void SetPose(float latitude, float longitude, float altitude);

    void SetOrientation(float azimuth, float pitch, float roll);

    void SetAzimuthRate(float azimuthRate);

    void SetVelocity(float northVelocity, float eastVelocity, float downVelocity);

    void SetDistances(float distanceTraveled, float odometerDistance);

    void SetMotionDetected(bool motionDetected);

    // Tiltan internal GPS
    void SetInternalGpsFields(short gpsFom, short numOfSatelites);

    // Tiltan Errors estimation message
    void SetDirectionErrors(float horizontalError, float verticalError, float northingError, float eastingError, float altitudeError);

    void SetVelocityErrors(float northVelocityError, float eastVelocityError, float downVelocityError);

    void SetOrientationErrors(float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);

    void SetMsgType(TiltanMsgType msgType);

    virtual void ReceiveData() override {}

};

#endif // TILTANWRAPPER_H