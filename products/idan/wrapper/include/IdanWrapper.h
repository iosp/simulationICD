#ifndef IDANWRAPPER_H
#define IDANWRAPPER_H

/*
* IdanWrapper.h
* Wrapper for Idan
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanData.h"
#include "IWrapper.h"

/**

 * */
class IdanWrapper : public IWrapper<IdanData> {
private:
    IdanData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    IdanWrapper(const std::string& confFilePath);

    ~IdanWrapper();

    virtual void Run() override;

    virtual void SetData() override {}

    virtual void GetData() override;

    unsigned char GetShutDownCmd();
   
};

#endif // IDANWRAPPER_H