#pragma once
#include "listener.h"
#include "sender.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

namespace TCP {
sf::IpAddress serverIp;
const int port = 50001;

sf::TcpSocket socket;

sf::Mutex globalMutex;
sf::Packet serverPacket;
sf::Packet clientPacket;
std::string dt;
bool quit = false;
bool connected = false;

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
