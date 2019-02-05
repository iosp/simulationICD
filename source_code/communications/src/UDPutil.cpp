#ifdef _WIN32
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

#endif