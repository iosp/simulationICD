#ifndef DGPSCONFIG_H
#define DGPSCONFIG_H

/*
* DgpsConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 31.01.18
* 
*/

#include <string>
#include "ProdConfig.h"

class ConfigurationINI; // forward declaration

class DgpsConfig : public ProdConfig {
private:
    static const std::string PORT_NAME_KEY;
    static const std::string PORT_NAME_DEF_VAL;

    static const std::string BAUD_RATE_KEY;
    static const std::string BAUD_RATE_DEF_VAL;

    static const std::string HERTZ_KEY;
    static const std::string HERTZ_DEF_VAL;

protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    DgpsConfig(const std::string& confFilePath);

    virtual ~DgpsConfig() {}

    std::string GetPortName() const;

    int GetBaudRate() const;

    float GetHertz() const;
};



#endif // DGPSCONFIG_H