#ifndef IBEOCONFIG_H
#define IBEOCONFIG_H

/*
* IbeoConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 23.04.18
* 
*/

#include "ProdConfig.h"

class IbeoConfig : public ProdConfig {
private:
    static const std::string PORT_KEY;
    static const std::string PORT_DEF_VAL;

    static const std::string T_START_ANGLE_KEY;
    static const std::string T_START_ANGLE_DEF_VAL;
    static const std::string T_END_ANGLE_KEY;
    static const std::string T_END_ANGLE_DEF_VAL;

    static const std::string B_START_ANGLE_KEY;
    static const std::string B_START_ANGLE_DEF_VAL;
    static const std::string B_END_ANGLE_KEY;
    static const std::string B_END_ANGLE_DEF_VAL;

    static const std::string ANGLE_INCREMENT_KEY;
    static const std::string ANGLE_INCREMENT_DEF_VAL;
    
protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:
    IbeoConfig(const std::string& confFilePath);

    virtual ~IbeoConfig(){}

    std::string GetPort() const;

    double GetTStartAngle() const;

    double GetTEndAngle() const;

    double GetBStartAngle() const;

    double GetBEndAngle() const;

    double GetAngleIncrement() const;

};



#endif // IBEOCONFIG_H