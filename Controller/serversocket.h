#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <queue>
#include <cstring>
#include <mutex>

class ServerSocket
{
private:
    struct ClientData
    {
        int client_socket;
        struct sockaddr_in address;
    };

    std::vector<ClientData> clients_data;

    std::mutex _mtx_clients_data;

    std::queue<char*> clients_messages;

    std::mutex _mtx_clients_messages;

    void accept_connections(SOCKET server_socket);

    void receive_data(SOCKET client_socket);

    //TODO implemente get message

public:
    ServerSocket();

    bool start_server();

    void send_message_to_clients(char* message);

    void send_message_to_a_client(char* message, SOCKET client_socket);

    char* get_message_from_queue();
};

#endif // SERVERSOCKET_H
