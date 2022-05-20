#pragma once

#include <SFML/Network.hpp>

namespace TCP {
extern sf::Mutex mutex;
extern sf::TcpSocket socket;
extern bool quit;
extern bool client_connected;
extern const int port;

class Server {
    sf::Packet packet;

public:
    Server();
    void listen();
    void send();
    sf::Packet& get();
    void set(sf::Packet&);
    // ~Server();
};

class Client {
    sf::Packet packet;

public:
    Client();
    void listen();
    void send();
    sf::Packet& get();
    void set(sf::Packet&);
    // ~Client();
};

}  // namespace TCP
