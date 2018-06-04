#ifndef IDANCONFIG_H
#define IDANCONFIG_H

/*
* IdanConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "ProdConfig.h"

class IdanConfig : public ProdConfig {
private:
    static const std::string INTERFACE_NAME_KEY;
    static const std::string INTERFACE_NAME_DEF_VAL;
    static const std::string IS_VIRTUAL_INTERFACE_KEY;
    static const std::string IS_VIRTUAL_INTERFACE_DEF_VAL;
    static const std::string CAN_BAUD_RATE_KEY;
    static const std::string CAN_BAUD_RATE_DEF_VAL;
    static const std::string HLC_HERTZ_KEY;
    static const std::string HLC_HERTZ_DEF_VAL;
protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    IdanConfig(const std::string& confFilePath);

    virtual ~IdanConfig() = default;

    std::string GetInterfaceName() const;

    int GetBaudRate() const;

    float GetHLCHertz() const;

    bool IsVirtualInterface() const;
};



#endif // IDANCONFIG_H