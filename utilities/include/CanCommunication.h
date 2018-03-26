#ifndef CANCOMMUNICATION_H
#define CANCOMMUNICATION_H

/*
* CanCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include "ICommunication.h"
#include <string>

class CanCommunication : public ICommunication {
private:
    std::string m_interfaceName;
    int m_getSocket;
    int m_sendSocket;

public:
    CanCommunication(const std::string& interfaceName);
    ~CanCommunication();

    bool Init() override;
    bool InitGet();
    bool InitSend();
    int SendData(const char* buffer, int sizeOfData) override;
    void GetData(char* buffer) override;
    
};



#endif // CANCOMMUNICATION_H