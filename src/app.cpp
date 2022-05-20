#include "app.h"

#include "tcp.h"
#include "valid_input.h"

#include <cmath>
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
    sf::Vector2<uint32_t> texture_size;
    sf::Vector2<uint32_t> window_size;
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

    sf::IpAddress serverIp;
    int packet_counter(0);
    sf::Clock PacketClock;
    std::string str_mode;

    validate_input(str_mode, serverIp);

    TCP::Server server;
    TCP::Client client;

    if (str_mode == "server") {
        std::thread server_listener(&TCP::Server::listen, &server);
        server_listener.join();
    } else {
        std::thread client_listener(&TCP::Client::listen, &client);
        TCP::socket.connect(serverIp, TCP::port);
        client_listener.join();
    }

    if (str_mode == "server") {
        while (!TCP::client_connected) {}
    }

    std::string data;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                TCP::quit = true;
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        window.display();

        if (str_mode == "server") {
            if (PacketClock.getElapsedTime().asSeconds() >= 1) {
                packet_counter = 0;
                PacketClock.restart();
            } else if ((PacketClock.getElapsedTime().asMilliseconds() / 33) > packet_counter) {
                server.get() << data;
                server.send();
                std::cout << data + "_" + str_mode;

                packet_counter++;
            }
        } else {
            if (PacketClock.getElapsedTime().asSeconds() >= 1) {
                packet_counter = 0;
                PacketClock.restart();
            } else if ((PacketClock.getElapsedTime().asMilliseconds() / 33) > packet_counter) {
                client.get() << data;
                client.send();
                std::cout << data + "_" + str_mode;
                packet_counter++;
            }
        }
    }

    return 0;
}

// Destroying the object
Application::~Application() {
    std::cout << "Exited the app" << std::endl;
}