/*
* ProdConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "ProdConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"

ProdConfig::ProdConfig(const std::string& confFilePath) : m_confFilePath(confFilePath) {
}

ProdConfig::~ProdConfig() {
    delete m_conf;
}

void ProdConfig::Init() {
    m_conf = new ConfigurationINI(m_confFilePath);
    SetConfDefaultValues();
    m_conf->ParseConfFile();
    LOG << GetProdName() << " configuration is:\n" << m_conf->toString() << "\n";
}