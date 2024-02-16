#include "serversocket.h"

ServerSocket::ServerSocket() {}

bool ServerSocket::start_server()
{
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult == INVALID_SOCKET)
    {
        return false;
    }

    struct addrinfo* result = NULL, * ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    PCSTR ip = "127.0.0.1";
    PCSTR port = "1";

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(ip, port, &hints, &result);
    if (iResult != 0)
    {
        return false;
    }

    // Create a SOCKET for the server to listen for client connections
    SOCKET server_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (server_socket == INVALID_SOCKET)
    {
        return false;
    }

    // Setup the TCP listening socket
    iResult = bind(server_socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        return false;
    }

    freeaddrinfo(result);

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        return false;
    }

    std::thread(&ServerSocket::accept_connections, this, server_socket).detach();

    return true;
}

void ServerSocket::accept_connections(SOCKET server_socket)
{
    while (true)
    {
        SOCKET client_socket = INVALID_SOCKET;
        struct sockaddr_in  client_address;
        int clientAddressSize = sizeof(struct sockaddr_in);

        // Accept a client socket
        client_socket = accept(server_socket, (sockaddr*)&client_address, &clientAddressSize);
        if (client_socket == INVALID_SOCKET)
        {
            continue;
        }

        struct ClientData* clientData = (ClientData*)malloc(sizeof(struct ClientData));
        clientData->address = client_address;
        clientData->client_socket = client_socket;

        clients_data.push_back(*clientData);

        std::thread(&ServerSocket::receive_data, this, client_socket).detach();
    }
}

void ServerSocket::receive_data(SOCKET client_socket)
{
    char buffer[1024];

    while (true)
    {
        int  amountReceived = recv(client_socket, buffer, 1023, 0);

        if (amountReceived > 0)
        {
            buffer[amountReceived] = 0;

            /*wchar_t wtext[1024];
                mbstowcs_s(wtext, buffer, strlen(buffer) + 1);
                OutputDebugString(wtext);*/

            //                size_t size = strlen(buffer) + 1;
            //                wchar_t* portName = new wchar_t[size];
            //                size_t outSize;
            //                mbstowcs_s(&outSize, portName, size, buffer, size - 1);
            //OutputDebugString(portName);


            //sendReceivedMessageToTheOtherClients(buffer, socketFD);
            send(client_socket, buffer, amountReceived, 0);
        }

        if (amountReceived == 0)
            break;
    }

    closesocket(client_socket);
}
