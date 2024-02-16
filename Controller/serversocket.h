#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <WS2tcpip.h>
#include <thread>
#include <vector>

class ServerSocket
{
private:
    struct ClientData
    {
        int client_socket;
        struct sockaddr_in address;
    };

    std::vector<ClientData> clients_data;

    void accept_connections(SOCKET server_socket);

    void receive_data(SOCKET client_socket);

public:
    ServerSocket();

    bool start_server();
};

#endif // SERVERSOCKET_H
