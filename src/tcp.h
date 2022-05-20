#pragma once

#include <SFML/Network.hpp>

namespace TCP {
extern sf::Mutex mutex;
extern sf::TcpSocket socket;
extern bool quit;
extern bool client_connected;

class Server {
    sf::Packet packet;

public:
    Server();
    void listen();
    void send();
    // ~Server();
};

class Client {
    sf::Packet packet;

public:
    Client();
    void listen();
    void send();
    // ~Client();
};

}  // namespace TCP
