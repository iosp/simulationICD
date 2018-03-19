
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
const std::string DgpsConfig::HERTZ_KEY = "HERTZ";
const std::string DgpsConfig::HERTZ_DEF_VAL = "10";

DgpsConfig::DgpsConfig(const std::string& confFilePath) {
    m_dgpsConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_dgpsConf->ParseConfFile();

    LOG << "Dgps configuration is:\n" << m_dgpsConf->toString() << "\n";

}

DgpsConfig::~DgpsConfig() {
    delete m_dgpsConf;
}

void DgpsConfig::SetConfDefaultValues() {
	m_dgpsConf->SetValue(PORT_NAME_KEY, PORT_NAME_DEF_VAL);
	m_dgpsConf->SetValue(BAUD_RATE_KEY, BAUD_RATE_DEF_VAL);
    m_dgpsConf->SetValue(HERTZ_KEY, HERTZ_DEF_VAL);
}

std::string DgpsConfig::GetPortName() const {
    return m_dgpsConf->GetValue(PORT_NAME_KEY);
}

int DgpsConfig::GetBaudRate() const {
    return std::stoi(m_dgpsConf->GetValue(BAUD_RATE_KEY)); // TODO handle wrong values!!
}

int DgpsConfig::GetHertz() const {
    return std::stoi(m_dgpsConf->GetValue(HERTZ_KEY));
}