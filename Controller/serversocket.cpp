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

    //TODO
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

        _mtx_clients_data.lock();
        clients_data.push_back(*clientData);
        _mtx_clients_data.unlock();

        std::thread(&ServerSocket::receive_data, this, client_socket).detach();
    }
}

void ServerSocket::receive_data(SOCKET client_socket)
{
    char buffer[1024];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        int  amountReceived = recv(client_socket, buffer, sizeof(buffer), 0);

        if (amountReceived <= 0)
            break;

        _mtx_clients_messages.lock();

        char* buffer_copy = (char*)malloc(strlen(buffer) + 1);
        memset(buffer_copy, 0, sizeof(buffer_copy));
        strncpy (buffer_copy, buffer, sizeof(buffer_copy));
        clients_messages.push(buffer_copy);

        _mtx_clients_messages.unlock();
    }

    closesocket(client_socket);
}

void ServerSocket::send_message_to_clients(char* message)
{
    for (ClientData& client : clients_data)
    {
        send(client.client_socket, message, strlen(message), 0);
    }
}

void ServerSocket::send_message_to_a_client(char* message, SOCKET client_socket)
{
    send(client_socket, message, strlen(message), 0);
}

char* ServerSocket::get_message_from_queue()
{
    _mtx_clients_messages.lock();

    if (clients_messages.empty())
    {
        _mtx_clients_messages.unlock();
        return nullptr;
    }

    char* message = clients_messages.front();
    clients_messages.pop();

    _mtx_clients_messages.unlock();

    return message;
}
