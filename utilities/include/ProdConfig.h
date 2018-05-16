#ifndef PRODCONFIG_H
#define PRODCONFIG_H

/*
* ProdConfig.h
* Interface for sensor configuration
* Author: Binyamin Appelbaum
* Date: 08.05.18
* 
*/

#include <string>

class ConfigurationINI; // forward declaration

class ProdConfig {
private:
    const std::string m_confFilePath;
    
protected:
    ConfigurationINI* m_conf = nullptr;

    virtual void SetConfDefaultValues() = 0;

    virtual std::string GetProdName() const = 0;

    virtual void Init();

public:
    ProdConfig(const std::string& confFilePath);

    virtual ~ProdConfig();
};



#endif // PRODCONFIG_H