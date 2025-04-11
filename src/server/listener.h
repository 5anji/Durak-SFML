#pragma once

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
