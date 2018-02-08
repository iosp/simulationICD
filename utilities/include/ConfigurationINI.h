#ifndef CONFIGURATIONINI_H
#define CONFIGURATIONINI_H

/*
* ConfigurationINI.h
* INI configuration (key-value)
* Author: Binyamin Appelbaum
* Date: 07.02.18
*/

#include <string>
#include <map>

/**
 * Configuration class of key-value
 */ 
class ConfigurationINI {
private:
    // congiuration file path
    std::string m_filePath;
    // configuration map
    std::map<std::string, std::string> m_confMap;

public:

    ConfigurationINI(const std::string& filePath);
    
    virtual ~ConfigurationINI() = default;

    // parse configuration file (fills the map)
    void ParseConfFile();

    // Get value from map configuration
    std::string GetValue(const std::string& key) const;

    // set value in map configuration
    void SetValue(const std::string& key, const std::string& val);

    // generate a string of the configuration map
    std::string toString() const;
};


#endif // CONFIGURATIONINI_H