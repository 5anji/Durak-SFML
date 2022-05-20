#include "tcp.h"

#include <iostream>

namespace TCP {
sf::Mutex mutex;
sf::TcpSocket socket;
bool quit = false;
bool client_connected = false;
const int port = 50001;
}  // namespace TCP

TCP::Server::Server() {
    // fun_ptr = &TCP::Server::listen;
}

void TCP::Server::listen() {
    std::cout << "Listening for clients." << std::endl;
    sf::TcpListener listener;
    listener.listen(port);
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

sf::Packet& TCP::Server::get() {
    return packet;
}

void TCP::Server::set(sf::Packet& copy) {
    packet = copy;
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


sf::Packet& TCP::Client::get() {
    return packet;
}

void TCP::Client::set(sf::Packet& copy) {
    packet = copy;
}