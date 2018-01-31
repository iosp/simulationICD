
/*
* VLPConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include "VLPConfig.h"
#include <sstream>
#include <boost/assign.hpp> // boost::assign::map_list_of
#include "Logger.h"

const std::map<VLPConfig::ReturnMode, std::string> VLPConfig::retModeToStr = 
            boost::assign::map_list_of(VLPConfig::_STRONGEST_, "strongest")(VLPConfig::_LAST_, "last")(VLPConfig::_DUAL_, "dual");

const std::map<VLPConfig::DataSource, std::string> VLPConfig::dataSourceToStr = 
            boost::assign::map_list_of(VLPConfig::_HDL32E_, "HDL_32E")(VLPConfig::_VLP16_, "VLP16");

VLPConfig::VLPConfig(const std::string& ipAddress, const std::string& port, Resolution horizontalResolution,
             ReturnMode returnMode, DataSource dataSource, int sensorFrequency) :
             m_ipAddress(ipAddress), m_port(port), m_horizontalResolution(horizontalResolution),
              m_returnMode(returnMode), m_dataSource(dataSource), m_sensorFrequency(sensorFrequency) {
    m_realHorizontalResolution = m_horizontalResolution / 1000.0;
    LOG << toString() << "\n";
}

std::string VLPConfig::toString() {
    std::stringstream ss;
    ss << "Configuration is: " << std::endl <<
         "     ip address: |" << m_ipAddress << "|" << std::endl <<
         "     port: |" << m_port << "|" << std::endl <<
         "     horizontalResolution: " << m_horizontalResolution << std::endl <<
         "     returnMode: " << m_returnMode << std::endl <<
         "     dataSource: " << m_dataSource << std::endl <<
         "     sensorFrequency: " << m_sensorFrequency << std::endl <<
         "     realHorizontalResolution: " << m_realHorizontalResolution;
    return ss.str();
}