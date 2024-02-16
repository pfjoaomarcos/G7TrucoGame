#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <queue>

class ServerSocket
{
private:
    struct ClientData
    {
        int client_socket;
        struct sockaddr_in address;
    };

    std::vector<ClientData> clients_data;

    std::queue<char*> clients_messages;

    void accept_connections(SOCKET server_socket);

    void receive_data(SOCKET client_socket);

    void send_message_to_clients(char* message);

    //TODO implemente get message

public:
    ServerSocket();

    bool start_server();
};

#endif // SERVERSOCKET_H
