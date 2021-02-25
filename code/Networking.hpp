
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

#pragma once

#ifdef NETWORKINGDLL_EXPORTS
#define NETWORKING_API __declspec(dllexport)
#else
#define NETWORKING_API __declspec(dllimport)
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>


#pragma comment(lib,"WS2_32")

using namespace std;

#define WIN32_LEAN_AND_MEAN


#define SERVER  "127.0.0.1"
#define PORT    "1000"

extern "C"
{
	//Server
 
	struct sockaddr_in Sender;
	int nSize = sizeof(Sender);
	char szBuffer[256];
	int nResult;
	SOCKET  Receiver;

	NETWORKING_API int  SetUpReceiver();	
	NETWORKING_API const char*  RecieveMessage();
	NETWORKING_API int SendMessageToClient(char* buffer);
	NETWORKING_API void  CloseReceiver();


	//Client

	struct sockaddr_in ReceiverC;
	int nSizeC = sizeof(ReceiverC);
	char szBufferC[256];
	int nResultC;
	SOCKET  SenderC;
	struct addrinfo* pResultC;

	NETWORKING_API int  SetUpClient();
	NETWORKING_API int SendMessageToServer(char* buffer);
	NETWORKING_API const char* RecieveMessageFromServer();
	NETWORKING_API void  CloseClient();
}