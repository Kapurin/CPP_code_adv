#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 2
#define DEFAULT_PORT "12345"

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test this is a test this is a test this is a test this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
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
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        system("pause");
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            system("pause");
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        system("pause");
        return 1;
    }
    else
        printf("Connected!\n");


    // ВВОД СООБЩЕНИЯ ОТ ПОЛЬЗОВАТЕЛЯ
    do
    {
        printf("Enter message to server: ");
        std::cin >> msg_str;
        if (msg_str.size() < 10)
            printf("\nEnter message large then 10 symbols! Try again!\n");
    } while (msg_str.size() < 10);


    // ОТПРАВКА СООБЩЕНИЯ СЕРВЕРУ
    // Send an initial buffer
    iResult = send(ConnectSocket, msg_str.c_str(), static_cast<int>(msg_str.size()), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        system("pause");
        return 1;
    }
    printf("Bytes sent: %ld\n", iResult);


    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        system("pause");
        return 1;
    }

    msg_str = "";   // очистка строки

    // ПРИЕМ СООБЩЕНИЯ ОТ СЕРВЕРА
    // Receive until the peer closes the connection
    do {
        ZeroMemory(recvbuf, sizeof(recvbuf));
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            for (int i = 0; i < iResult; i++)
                msg_str += recvbuf[i];
        else if (iResult == 0)
            printf("Receive message is over.\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
    } while (iResult > 0);

    // ВЫВОД ПРИНЯТОГО СООБЩЕНИЯ ОТ СЕРВЕРА
    std::cout << "Message received from server: " << msg_str << std::endl;
    printf("Connection closed.\n");

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    system("pause");
    return 0;
}