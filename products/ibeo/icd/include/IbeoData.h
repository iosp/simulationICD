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

    int m_numOfPoints;
    std::vector<double> m_rangesB1;
    std::vector<double> m_rangesB2;
    std::vector<double> m_rangesT1;
    std::vector<double> m_rangesT2;
    float m_simTime;

public:
    IbeoData() = default;
    
    ~IbeoData() = default;

    int GetNumOfPoints() const {
        return m_numOfPoints;
    }

    const std::vector<double>& GetRangeB1() const {
        return m_rangesB1;
    }

    const std::vector<double>& GetRangeB2() const {
        return m_rangesB2;
    }

    const std::vector<double>& GetRangeT1() const {
        return m_rangesT1;
    }

    const std::vector<double>& GetRangeT2() const {
        return m_rangesT2;
    }

    float GetSimTime() const {
        return m_simTime;
    }

    std::string toString() const;
};



#endif // IBEO_DATA_H