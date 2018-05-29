#ifndef IICD_H
#define IICD_H

/*
* IICD.h
* Interface for ICD commonication
* Author: Binyamin Appelbaum
* Date: 09.01.18
* 
*/

template <class TData>
class IICD {
protected:
    bool m_isCommInitialized = false;

    /**
     * Initialize communication of the ICD
    */
    virtual void InitCommunication() = 0;
    
public:
    IICD() = default;
    
    virtual ~IICD() = default;

    /**
     * Set Data on ICD commonication object
     */ 
    virtual void SendData(const TData& data) = 0;

    /**
     * Receive Data from ICD commonication object
     */ 
    virtual TData ReceiveData() = 0;
};

#endif // IICD_H