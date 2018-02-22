
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
const std::string VLPConfig::HORIZONTAL_RES_KEY = "HORIZONTAL_RES";
const std::string VLPConfig::HORIZONTAL_RES_DEF_VAL = "0.2";
const std::string VLPConfig::RETURN_MODE_KEY = "RETURN_MODE";
const std::string VLPConfig::RETURN_MODE_DEF_VAL = "37";
const std::string VLPConfig::DATA_SOURCE_KEY = "DATA_SOURCE";
const std::string VLPConfig::DATA_SOURCE_DEF_VAL = "22";
const std::string VLPConfig::SENSOR_FREQ_KEY = "SENSOR_FREQ";
const std::string VLPConfig::SENSOR_FREQ_KEY_DEF_VAL = "10";

const std::map<VLPConfig::ReturnMode, std::string> VLPConfig::retModeToStr = 
            boost::assign::map_list_of(VLPConfig::_STRONGEST_, "strongest")(VLPConfig::_LAST_, "last")(VLPConfig::_DUAL_, "dual");

const std::map<VLPConfig::DataSource, std::string> VLPConfig::dataSourceToStr = 
            boost::assign::map_list_of(VLPConfig::_HDL32E_, "HDL_32E")(VLPConfig::_VLP16_, "VLP16");

VLPConfig::VLPConfig(const std::string& confFilePath) {
    m_vlpConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_vlpConf->ParseConfFile();
    if (ValidateConfiguration()) {
        LOG << "Velodyne configuration is:\n" << m_vlpConf->toString() << "\n";
    }
    else {
        ERRLOG << "Velodyne configuration is not valid!\n";
    }
}

VLPConfig::~VLPConfig() {
    delete m_vlpConf;
}

void VLPConfig::SetConfDefaultValues() {
	m_vlpConf->SetValue(IP_ADDRESS_KEY, IP_ADDRESS_DEF_VAL);
	m_vlpConf->SetValue(PORT_KEY, PORT_DEF_VAL);
    m_vlpConf->SetValue(HORIZONTAL_RES_KEY, HORIZONTAL_RES_DEF_VAL);
    m_vlpConf->SetValue(RETURN_MODE_KEY, RETURN_MODE_DEF_VAL);
    m_vlpConf->SetValue(DATA_SOURCE_KEY, DATA_SOURCE_DEF_VAL);
    m_vlpConf->SetValue(SENSOR_FREQ_KEY, SENSOR_FREQ_KEY_DEF_VAL);
}

bool VLPConfig::ValidateConfiguration() const {
    bool valid = true;
    if ((GetHorizontalResolution() * 1000 != _RES02_) && (GetHorizontalResolution() * 1000 != _RES04_)) {
        ERRLOG << "Value of " << HORIZONTAL_RES_KEY << ": " << GetHorizontalResolution() << " is not valid!\n";
        valid = false;
    }
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
    return m_vlpConf->GetValue(IP_ADDRESS_KEY);
}

std::string VLPConfig::GetPort() const {
    return m_vlpConf->GetValue(PORT_KEY);
}

double VLPConfig::GetHorizontalResolution() const {
    return std::stod(m_vlpConf->GetValue(HORIZONTAL_RES_KEY));
}

VLPConfig::ReturnMode VLPConfig::GetReturnMode() const {
    return (ReturnMode)std::stoi(m_vlpConf->GetValue(RETURN_MODE_KEY));
}

VLPConfig::DataSource VLPConfig::GetDataSource() const {
    return (DataSource)std::stoi(m_vlpConf->GetValue(DATA_SOURCE_KEY));
}

int VLPConfig::GetSensorFrequency() const {
    return std::stoi(m_vlpConf->GetValue(SENSOR_FREQ_KEY));
}