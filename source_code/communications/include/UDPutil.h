// **********************************************************
//
// File Name:		 UDPutil.h
//
// Revision History:
// ==========================================================
// Version		Date				Modifier Name
// ==========================================================
// <nnnnn>		<dd/mm/yyyy>		<modifier name>

//  ....
//
// **********************************************************

#ifndef C_UDP_UTIL
#define C_UDP_UTIL
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <ws2def.h>
//#include <winsock2.h>
#define UDP 0
#define TCP 1

enum SocketType { SERVER = 0, CLIENT = 1, PEAR_TO_PEAR, SPECIAL_SERVER };



class C_UDPutill
{
public:
	C_UDPutill();
	bool UDPutill_INIT(int PortLocal, std::string PortRemote, char *IP_1, char *IP_2, SocketType SocketTypeIn);
	bool UDPutill_SEND(char *SendBuff, int SendBuffLen);
	bool UDPutill_RECEIVE(char *RcvBuff, int RcvBuffLen);

private:
	static DWORD WrapperTCP_SERVER_Thread(LPVOID lpParam);
	DWORD TCP_SERVER_Thread(LPVOID lpParam);
	bool openTCP_SERVER_Socket(void);
	int	m_TCPlocalPORT;
	bool s_wsFlag;
	HANDLE m_ThreadTCP;
	bool wSstartup();
	bool m_TCP_Init;
	int m_TCP_Send_Counter;
	bool openTCP_SERVER_Thread(void);
	SocketType SocketTypeMode;

	SOCKET				m_UDPsckt;
	int					m_UDPlocalPORT;
	int					m_UDPremotePORT;
	int					m_RCVlen;


	char				m_UDPserverIP[50];
	SOCKADDR_IN         clientaddr;
	//struct sockaddr_in	clientaddr;
	int					clientaddr_Lengh;
};
#endif //C_UDP_UTIL 
