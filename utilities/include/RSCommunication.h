#ifndef RSCOMMUNICATION_H
#define RSCOMMUNICATION_H

/*
* RSCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 24.01.18
* 
*/

#include <string>
#include <boost/asio.hpp> // boost::asio::io_service
#include <boost/asio/serial_port.hpp>
#include "ICommunication.h"

typedef boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;

class RSCommunication : public ICommunication {
private:
    serial_port_ptr m_port;
    std::string m_tty;

public:
    RSCommunication(const std::string& tty);
    ~RSCommunication() = default;

    bool Init();
    int SendData(const char* buffer, int sizeOfData) const;
};



#endif // RSCOMMUNICATION_H