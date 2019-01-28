
/*
* NovatelConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 21.01.18
* 
*/

#include "NovatelConfig.h"
#include "ConfigurationINI.h"

const std::string NovatelConfig::PORT_NAME_KEY = "PORT_NAME";
const std::string NovatelConfig::PORT_NAME_DEF_VAL = "COM1";
const std::string NovatelConfig::BAUD_RATE_KEY = "BAUD_RATE";
const std::string NovatelConfig::BAUD_RATE_DEF_VAL = "115200";

NovatelConfig::NovatelConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    LOG << "Initializing novatel configurations\n";
    Init();
}

void NovatelConfig::SetConfDefaultValues() {
	m_conf->SetValue(PORT_NAME_KEY, PORT_NAME_DEF_VAL);
	m_conf->SetValue(BAUD_RATE_KEY, BAUD_RATE_DEF_VAL);
}

std::string NovatelConfig::GetProdName() const {
    return "Novatel";
}

std::string NovatelConfig::GetPortName() const {
    return m_conf->GetValue<std::string>(PORT_NAME_KEY);
}

int NovatelConfig::GetBaudRate() const {
    return m_conf->GetValue<int>(BAUD_RATE_KEY);
}