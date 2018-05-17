#ifndef INSCONFIG_H
#define INSCONFIG_H

/*
* InsConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 12.02.18s 
*/

#include "ProdConfig.h"

class ConfigurationINI; // forward declaration

class InsConfig : public ProdConfig {
private:
    static const std::string STATUS_MSG_PORT_KEY;
    static const std::string STATUS_MSG_PORT_DEF_VAL;

    static const std::string NAVIGATION_DATA_MSG_IP_ADDRESS_KEY;
    static const std::string NAVIGATION_DATA_MSG_IP_ADDRESS_DEF_VAL;
    static const std::string NAVIGATION_DATA_MSG_PORT_KEY;
    static const std::string NAVIGATION_DATA_MSG_PORT_DEF_VAL;

    static const std::string INTERNAL_GPS_MSG_IP_ADDRESS_KEY;
    static const std::string INTERNAL_GPS_MSG_IP_ADDRESS_DEF_VAL;
    static const std::string INTERNAL_GPS_MSG_PORT_KEY;
    static const std::string INTERNAL_GPS_MSG_PORT_DEF_VAL;

    static const std::string ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY;
    static const std::string ERRORS_ESTIMATION_MSG_IP_ADDRESS_DEF_VAL;
    static const std::string ERRORS_ESTIMATION_MSG_PORT_KEY;
    static const std::string ERRORS_ESTIMATION_MSG_PORT_DEF_VAL;

protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    InsConfig(const std::string& confFilePath);

    virtual ~InsConfig(){}

    std::string GetStatusMsgPort() const;

    std::string GetNavigationDataMsgIpAddress() const;
    std::string GetNavigationDataMsgPort() const;

    std::string GetInternalGPSMsgIpAddress() const;
    std::string GetInternalGPSMsgPort() const;

    std::string GetErrorsEstimationMsgIpAddress() const;
    std::string GetErrorsEstimationMsgPort() const;
};



#endif // INSCONFIG_H