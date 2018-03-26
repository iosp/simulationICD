#ifndef IWRAPPER_H
#define IWRAPPER_H

/*
* IWrapper.h
* Interface for ICD Wrappers
* Author: Binyamin Appelbaum
* Date: 09.01.18
* 
*/

#include "IICD.h"

template <class T>
class IWrapper {
protected:
    /**
     * ICD object pointer (T represents the ICD data type)
    */
    IICD<T>* m_icd;
    
public:
    
    IWrapper() = default;
    
    virtual ~IWrapper() = default;

    /**
     * Set the accumolative data on ICD object
     */ 
    virtual void SetData() = 0;
    
    /**
     * Get the accumolative data tp ICD object
     */ 
    virtual void GetData() = 0;

    /**
     * Call run method of ICD object
     */ 
    virtual void Run() = 0;
};


#endif // IWRAPPER_H