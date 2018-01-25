#ifndef ICOMMUNICATION_H
#define ICOMMUNICATION_H

/*
* ICommunication.h
* Interface for communication protocol
* Author: Binyamin Appelbaum
* Date: 25.01.18
* 
*/

class ICommunication {
public:
    
    ICommunication() = default;
    
    virtual ~ICommunication() = default;
    
    /**
     * Send data via protocol
     * @param buffer - the data to send
     * @sizeOfData - data size to send
     * @return num of bytes that has been sent
     */ 
    virtual int SendData(const char* buffer, int sizeOfData) const = 0;
};


#endif // ICOMMUNICATION_H