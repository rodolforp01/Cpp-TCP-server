// TCP IP server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

int main()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        std::cerr << "Cant initialize winsock! Quitting" << std::endl;

    }

    //create the socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        std::cerr << "Cant create a socket! Quitting" << std::endl;
        return -1;
    }
    
    //bind the socket to an ip address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(1320); //port
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    //tell winsock the socket is for listening
    listen(listening, SOMAXCONN);

    //wait for a connection
    sockaddr_in client;
    int clientSize = sizeof(client);



    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == INVALID_SOCKET)
        std::cerr << "Client socket error" << std::endl;

    char host[NI_MAXHOST];          //clients remote name
    char service[NI_MAXHOST];       //service (i.e port) the client connected on

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
        std::cout << host << " Connected on port " << service << std::endl;
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }

    //close listening socket
    closesocket(listening);

    //while loop: accept and echo message back to client
    char buf[4096];

    //data 
    char ok[]
    {
        0x01, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x7c, 0x5c, 0x43, 0x27, 0x04, 0x19, 0x04, 0x2a, 0x3f, 0x3f, 0x3f, 0x22, 0x3f, 0x3f, 0x3f, 0x22, 0x40, 0x3f, 0x3f, 0x22, 0x3f, 0x3f, 0x51, 0x14, 0x04, 0x3f, 0x3f, 0x51, 0x14, 0x04, 0x0c, 0x3f, 0x3f, 0x3f, 0x3f, 0x6e, 0x3f, 0x3f, 0x6e, 0x40, 0x07, 0x44, 0x03, 0x04, 0x3f, 0x3f, 0x51, 0x14, 0x04, 0x04, 0x3f, 0x43, 0x3f, 0x55, 0x3f, 0x13, 0x7c, 0x31, 0x7c, 0x46, 0x61, 0x6c, 0x73, 0x65, 0x7c, 0x7c, 0x54, 0x72, 0x75, 0x65, 0x7c, 0x54, 0x72, 0x75, 0x65, 0x7c, 0x32, 0x44, 0x36, 0x30, 0x33, 0x43, 0x32, 0x35, 0x37, 0x35, 0x34, 0x35, 0x35, 0x32, 0x32, 0x35, 0x35, 0x31, 0x37, 0x32, 0x32, 0x33, 0x33, 0x36, 0x36, 0x42, 0x32, 0x32, 0x34, 0x42, 0x33, 0x35, 0x33, 0x46, 0x32, 0x33, 0x32, 0x37, 0x32, 0x41, 0x34, 0x38, 0x32, 0x36, 0x33, 0x38, 0x33, 0x39, 0x33, 0x42, 0x33, 0x37, 0x32, 0x35, 0x7c, 0x3e, 0x10, 0x27, 0x63, 0x36, 0x31, 0x30, 0x63, 0x31, 0x30, 0x65, 0x31, 0x39, 0x65, 0x32, 0x30, 0x34, 0x39, 0x35, 0x30, 0x37, 0x66, 0x65, 0x37, 0x36, 0x30, 0x65, 0x62, 0x01, 0x7c
    };

    while (true)
    { 
        //wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived > 0)
        {
            send(clientSocket, ok, sizeof(ok), 0);
            return -1;
        }
        else
            std::cout << "Error Receiving bytes.";

        //echo message back to client
    }

    closesocket(clientSocket);

    WSACleanup();
   
    return 0;
}

