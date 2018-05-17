#ifndef IBEOWRAPPER_H
#define IBEOWRAPPER_H

/*
* IbeoWrapper.h
* Wrapper for DGPS
* Author: Binyamin Appelbaum
* Date: 24.04.18
*/

#include "IbeoData.h"
#include "IWrapper.h"

/**

 * */
class IbeoWrapper : public IWrapper<IbeoData> {
private:
    IbeoData m_data;

    std::vector<double> m_currRangeB1;
    std::vector<double> m_currRangeB2;
    std::vector<double> m_currRangeT1;
    std::vector<double> m_currRangeT2;
    float m_simTime;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    IbeoWrapper(const std::string& confFilePath);

    ~IbeoWrapper();

    /**
     * Take the temporary data and set it to icd
     */ 
    virtual void SendData() override;

    void SetNumOfPoints(int numOfPoints);

    void SetRangePointB1(double point);

    void SetRangePointB2(double point);

    void SetRangePointT1(double point);

    void SetRangePointT2(double point);

    void SetTimeStamp(float timeStamp);

    virtual void ReceiveData() override {}
};

#endif // IBEOWRAPPER_H