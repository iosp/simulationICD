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
    bool m_isVirtualInterface;
    int m_baudRate;
    int m_getSocket;
    int m_sendSocket;

    // initialize baud rate with system call
    void InitBaudRate();
    // initialize CAN to get data
    bool InitGet();
    // initialize CAN to send data
    bool InitSend(); 

public:
    CanCommunication(const std::string& interfaceName, int baudRate, bool isVirtualInterface);
    ~CanCommunication();

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) override;
    void GetData(char* buffer) override;
    
};



#endif // CANCOMMUNICATION_H