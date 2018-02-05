
/*
* DgpsConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 21.01.18
* 
*/

#include <sstream>
#include "DgpsConfig.h"
#include "Logger.h"

DgpsConfig::DgpsConfig(const std::string& portName, int baudRate) :
             m_portName(portName), m_baudRate(baudRate) {
    LOG << toString() << "\n";
}

std::string DgpsConfig::toString() const {
    std::stringstream ss;
    ss << "Dgps Configuration is: " << std::endl <<
         "     port name: |" << m_portName << "|" << std::endl <<
         "     baud rate: " << m_baudRate;
    return ss.str();
}