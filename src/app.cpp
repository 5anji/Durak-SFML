#include "app.h"

#include "cards.h"
#include "tcp.h"
#include "ui/cardpack.h"

#include <cmath>
#include <csignal>
#include <functional>
#include <thread>

namespace {
std::function<void(int)> shutdown_handler;
void signalHandler(int n) { shutdown_handler(n); }
}  // namespace

// Creating the object
Application::Application(uint16_t width, uint16_t height)
        : video_mode(width, height)
        , style(sf::Style::Close)
        , title("Durak-SFML")
        , cards_directory("assets/cards/") {
    settings.antialiasingLevel = 4;
}

// Starting the main window
int8_t Application::start(std::string& mode, sf::IpAddress& serverIp) {
    TCP::serverIp = serverIp;
    sf::Thread* TCP_Listener;
    sf::Clock Clock;
    sf::Clock PacketClock;
    int packet_counter = 0;
    sf::Time time;
    std::string command = "";

    if (mode == "server") {
        TCP_Listener = new sf::Thread(&TCP::ServerListener);
    } else {
        TCP_Listener = new sf::Thread(&TCP::ClientListener);
        TCP::socket.connect(TCP::serverIp, TCP::port);
    }

    TCP_Listener->launch();

    signal(SIGINT, signalHandler);

    shutdown_handler = [&](int n) {
        if (n == 2) {
            TCP::quit = true;

            TCP_Listener->terminate();
            delete TCP_Listener;
            std::cout << std::endl
                      << "Terminated threads" << std::endl;
            this->~Application();
            exit(n);
        }
    };

    if (mode == "server") {
        while (!TCP::connected) {}
    }

    Cards it(1);
    time_t now;
    std::string dt;

    sf::RenderWindow window(video_mode, std::string(title) + " [" + mode + "]", style, settings);
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

    // sf::Texture card;
    // card.loadFromFile(it[1].get_filename());
    // sf::Sprite c;
    // c.setTexture(card);
    // c.setPosition(30, 30);
    const cardpack test(it[35], window.getSize());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                TCP::quit = true;
                TCP_Listener->terminate();
                delete TCP_Listener;
                window.close();
            }
        }
        // if (mode == "server") {
        // } else {
        // }

        window.clear();
        window.draw(background);
        window.draw(test);
        window.display();

        if (mode == "server") {
            if (PacketClock.getElapsedTime().asSeconds() >= 1) {
                packet_counter = 0;
                PacketClock.restart();
            } else if ((PacketClock.getElapsedTime().asMilliseconds() / 33) > packet_counter) {
                now = ::time(0);
                dt = ctime(&now);

                TCP::serverPacket << dt;
                TCP::ServerSend();

                packet_counter++;
            }
        } else {
            if (PacketClock.getElapsedTime().asSeconds() >= 1) {
                packet_counter = 0;
                PacketClock.restart();
            } else if ((PacketClock.getElapsedTime().asMilliseconds() / 33) > packet_counter) {
                // TCP::clientPacket << ' ';
                // TCP::ClientSend();
                packet_counter++;
            }
        }

        time = Clock.restart();
    }
    return 0;
}

// Destroying the object
Application::~Application() {
    std::cout << "Exited the app" << std::endl;
}