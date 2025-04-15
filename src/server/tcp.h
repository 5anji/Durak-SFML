#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

namespace TCP {
sf::IpAddress serverIp;
int const port = 50001;

sf::TcpSocket socket;

sf::Mutex globalMutex;
sf::Packet serverPacket;
sf::Packet clientPacket;
std::string dt;
bool quit = false;
bool connected = false;

inline void listen(bool quit,
                   sf::Packet& packet,
                   sf::Mutex& mutex,
                   sf::TcpSocket& socket,
                   std::string& dt) {
    while (!quit) {
        socket.receive(packet);

        while (!packet.endOfPacket()) {
            mutex.lock();
            packet >> dt;
            std::cout << dt;
            mutex.unlock();
        }

        packet.clear();
    }
}

inline void send(sf::Packet& packet, sf::Mutex& mutex, sf::TcpSocket& socket) {
    if (packet.getDataSize() > 0) {
        mutex.lock();
        socket.send(packet);
        packet.clear();
        mutex.unlock();
    }
}

void ServerListener() {
    std::cout << "Listening for clients." << std::endl;
    sf::TcpListener listener;
    listener.listen(port);
    listener.accept(socket);
    std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
    connected = true;

    listen(quit, clientPacket, globalMutex, socket, dt);
}

void ClientListener() {
    listen(quit, serverPacket, globalMutex, socket, dt);
}

void ServerSend() {
    send(serverPacket, globalMutex, socket);
}

void ClientSend() {
    send(clientPacket, globalMutex, socket);
}
}  // namespace TCP
