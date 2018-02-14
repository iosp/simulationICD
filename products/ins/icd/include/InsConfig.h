#ifndef INSCONFIG_H
#define INSCONFIG_H

/*
* InsConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include <string>

class ConfigurationINI; // forward declaration

class InsConfig {
private:
    ConfigurationINI* m_insConf;

    void SetConfDefaultValues();

public:
    InsConfig(const std::string& confFilePath);

    virtual ~InsConfig();

};



#endif // INSCONFIG_H