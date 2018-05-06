#ifndef IBEO_DATA_H
#define IBEO_DATA_H

/*
* IbeoData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include <string>
#include <vector>

class IbeoData {
private:

    int m_numOfPoints = 0;
    std::vector<double> m_rangeB1;
    std::vector<double> m_rangeB2;
    std::vector<double> m_rangeT1;
    std::vector<double> m_rangeT2;
    float m_simTime = 0;

public:
    IbeoData() = default;
    
    ~IbeoData() = default;

    int GetNumOfPoints() const {
        return m_numOfPoints;
    }

    void SetNumOfPoints(int numOfPoints) {
        m_numOfPoints = numOfPoints;
    }

    const std::vector<double>& GetRangeB1() const {
        return m_rangeB1;
    }

    void SetRangeB1(const std::vector<double>& range) {
        m_rangeB1 = range;
    }

    const std::vector<double>& GetRangeB2() const {
        return m_rangeB2;
    }

    void SetRangeB2(const std::vector<double>& range) {
        m_rangeB2 = range;
    }

    const std::vector<double>& GetRangeT1() const {
        return m_rangeT1;
    }

    void SetRangeT1(const std::vector<double>& range) {
        m_rangeT1 = range;
    }

    const std::vector<double>& GetRangeT2() const {
        return m_rangeT2;
    }

    void SetRangeT2(const std::vector<double>& range) {
        m_rangeT2 = range;
    }

    float GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(float simTime) {
        m_simTime = simTime;
    }

    std::string toString() const;
};



#endif // IBEO_DATA_H