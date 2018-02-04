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

static const int SENSOR_FREQ = 10;

class VLPConfig {
public:
    enum Resolution { _RES02_ = 200, _RES04_ = 400};
    enum ReturnMode { _STRONGEST_ = 37, _LAST_ = 38, _DUAL_ = 39};
    enum DataSource {_HDL32E_ = 21, _VLP16_ = 22};

    static const std::map<ReturnMode, std::string> retModeToStr;
    static const std::map<DataSource, std::string> dataSourceToStr;

private:
    std::string m_ipAddress;
    std::string m_port;
    Resolution m_horizontalResolution;
    double m_realHorizontalResolution;
    ReturnMode m_returnMode;
    DataSource m_dataSource;
    int m_sensorFrequency;

public:
    VLPConfig() = default;
    VLPConfig(const std::string& ipAddress, const std::string& port, Resolution horizontalResolution = _RES02_,
        ReturnMode returnMode = _STRONGEST_, DataSource dataSource = _VLP16_,
            int sensorFrequency = SENSOR_FREQ);

    virtual ~VLPConfig() = default;

    const std::string& GetIpAddress() const {
        return m_ipAddress;
    }

    const std::string& GetPort() const {
        return m_port;
    }

    double GetRealHorizontalResolution() const {
        return m_realHorizontalResolution;
    }

    ReturnMode GetReturnMode() const {
        return m_returnMode;
    }

    DataSource GetDataSource() const {
        return m_dataSource;
    }

    int GetSensorFrequency() const {
        return m_sensorFrequency;
    }

    std::string toString() const;

};



#endif // VLPCONFIG_H