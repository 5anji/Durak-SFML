#pragma once

inline void send(sf::Packet& packet, sf::Mutex& mutex, sf::TcpSocket& socket) {
    if (packet.getDataSize() > 0) {
        mutex.lock();
        socket.send(packet);
        packet.clear();
        mutex.unlock();
    }
}