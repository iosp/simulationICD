
/*
* DgpsConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 21.01.18
* 
*/

#include "DgpsConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include <sstream>

const std::string DgpsConfig::PORT_NAME_KEY = "PORT_NAME";
const std::string DgpsConfig::PORT_NAME_DEF_VAL = "/dev/ttyUSB0";
const std::string DgpsConfig::BAUD_RATE_KEY = "BAUD_RATE";
const std::string DgpsConfig::BAUD_RATE_DEF_VAL = "115200";

DgpsConfig::DgpsConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    Init();
}

void DgpsConfig::SetConfDefaultValues() {
	m_conf->SetValue(PORT_NAME_KEY, PORT_NAME_DEF_VAL);
	m_conf->SetValue(BAUD_RATE_KEY, BAUD_RATE_DEF_VAL);
}

std::string DgpsConfig::GetProdName() const {
    return "DGPS";
}

std::string DgpsConfig::GetPortName() const {
    return m_conf->GetValue<std::string>(PORT_NAME_KEY);
}

int DgpsConfig::GetBaudRate() const {
    return m_conf->GetValue<int>(BAUD_RATE_KEY);
}