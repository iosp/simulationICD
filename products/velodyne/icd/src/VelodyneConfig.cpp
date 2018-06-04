/*
* VelodyneConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
*/

#include "VelodyneConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include <boost/assign.hpp> // boost::assign::map_list_of

const std::string VelodyneConfig::IP_ADDRESS_KEY = "IP_ADDRESS";
const std::string VelodyneConfig::IP_ADDRESS_DEF_VAL = "192.168.1.77";
const std::string VelodyneConfig::PORT_KEY = "PORT";
const std::string VelodyneConfig::PORT_DEF_VAL = "2368";
const std::string VelodyneConfig::RETURN_MODE_KEY = "RETURN_MODE";
const std::string VelodyneConfig::RETURN_MODE_DEF_VAL = "37";
const std::string VelodyneConfig::DATA_SOURCE_KEY = "DATA_SOURCE";
const std::string VelodyneConfig::DATA_SOURCE_DEF_VAL = "22";

const std::map<VelodyneConfig::ReturnMode, std::string> VelodyneConfig::retModeToStr = 
            boost::assign::map_list_of(VelodyneConfig::_STRONGEST_, "strongest")(VelodyneConfig::_LAST_, "last")(VelodyneConfig::_DUAL_, "dual");

const std::map<VelodyneConfig::DataSource, std::string> VelodyneConfig::dataSourceToStr = 
            boost::assign::map_list_of(VelodyneConfig::_HDL32E_, "HDL_32E")(VelodyneConfig::_VELODYNE16_, "Velodyne16");

VelodyneConfig::VelodyneConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    Init();
    if (!ValidateConfiguration()) {
        ERRLOG << "Velodyne configuration is not valid!\n";
    }
}

void VelodyneConfig::SetConfDefaultValues() {
	m_conf->SetValue(IP_ADDRESS_KEY, IP_ADDRESS_DEF_VAL);
	m_conf->SetValue(PORT_KEY, PORT_DEF_VAL);
    m_conf->SetValue(RETURN_MODE_KEY, RETURN_MODE_DEF_VAL);
    m_conf->SetValue(DATA_SOURCE_KEY, DATA_SOURCE_DEF_VAL);
}

std::string VelodyneConfig::GetProdName() const {
    return "Velodyne";
}

bool VelodyneConfig::ValidateConfiguration() const {
    bool valid = true;
    if (retModeToStr.find(GetReturnMode()) == retModeToStr.end()) {
        ERRLOG << "Value of " << RETURN_MODE_KEY << ": " << GetReturnMode() << " is not valid!\n";
        valid = false;
    }
    if (dataSourceToStr.find(GetDataSource()) == dataSourceToStr.end()) {
        ERRLOG << "Value of " << DATA_SOURCE_KEY << ": " << GetDataSource() << " is not valid!\n";
        valid = false;
    }
    return valid;
}


std::string VelodyneConfig::GetIpAddress() const {
    return m_conf->GetValue<std::string>(IP_ADDRESS_KEY);
}

std::string VelodyneConfig::GetPort() const {
    return m_conf->GetValue<std::string>(PORT_KEY);
}

VelodyneConfig::ReturnMode VelodyneConfig::GetReturnMode() const {
    return (ReturnMode)m_conf->GetValue<int>(RETURN_MODE_KEY);
}

VelodyneConfig::DataSource VelodyneConfig::GetDataSource() const {
    return (DataSource)m_conf->GetValue<int>(DATA_SOURCE_KEY);
}