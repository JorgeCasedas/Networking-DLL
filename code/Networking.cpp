
/**********************************************************************
*Project           : MiddlewareDLL
*
*Author : Jorge Cásedas
*
*Starting date : 1/06/2020
*
*Ending date : 06/06/2020
*
*Purpose : Creating a dll in order to handle connections between aplications
*
**********************************************************************/

#include "Networking.hpp"

extern "C"
{
	int SetUpReceiver()
	{
		WSADATA     wsData;

		nResult = WSAStartup(MAKEWORD(2, 2), &wsData);

		struct addrinfo     info;
		struct addrinfo* pResult;

		ZeroMemory(&info, sizeof(info));
		info.ai_family = AF_INET;
		info.ai_socktype = SOCK_DGRAM;
		info.ai_protocol = IPPROTO_UDP;
		info.ai_flags = AI_PASSIVE;

		nResult = getaddrinfo(NULL, PORT, &info, &pResult);



		Receiver = socket(pResult->ai_family, pResult->ai_socktype, pResult->ai_protocol);
		if (Receiver == INVALID_SOCKET) {
			std::cout << WSAGetLastError() << std::endl;
			return 0;
		}


		ZeroMemory(&Sender, sizeof(Sender));
		Sender.sin_family = AF_INET;
		Sender.sin_port = htons(atoi(PORT));
		Sender.sin_addr.s_addr = INADDR_ANY;


		nResult = ::bind(Receiver, (struct sockaddr*) & Sender, nSize);
		if (nResult == INVALID_SOCKET) {
			int k = 3;
			return k;
		}
		return 1;
	}
	
	const char* RecieveMessage()
	{
		//cout << "waiting to recieve... " << endl;
		nResult = recvfrom(Receiver, szBuffer, sizeof(szBuffer), 0, (struct sockaddr*) & Sender, &nSize);
		//cout << "recieved" << endl << "waiting to print... " << endl;
		if (nResult > 0) 
		{
			if (nResult < 256)
			{
				szBuffer[nResult] = '\0';

				return szBuffer;
			}
				
			//cout << szBuffer << endl;
			return 0;
		}
		//cout << "printed" << endl;
		return 0;
	}

	int SendMessageToClient(char* buffer)
	{
		if (sendto(Receiver, buffer, strlen(buffer), 0, (struct sockaddr*) & Sender, nSize) == SOCKET_ERROR)
		{
			return 0;
		}
		return 1;
	}

	int SetUpClient()
	{

		WSADATA     wsData;

		nResultC = WSAStartup(MAKEWORD(2, 2), &wsData);

		struct addrinfo     info;
		

		ZeroMemory(&info, sizeof(info));
		info.ai_family = AF_INET;
		info.ai_socktype = SOCK_DGRAM;
		info.ai_protocol = IPPROTO_UDP;

		nResultC = getaddrinfo(NULL, PORT, &info, &pResultC);



		SenderC = socket(pResultC->ai_family, pResultC->ai_socktype, pResultC->ai_protocol);
		if (SenderC == INVALID_SOCKET) {
			std::cout << WSAGetLastError() << std::endl;
			return 0;
		}


		ZeroMemory(&Receiver, sizeof(Receiver));
		ReceiverC.sin_family = AF_INET;
		ReceiverC.sin_port = htons(atoi(PORT));
		ReceiverC.sin_addr.S_un.S_addr = inet_addr(SERVER);

		return 1;
	}


	int SendMessageToServer(char* buffer)
	{
		if (sendto(SenderC, buffer, strlen(buffer), 0, (struct sockaddr*) & ReceiverC, nSizeC) == SOCKET_ERROR)
		{
			return 0;
		}
		return 1;
	}

	const char* RecieveMessageFromServer()
	{
		nResultC = recvfrom(SenderC, szBufferC, sizeof(szBufferC), 0, (struct sockaddr*) & ReceiverC, &nSizeC);
		if (nResultC > 0) {
			if (nResultC < 256) 
			{
				szBufferC[nResultC] = '\0';
				return szBufferC;
			}
			return 0;
		}
		return 0;
	}

	void CloseClient()
	{
		freeaddrinfo(pResultC);
		closesocket(SenderC);
		WSACleanup();
	}

	void NETWORKING_API CloseReceiver()
	{
		closesocket(Receiver);
	}

}