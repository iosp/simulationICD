#ifndef DGPSCONFIG_H
#define DGPSCONFIG_H

/*
* DgpsConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 31.01.18
* 
*/

#include <string>

class DgpsConfig {
private:
    std::string m_portName;
    int m_baudRate;

public:
    DgpsConfig() = default;
    DgpsConfig(const std::string& portName, int baudRate);

    virtual ~DgpsConfig() = default;

    const std::string& GetPortName() const {
        return m_portName;
    }

    int GetBaudRate() const {
        return m_baudRate;
    }

    std::string toString() const;

};



#endif // DGPSCONFIG_H