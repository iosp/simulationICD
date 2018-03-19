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
#include <boost/lexical_cast.hpp>
#include "LoggerProxy.h"

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
    template <class T>
    T GetValue(const std::string& key) const {
        std::string strVal;
        T retVal;
        // find value in map
        if (m_confMap.find(key) != m_confMap.end()) {
            strVal = m_confMap.find(key)->second;
        }
        else {
            ERRLOG << "Key " << key << " does not exist on map!\n";
            return retVal;
        }

        // convert the value to the required type
        try {
            retVal = boost::lexical_cast<T>(strVal);
        }
        catch (const boost::bad_lexical_cast& e) {
            ERRLOG << e.what() << "\n";
        }
        return retVal;
    }

    // set value in map configuration
    void SetValue(const std::string& key, const std::string& val);

    // generate a string of the configuration map
    std::string toString() const;
};


#endif // CONFIGURATIONINI_H