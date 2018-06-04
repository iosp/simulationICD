#ifndef NOVATELCONFIG_H
#define NOVATELCONFIG_H

/*
* NovatelConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 31.01.18
*/

#include "ProdConfig.h"

class NovatelConfig : public ProdConfig {
private:
    static const std::string PORT_NAME_KEY;
    static const std::string PORT_NAME_DEF_VAL;

    static const std::string BAUD_RATE_KEY;
    static const std::string BAUD_RATE_DEF_VAL;

protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    NovatelConfig(const std::string& confFilePath);

    virtual ~NovatelConfig() {}

    std::string GetPortName() const;

    int GetBaudRate() const;
};



#endif // NOVATELCONFIG_H