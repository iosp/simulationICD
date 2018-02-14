
/*
* InsConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "InsConfig.h"
#include "Logger.h"
#include "ConfigurationINI.h"
#include <sstream>

InsConfig::InsConfig(const std::string& confFilePath) {
    m_insConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_insConf->ParseConfFile();

    LOG << "INS configuration is:\n" << m_insConf->toString() << "\n";

}

InsConfig::~InsConfig() {
    delete m_insConf;
}

void InsConfig::SetConfDefaultValues() {

}
