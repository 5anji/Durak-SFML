#include "app.h"

#include "tcp.h"
#include <cmath>
#include <fstream>
#include <functional>
#include <thread>

// Creating the object
Application::Application(uint16_t width, uint16_t height)
        : video_mode(width, height)
        , style(sf::Style::Close)
        , title("Durak-SFML")
        , cards_directory("assets/cards/") {
    settings.antialiasingLevel = 4;
}

// Starting the main window
int8_t Application::start() {
    sf::RenderWindow window(video_mode, title, style, settings);
    window.setFramerateLimit(48);
    window.setPosition(sf::Vector2<int>(20, 40));

    // scale backround
    sf::Vector2<unsigned int> texture_size;
    sf::Vector2<unsigned int> window_size;
    sf::Texture texture;

    texture.setSmooth(true);
    sf::Sprite background;

    if (texture.loadFromFile("assets/background.jpg")) {
        texture_size = texture.getSize();
        window_size = window.getSize();

        float ScaleX = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
        float ScaleY = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);

        background.setTexture(texture);
        background.setScale(ScaleX, ScaleY);
    } else {
        return -1;
    }
    // end scaling

    char mode = 'n';
    sf::IpAddress serverIp;

    std::string str_mode;

    while (!(mode == 'C' || mode == 'S' || mode == 'c' || mode == 's')) {
        std::cout << "[S]erver or [C]lient?\n";
        std::cin >> mode;

        if (!(mode == 'C' || mode == 'S' || mode == 'c' || mode == 's')) {
            std::cout << "Invalid." << std::endl;
        }
    }
    if (mode == 'C' || mode == 'c') {
        str_mode = "client";
        do {
            std::cout << "Type the address or name of the server to connect to: ";
            std::cin >> serverIp;
        } while (serverIp == sf::IpAddress::None);
    }
    if (mode == 'S' || mode == 's') {
        str_mode = "server";
    }
    while (!(mode == 'C' || mode == 'S' || mode == 'c' || mode == 's')) {
        std::cout << "[S]erver or [C]lient?\n";
        std::cin >> mode;

        if (!(mode == 'C' || mode == 'S' || mode == 'c' || mode == 's')) {
            std::cout << "Invalid." << std::endl;
        }
    }

    std::cout << "Selected mode: " << str_mode << std::endl;

    // std::function<void(TCP::Server&)> listen_server = &TCP::Server::listen;
    // std::function<void(TCP::Client&)> listen_client = &TCP::Client::listen;

    TCP::Server listen_server;
    TCP::Client listen_client;
    std::thread server(&TCP::Server::listen, &listen_server);
    std::thread client(&TCP::Client::listen, &listen_client);

    server.join();
    client.join();

    // sf::Thread TCPserverListenerThread(&listen_server);
    // sf::Thread TCPclientListenerThread(&listen_client);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}

// Destroying the object
Application::~Application() {
    std::cout << "Exited the app" << std::endl;
}