#ifndef IPONCONFIG_H
#define IPONCONFIG_H

/*
* IponConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 02.05.18
* 
*/

#include "ProdConfig.h"

class IponConfig : public ProdConfig {
private:
    static const std::string UDP_IP_ADDRESS_KEY;
    static const std::string UDP_IP_ADDRESS_DEF_VAL;
    static const std::string UDP_PORT_KEY;
    static const std::string UDP_PORT_DEF_VAL;
    static const std::string TCP_PORT_KEY;
    static const std::string TCP_PORT_DEF_VAL;

protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    IponConfig(const std::string& confFilePath);

    virtual ~IponConfig(){}

    std::string GetUDPIPAdrress() const;

    std::string GetUDPPort() const;

    std::string GetTCPPort() const;
};



#endif // IPONCONFIG_H