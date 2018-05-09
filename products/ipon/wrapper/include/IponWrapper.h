#ifndef IPONWRAPPER_H
#define IPONWRAPPER_H

/*
* IponWrapper.h
* Wrapper for IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponData.h"
#include "IWrapper.h"

/**

 * */
class IponWrapper : public IWrapper<IponData> {
private:
    IponData m_data;

    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    IponWrapper(const std::string& confFilePath);

    ~IponWrapper();

    /**
     * Calls ibeo->run
     */ 
    virtual void Run() override;

    /**
     * Take the temporary data and set it to icd
     */ 
    virtual void SetData() override;

    virtual void GetData() override {}
};

#endif // IPONWRAPPER_H