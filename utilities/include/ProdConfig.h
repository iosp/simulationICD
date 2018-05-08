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
protected:
    ConfigurationINI* m_conf = nullptr;

    std::string m_confFilePath;
    
    virtual void SetConfDefaultValues() = 0;

    virtual std::string GetProdName() const = 0;

    void Init();

public:
    ProdConfig();

    virtual ~ProdConfig();
};



#endif // PRODCONFIG_H