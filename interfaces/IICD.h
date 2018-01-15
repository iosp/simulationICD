#ifndef IICD_H
#define IICD_H

/*
* IICD.h
* Interface for ICD commonication
* Author: Binyamin Appelbaum
* Date: 09.01.18
* 
*/

template <class T>
class IICD {
public:
    IICD() = default;
    
    virtual ~IICD() = default;

    /**
     * Set Data on ICD commonication object
     */ 
    virtual void SetData(const T& data) = 0;

    /**
     * Get Data from ICD commonication object
     */ 
    virtual T* GetData() = 0;

    /**
     * Run ICD comminication, this is the operation point of the ICD
     */ 
    virtual void Run() = 0;
};

#endif // IICD_H