
/*
* VLPConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include "VLPConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include <boost/assign.hpp> // boost::assign::map_list_of

const std::string VLPConfig::IP_ADDRESS_KEY = "IP_ADDRESS";
const std::string VLPConfig::IP_ADDRESS_DEF_VAL = "192.168.1.77";
const std::string VLPConfig::PORT_KEY = "PORT";
const std::string VLPConfig::PORT_DEF_VAL = "2368";
const std::string VLPConfig::RETURN_MODE_KEY = "RETURN_MODE";
const std::string VLPConfig::RETURN_MODE_DEF_VAL = "37";
const std::string VLPConfig::DATA_SOURCE_KEY = "DATA_SOURCE";
const std::string VLPConfig::DATA_SOURCE_DEF_VAL = "22";

const std::map<VLPConfig::ReturnMode, std::string> VLPConfig::retModeToStr = 
            boost::assign::map_list_of(VLPConfig::_STRONGEST_, "strongest")(VLPConfig::_LAST_, "last")(VLPConfig::_DUAL_, "dual");

const std::map<VLPConfig::DataSource, std::string> VLPConfig::dataSourceToStr = 
            boost::assign::map_list_of(VLPConfig::_HDL32E_, "HDL_32E")(VLPConfig::_VLP16_, "VLP16");

VLPConfig::VLPConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    Init();
    if (!ValidateConfiguration()) {
        ERRLOG << "Velodyne configuration is not valid!\n";
    }
}

void VLPConfig::SetConfDefaultValues() {
	m_conf->SetValue(IP_ADDRESS_KEY, IP_ADDRESS_DEF_VAL);
	m_conf->SetValue(PORT_KEY, PORT_DEF_VAL);
    m_conf->SetValue(RETURN_MODE_KEY, RETURN_MODE_DEF_VAL);
    m_conf->SetValue(DATA_SOURCE_KEY, DATA_SOURCE_DEF_VAL);
}

std::string VLPConfig::GetProdName() const {
    return "Velodyne";
}

bool VLPConfig::ValidateConfiguration() const {
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


std::string VLPConfig::GetIpAddress() const {
    return m_conf->GetValue<std::string>(IP_ADDRESS_KEY);
}

std::string VLPConfig::GetPort() const {
    return m_conf->GetValue<std::string>(PORT_KEY);
}

VLPConfig::ReturnMode VLPConfig::GetReturnMode() const {
    return (ReturnMode)m_conf->GetValue<int>(RETURN_MODE_KEY);
}

VLPConfig::DataSource VLPConfig::GetDataSource() const {
    return (DataSource)m_conf->GetValue<int>(DATA_SOURCE_KEY);
}