#ifndef IWRAPPER_H
#define IWRAPPER_H

/*
* IWrapper.h
* 
* Author: Binyamin Appelbaum
* Date: 09.01.18
* 
*/

#include "IICD.h"

template <class T>
class IWrapper {
protected:
    IICD<T>* m_icd;
    
public:
    
    IWrapper() = default;
    
    virtual ~IWrapper() = default;

    virtual void SetData() = 0;

    virtual void Run() = 0;
};


#endif // IWRAPPER_H