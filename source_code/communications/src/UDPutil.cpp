
#include "UDPutil.h"
//#include "Mmsystem.h"


C_UDPutill* my_Ptr;
//void CALLBACK TimerFunction(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
//stay
C_UDPutill::C_UDPutill()
{
	//pass to C++ log class
	my_Ptr = this;
	m_TCP_Send_Counter = 0;
	m_UDPsckt = NULL;
}

//bool C_UDPutill::s_wsFlag = false;
bool C_UDPutill::wSstartup()
{
	WSADATA WSAData;
	int ErrorNum;

	if (0 != WSAStartup(MAKEWORD(2, 2), &WSAData))
	{
		ErrorNum = WSAGetLastError();
		return(false);
	}
	return(true);
}
/*
bool C_UDPutill::openUDP_Socket(void)
{
	int				ErrorNum;
	unsigned long	NonBlocking = 1;
	int				optValue = 0;
	int				ret;
	int				optLen = 4;

	if (m_UDPsckt == NULL)
	{
		if ((m_UDPsckt = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			ErrorNum = WSAGetLastError();
			return(false);
		}
	}
	ioctlsocket(m_UDPsckt, FIONBIO, &NonBlocking);
	//	SOCKADDR_IN lsock;

	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_RCVBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_SNDBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 1;							 // no loopback
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_REUSEADDR, (char*)&optValue, optLen); // changing size of buffer

																					 // build address to receive message on the socket   
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(m_UDPlocalPORT);  // mdp port number 
	servaddr_Lengh = sizeof(struct sockaddr_in);
	// build address to send message on the socket   
	memset(&clientaddr, 0, sizeof(servaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = inet_addr(m_UDPserverIP);
	clientaddr.sin_port = htons(m_UDPremotePORT);  // mdp port number 
	clientaddr_Lengh = sizeof(struct sockaddr_in);


	// connect to send socket 
	if (connect(m_UDPsckt, (struct sockaddr *)&clientaddr, sizeof(struct sockaddr_in)) < 0)
	{
		ErrorNum = WSAGetLastError();
		//		printf("(WSAStartup) Error %d Aplication will be closed!",ErrorNum);
		closesocket(m_UDPsckt);
		return(false);
	}

	return(true);
}

bool C_UDPutill::openUDP_SERVER_Socket(void)
{
	int				ErrorNum;
	unsigned long	NonBlocking = 1;
	int				optValue = 0;
	int				ret;
	int				optLen = 4;

	if (m_UDPsckt == NULL)
	{
		if ((m_UDPsckt = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			ErrorNum = WSAGetLastError();
			return(false);
		}
	}
	ioctlsocket(m_UDPsckt, FIONBIO, &NonBlocking);
	//	SOCKADDR_IN lsock;

	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_RCVBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_SNDBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 1;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_REUSEADDR, (char*)&optValue, optLen); // changing size of buffer

																					 // build address to receive message on the socket   
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons((unsigned short)m_UDPlocalPORT);  // mdp port number 
	clientaddr_Lengh = sizeof(struct sockaddr_in);



	if (bind(m_UDPsckt, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) < 0)
	{
		ErrorNum = WSAGetLastError();
		closesocket(m_UDPsckt);
		return(false);
	}



	return(true);
}
*/
bool C_UDPutill::openTCP_SERVER_Thread(void)
{
	DWORD dwThreadId;
	// THREAD
	////TIMECAPS	ptc;
	////UINT		cbtc = 0;
	////MMRESULT	result;
	////int			m_elTime = 20;

	////result = timeBeginPeriod(ptc.wPeriodMin);
	////if (result == TIMERR_NOERROR)
	////{
	////	result = timeSetEvent(
	////		m_elTime,
	////		ptc.wPeriodMin,
	////		TimerFunction,
	////		(DWORD)this,
	////		TIME_PERIODIC);
	////}
	m_ThreadTCP = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&WrapperTCP_SERVER_Thread, this, 0, &dwThreadId);

	return(true);
}
/*
bool C_UDPutill::UDPutill_LISTEN(void)
{
	struct hostent *hostp; // client host info
	char *hostaddrp; // dotted decimal host addr string

	m_childfd = 0;

	if (listen(m_UDPsckt, 5) < 0)
	{
		closesocket(m_UDPsckt);
		return(false);
	}
	clientaddr_Lengh = sizeof(clientaddr);
	// wait for connection request
	m_childfd = accept(m_UDPsckt, (struct sockaddr *)&clientaddr, &clientaddr_Lengh);
	if ((m_childfd < 0) || (m_childfd > 10000))
		return false;
	hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.S_un.S_addr, sizeof(clientaddr.sin_addr.S_un.S_addr), AF_INET);
	if (hostp == NULL)
		return false;
	hostaddrp = inet_ntoa(clientaddr.sin_addr);
	if (hostaddrp == NULL)
		return false;
	else
		return true;

}
bool C_UDPutill::openUDP_SPECIAL_SERVER_Socket(void)
{
	int				ErrorNum;
	unsigned long	NonBlocking = 1;
	int				optValue = 0;
	int				ret;
	int				optLen = 4;

	if (m_UDPsckt == NULL)
	{
		
		if ((m_UDPsckt = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			ErrorNum = WSAGetLastError();
			return(false);
		}
		
	}
	//	SOCKADDR_IN lsock;

	////////optValue = 60000 ;							 // non blocking --> reciveing message continiously
	////////ret = setsockopt(m_UDPsckt,SOL_SOCKET, SO_RCVBUF,(char*)&optValue, optLen); // changing size of buffer
	////////optValue = 60000 ;							 // non blocking --> reciveing message continiously
	////////ret = setsockopt(m_UDPsckt,SOL_SOCKET, SO_SNDBUF,(char*)&optValue, optLen); // changing size of buffer
	optValue = 1;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_REUSEADDR, (char*)&optValue, optLen); // changing size of buffer

																					 // build address to receive message on the socket   
	memset(&MyAddr, 0, sizeof(MyAddr));
	MyAddr.sin_family = AF_INET;
	MyAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	MyAddr.sin_port = htons(m_UDPlocalPORT);
	sockaddr_in_Lengh = sizeof(struct sockaddr_in);
	// build address to send message on the socket   
	memset(&TargetAddr[0], 0, sockaddr_in_Lengh);
	TargetAddr[0].sin_family = AF_INET;
	TargetAddr[0].sin_addr.s_addr = inet_addr(m_TargerIP[0]);
	TargetAddr[0].sin_port = htons(m_UDPremotePORT);
	memset(&TargetAddr[1], 0, sockaddr_in_Lengh);
	TargetAddr[1].sin_family = AF_INET;
	TargetAddr[1].sin_addr.s_addr = inet_addr(m_TargerIP[1]);
	TargetAddr[1].sin_port = htons(m_UDPremotePORT);

	
		//		ioctlsocket( m_UDPsckt, FIONBIO, &NonBlocking );
	if (connect(m_UDPsckt, (struct sockaddr *)&TargetAddr[0], sockaddr_in_Lengh) < 0)
	{
		ErrorNum = WSAGetLastError();
		closesocket(m_UDPsckt);
		return(false);
	}
		ioctlsocket(m_UDPsckt, FIONBIO, &NonBlocking);
	
	return(true);
}
bool C_UDPutill::openUDP_CLIENT_Socket(void)
{
	int				ErrorNum;
	unsigned long	NonBlocking = 1;
	int				optValue = 0;
	int				ret;
	int				optLen = 4;

	if (m_UDPsckt == NULL)
	{
	
		if ((m_UDPsckt = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			ErrorNum = WSAGetLastError();
			return(false);
		}
		
	}
	ioctlsocket(m_UDPsckt, FIONBIO, &NonBlocking);
	//	SOCKADDR_IN lsock;

	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_RCVBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 60000;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_SNDBUF, (char*)&optValue, optLen); // changing size of buffer
	optValue = 1;							 // non blocking --> reciveing message continiously
	ret = setsockopt(m_UDPsckt, SOL_SOCKET, SO_REUSEADDR, (char*)&optValue, optLen); // changing size of buffer

																					 // build address to send message on the socket   
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(m_UDPserverIP);// Destination IP adress
	servaddr.sin_port = htons(m_UDPremotePORT);  // mdp port number 
	clientaddr_Lengh = sizeof(clientaddr);
	return(true);
}
*/
//stay
bool C_UDPutill::UDPutill_INIT(int PortLocal, std::string PortRemote, char *IP_1, char *IP_2, SocketType SocketTypeIn)
{
	if (!C_UDPutill::s_wsFlag)
	{
		// start the SOCKET option
		if (false == wSstartup())
			return false;
		else
			C_UDPutill::s_wsFlag = true;
	}
	m_RCVlen = 0;
	// start the socket
	m_UDPlocalPORT = PortLocal;
	m_TCPlocalPORT = PortLocal;
	m_UDPremotePORT = std::stoi(PortRemote);
	SocketTypeMode = SocketTypeIn;
	m_ThreadTCP = NULL;
	m_TCP_Init = false;

		
	strcpy_s(m_UDPserverIP, 50, IP_1);
	return openTCP_SERVER_Thread();

	}
//stay
bool C_UDPutill::UDPutill_SEND(char *SendBuff, int SendBuffLen)
{
	int len = 0;
	int len1 = 0;
	bool RtnVal = false;

	if (m_UDPsckt != NULL)
	{
		len = sendto(m_UDPsckt, SendBuff, SendBuffLen, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		if (len > 0)
		{
			RtnVal = true;
			
				m_TCP_Send_Counter++;
		}
		else
		{
			m_TCP_Send_Counter++;
		}

	}
	return RtnVal;
}
//stay
bool C_UDPutill::UDPutill_RECEIVE(char *RcvBuff, int RcvBuffLen)
{
	bool RtnVal = false;
	m_RCVlen = 0;
	int Rcv1 = 0;
	int Rcv2 = 0;
	DWORD err;

	if (m_UDPsckt != NULL)
	{
		m_RCVlen = recvfrom(m_UDPsckt, RcvBuff, RcvBuffLen, 0, (struct sockaddr *)&clientaddr, &clientaddr_Lengh);
		if (m_RCVlen > 0)
			RtnVal = true;	
	}
	return RtnVal;
}
/*
int C_UDPutill::UDPutill_GetReciveBuffLen(void)
{
	return (m_RCVlen);
}
void UDPutill_FLUSH_RCV_BUFFER(void)
{
	//int				ret;
	//int				optLen = 4;

	//optValue = 60000 ;							 
	//ret = setsockopt(m_UDPsckt,SOL_SOCKET, SO_RCVBUF,(char*)&optValue, optLen);
}
void C_UDPutill::UDPutill_CLOSE(void)
{
	if (m_UDPsckt != NULL)
		closesocket(m_UDPsckt);
	if (m_ThreadTCP != NULL)
	{
		TerminateThread(m_ThreadTCP, 0);
		CloseHandle(m_ThreadTCP);
	}
}

void C_UDPutill::closeTCP_SERVER_Socket(void)
{
	closesocket(m_UDPsckt);// m_TCPsckt);
	WSACleanup();
}
*/
bool C_UDPutill::openTCP_SERVER_Socket(void)
{
	///	int				ErrorNum;
	unsigned long	NonBlocking = 1;
	int				optValue = 0;
	///	int				ret;
	int				optLen = 4;
	SOCKET			ListenSocket = INVALID_SOCKET;
	struct addrinfo hints;
	struct addrinfo *result = NULL;
	int				iResult;
	char			StrLocalPort[20] = { 0 };

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	sprintf_s(StrLocalPort, 20, "%d", m_TCPlocalPORT);
	iResult = getaddrinfo(NULL, StrLocalPort, &hints, &result);
	if (iResult != 0)
	{
		//		printf("Fatal Error:getaddrinfo failed %d\n", iResult);
		WSACleanup();
		//		nRetCode = 0;
		//		return nRetCode;
		return(false);
	}
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		//		printf("Fatal Error:socket failed %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//		nRetCode = 0;
		//		return nRetCode;
		return(false);
	}
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		//		printf("Fatal Error:bind failed %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		//		nRetCode = 0;
		//		return nRetCode;
		return(false);
	}
	freeaddrinfo(result);
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		//		printf("Fatal Error:listen failed %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//		nRetCode = 0;
		//		return nRetCode;
		return(false);
	}
	//	m_TCPsckt = accept(ListenSocket, NULL, NULL);
	m_UDPsckt = accept(ListenSocket, NULL, NULL);
	//	if (m_TCPsckt == INVALID_SOCKET)
	if (m_UDPsckt == INVALID_SOCKET)
	{
		//		printf("Fatal Error:accept failed %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//		nRetCode = 0;
		//		return nRetCode;
		return(false);
	}
	//	ioctlsocket(m_TCPsckt, FIONBIO, &NonBlocking);
	ioctlsocket(m_UDPsckt, FIONBIO, &NonBlocking);
	closesocket(ListenSocket);

	return(true);
}

//void CALLBACK TimerFunction(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
DWORD C_UDPutill::WrapperTCP_SERVER_Thread(LPVOID lpParam)
{
	return my_Ptr->TCP_SERVER_Thread(lpParam);
}

DWORD C_UDPutill::TCP_SERVER_Thread(LPVOID lpParam)
{
	while (1)
	{
		if (m_TCP_Init == false)
		{
			if (true == openTCP_SERVER_Socket())
				m_TCP_Init = true;
		}
		if (m_TCP_Init == true)
		{
			if (m_TCP_Send_Counter > 10)
			{
				// close TCP server and start again
				//				closeTCP_SERVER_Socket();
				m_TCP_Init = false;
			}
		}
		else
			Sleep(10);
	}
	return 0;
}

