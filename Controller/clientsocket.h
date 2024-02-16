#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <WS2tcpip.h>
#include <thread>
#include <mutex>
#include <queue>

class ClientSocket
{
private:
    std::queue<char*> server_messages;

    std::mutex _mtx_server_messages;

    SOCKET _server_socket;

    void receive_data(SOCKET server_socket);
public:
    ClientSocket();

    bool connect_to_server(PCSTR ip = "127.0.0.1", PCSTR port = "1");

    void send_message(char* message);

    char* get_message_from_queue();
};

#endif // CLIENTSOCKET_H
