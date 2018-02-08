#ifndef VLPCONFIG_H
#define VLPCONFIG_H

/*
* VLPConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include <string>
#include <map>

class ConfigurationINI; // forward declaration

class VLPConfig {
public:
    enum Resolution { _RES02_ = 200, _RES04_ = 400};
    enum ReturnMode { _STRONGEST_ = 37, _LAST_ = 38, _DUAL_ = 39};
    enum DataSource {_HDL32E_ = 21, _VLP16_ = 22};

    static const std::map<ReturnMode, std::string> retModeToStr;
    static const std::map<DataSource, std::string> dataSourceToStr;

private:
    ConfigurationINI* m_vlpConf;

    static const std::string IP_ADDRESS_KEY;
    static const std::string IP_ADDRESS_DEF_VAL;

    static const std::string PORT_KEY;
    static const std::string PORT_DEF_VAL;

    static const std::string HORIZONTAL_RES_KEY;
    static const std::string HORIZONTAL_RES_DEF_VAL;

    static const std::string RETURN_MODE_KEY;
    static const std::string RETURN_MODE_DEF_VAL;

    static const std::string DATA_SOURCE_KEY;
    static const std::string DATA_SOURCE_DEF_VAL;

    static const std::string SENSOR_FREQ_KEY;
    static const std::string SENSOR_FREQ_KEY_DEF_VAL;

    void SetConfDefaultValues();

    bool ValidateConfiguration() const;

public:
    VLPConfig(const std::string& confFilePath);

    virtual ~VLPConfig();

    std::string GetIpAddress() const;

    std::string GetPort() const;

    double GetHorizontalResolution() const;

    ReturnMode GetReturnMode() const;

    DataSource GetDataSource() const;

    int GetSensorFrequency() const;
};



#endif // VLPCONFIG_H