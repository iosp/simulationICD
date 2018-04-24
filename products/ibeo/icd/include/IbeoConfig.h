#ifndef IBEOCONFIG_H
#define IBEOCONFIG_H

/*
* IbeoConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 23.04.18
* 
*/

#include <string>
#include <map>

class ConfigurationINI; // forward declaration

class IbeoConfig {
private:
    ConfigurationINI* m_ibeoConf;

    static const std::string IP_ADDRESS_KEY;
    static const std::string IP_ADDRESS_DEF_VAL;

    static const std::string PORT_KEY;
    static const std::string PORT_DEF_VAL;

    static const std::string HERTZ_KEY;
    static const std::string HERTZ_DEF_VAL;

    void SetConfDefaultValues();

public:
    IbeoConfig(const std::string& confFilePath);

    virtual ~IbeoConfig();

    std::string GetIpAddress() const;

    std::string GetPort() const;

    float GetHertz() const;

};



#endif // IBEOCONFIG_H