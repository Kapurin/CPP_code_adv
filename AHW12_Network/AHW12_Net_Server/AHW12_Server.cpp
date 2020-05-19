#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 2
#define DEFAULT_PORT "12345"

int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    std::string msg_str = "";

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        system("pause");
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        system("pause");
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        system("pause");
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        system("pause");
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        system("pause");
        return 1;
    }


    // Accept a client socket
    printf("Wait connecting client...\n");
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        system("pause");
        return 1;
    }
    else
        printf("Client connected!\n");

    // No longer need server socket
    closesocket(ListenSocket);


    // ПРИЕМ СООБЩЕНИЯ ОТ КЛИЕНТА
    // Receive until the peer shuts down the connection
    do {
        ZeroMemory(recvbuf, sizeof(recvbuf));
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            for (int i = 0; i < iResult; i++)
                msg_str += recvbuf[i];
        }
        else if (iResult == 0)
            printf("Receive message is over.\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            system("pause");
            return 1;
        }
    } while (iResult > 0);

    // ВЫВОД ПРИНЯТОГО СООБЩЕНИЯ ОТ КЛИЕНТА
    std::cout << "Message received from client: " << msg_str << std::endl;

    // ВВОД СООБЩЕНИЯ ОТ ПОЛЬЗОВАТЕЛЯ
    do
    {
        printf("Enter message to client: ");
        std::cin >> msg_str;
        if (msg_str.size() < 10)
            printf("\nEnter message large then 10 symbols! Try again!\n\n");
    } while (msg_str.size() < 10);


    // ОТПРАВКА СООБЩЕНИЯ КЛИЕНТУ
    // Send an initial buffer
    iSendResult = send(ClientSocket, msg_str.c_str(), static_cast<int>(msg_str.size()), 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        system("pause");
        return 1;
    }
    else if (iSendResult > 0)
    {
        printf("Bytes sent: %d\n", iSendResult);
        printf("Connection closed.\n");
    }

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        system("pause");
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    system("pause");
    return 0;
}