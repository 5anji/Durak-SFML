#include "tcp.h"

#include <iostream>
namespace TCP {
sf::Mutex mutex;
sf::TcpSocket socket;
extern bool quit = false;
bool client_connected = false;
}  // namespace TCP
TCP::Server::Server() {
    // fun_ptr = &TCP::Server::listen;
}

void TCP::Server::listen() {
    std::cout << "Listening for clients." << std::endl;
    sf::TcpListener listener;
    listener.listen(50001);
    listener.accept(TCP::socket);
    std::cout << "New client connected: " << TCP::socket.getRemoteAddress() << std::endl;
    TCP::client_connected = true;

    // data

    while (!TCP::quit) {
        TCP::socket.receive(packet);

        while (!packet.endOfPacket()) {
            TCP::mutex.lock();
            packet >> "something >> must >> be >> here";

            TCP::mutex.unlock();
        }

        packet.clear();
    }
}

void TCP::Server::send() {
    if (packet.getDataSize() > 0) {
        TCP::mutex.lock();
        TCP::socket.send(packet);
        packet.clear();
        TCP::mutex.unlock();
    }
}

TCP::Client::Client() {
    // fun_ptr = &TCP::Client::listen;
}

void TCP::Client::listen() {
    // data

    while (!TCP::quit) {
        TCP::socket.receive(packet);

        while (!packet.endOfPacket()) {
            TCP::mutex.lock();
            packet >> "something >> must >> be >> here";
            TCP::mutex.unlock();
        }

        packet.clear();
    }
}

void TCP::Client::send() {
    if (packet.getDataSize() > 0) {
        TCP::mutex.lock();
        TCP::socket.send(packet);
        packet.clear();
        TCP::mutex.unlock();
    }
}