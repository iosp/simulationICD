/*
* CanCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#include <fcntl.h>
#include "CanCommunication.h"
#include "LoggerProxy.h"
#include "Helper.h"

CanCommunication::CanCommunication(const std::string& interfaceName, int baudRate, bool isVirtualInterface) 
	: m_interfaceName(interfaceName), m_baudRate(baudRate), m_isVirtualInterface(isVirtualInterface) {
}

CanCommunication::~CanCommunication() {

}

bool CanCommunication::Init() {
	InitBaudRate();
	return InitGet() && InitSend();
}

void CanCommunication::InitBaudRate() {
	if (!m_isVirtualInterface) {
		std::stringstream ss;
		// set can down
		ss << "sudo ip link set " << m_interfaceName << " down";
		Utilities::RunSystemCmd(ss.str());
		ss.str("");
		// change bitrate
		ss << "sudo ip link set " << m_interfaceName << " type can bitrate " << m_baudRate;
		Utilities::RunSystemCmd(ss.str());
		ss.str("");
		// set can up
		ss << "sudo ip link set " << m_interfaceName << " up";
		Utilities::RunSystemCmd(ss.str());
	}
}

bool CanCommunication::InitGet() {
	struct sockaddr_can addr;
	struct ifreq ifr;

	if ((m_getSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		ERRLOG << "Error while opening socket\n";
		return false;
	}

	strcpy(ifr.ifr_name, m_interfaceName.c_str());
	ioctl(m_getSocket, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex; 

	if (bind(m_getSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		ERRLOG << "Error in socket bind\n" ;
		return false;
	}

	int setflag = setflag|O_NONBLOCK;
	int ret = fcntl(m_getSocket, F_SETFL,setflag);
	int getflag = fcntl(m_getSocket ,F_GETFL,0);

	can_err_mask_t err_mask = CAN_ERR_TX_TIMEOUT |CAN_ERR_BUSOFF;
	ret = setsockopt(m_getSocket , SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask));
	if (ret != 0) {
		ERRLOG << "setsockopt fail\n";
    }

	LOG << "Can Get initialized successfully. interface name: " << m_interfaceName << "\n";
    return true;
}

bool CanCommunication::InitSend() {
	struct sockaddr_can addr;
	struct ifreq ifr;

	if ((m_sendSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		ERRLOG << "Error while opening socket\n";
		return false;
	}

	strcpy(ifr.ifr_name, m_interfaceName.c_str());
	ioctl(m_sendSocket, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex; 


	if (bind(m_sendSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)  {
		ERRLOG << "Error in socket bind\n";
		return false;
	}		

	LOG << "Can send initialized successfully. interface name: " << m_interfaceName << "\n";
	return true;
}

void CanCommunication::GetData(char* buffer) {
    struct can_frame frame;
    
    int nbytes = read(m_getSocket, &frame, sizeof(frame));
    if (nbytes > 0) {
		DBGLOG << "Can read " << nbytes << " bytes from socket\n";
        if (frame.can_id & CAN_ERR_FLAG) {
            ERRLOG << "error frame\n";
        }
        else {
            memcpy(buffer, &frame.can_id, sizeof(frame.can_id));
            memcpy(buffer + 4, &frame.can_dlc, sizeof(frame.can_dlc));
            memcpy(buffer + 8, &frame.data, sizeof(frame.data));
        }
	}
}

int CanCommunication::SendData(const char* buffer, int sizeOfData) {
	struct can_frame frame;
	memcpy(&frame.can_id, buffer, sizeof(frame.can_id));
	memcpy(&frame.can_dlc, buffer + 4, sizeof(frame.can_dlc));
	memcpy(&frame.data, buffer + 8, sizeof(frame.data));
	DBGLOG << "Can is going to send " << sizeOfData << " bytes to socket\n";
    int nbytes = write(m_sendSocket, &frame, sizeof(struct can_frame));
    return nbytes;
}