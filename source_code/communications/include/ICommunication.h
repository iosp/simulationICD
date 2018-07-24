#ifndef ICOMMUNICATION_H
#define ICOMMUNICATION_H

/*
* ICommunication.h
* Interface for communication protocol
* Author: Binyamin Appelbaum
* Date: 25.01.18
*/

class ICommunication {
public:
    
    ICommunication() = default;
    
    virtual ~ICommunication() = default;
    
    /**
     * Initialize communication protocol
     * @return true if succeeded and false O.W
     */ 
    virtual bool Init() = 0;
    /**
     * Send data via protocol
     * @param buffer - the data to send
     * @sizeOfData - data size to send
     * @return num of bytes that has been sent
     */ 
    virtual int SendData(const char* buffer, int sizeOfData) = 0;
    /**
     * Get data via protocol
     * @param buffer - the data to get - output
     */ 
    virtual void GetData(/* out */ char* buffer) = 0;
};


#endif // ICOMMUNICATION_H