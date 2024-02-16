#include "ClientSocket.h"

ClientSocket::ClientSocket() {}

bool ClientSocket::connect_to_server(PCSTR ip, PCSTR port)
{
    // Inicializa o Winsock
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

    // Resolve o ip e porta a ser usado pelo server
    iResult = getaddrinfo(ip, port, &hints, &result);
    if (iResult != 0)
    {
        return false;
    }

    // Cria o socket para conectar ao server
    SOCKET server_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (server_socket == INVALID_SOCKET)
    {
        freeaddrinfo(result);
        return false;
    }

    _server_socket = server_socket;

    // Connecta ao server
    iResult = connect(server_socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(server_socket);
        freeaddrinfo(result);
        return false;
    }

    freeaddrinfo(result);

    // Cria uma thread para ficar recebendo dados
    std::thread(&ClientSocket::receive_data, this, server_socket).detach();

    return true;
}

// Recebe as mensagens do server e adiciona a uma fila
void ClientSocket::receive_data(SOCKET client_socket)
{
    char buffer[1024];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        int  amountReceived = recv(client_socket, buffer, sizeof(buffer), 0);

        if (amountReceived <= 0)
            break;

        _mtx_server_messages.lock();

        char* buffer_copy = (char*)malloc(strlen(buffer) + 1);
        memset(buffer_copy, 0, sizeof(buffer_copy));
        strncpy (buffer_copy, buffer, sizeof(buffer_copy));
        server_messages.push(buffer_copy);

        _mtx_server_messages.unlock();
    }

    closesocket(client_socket);
}

// Manda mensagem para o server
void ClientSocket::send_message(char* message)
{
    send(_server_socket, message, strlen(message), 0);
}

// Pega a primeira mensagem da fila onde se acumula as mensagens recebidas do server
char* ClientSocket::get_message_from_queue()
{
    _mtx_server_messages.lock();

    if (server_messages.empty())
    {
        _mtx_server_messages.unlock();
        return nullptr;
    }

    char* message = server_messages.front();
    server_messages.pop();

    _mtx_server_messages.unlock();

    return message;
}
