#ifndef IICD_H
#define IICD_H

/*
* IICD.h
* 
* Author: Binyamin Appelbaum
* Date: 09.01.18
* 
*/

template <class T>
class IICD {
public:
    IICD() = default;
    
    virtual ~IICD() = default;

    virtual void SetData(const T& data) = 0;

    virtual T* GetData() = 0;

    virtual void Run() = 0;
};

#endif // IICD_H