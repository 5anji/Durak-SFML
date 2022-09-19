#include "app.h"

#include "rules/cards.h"
#include "server/tcp.h"
#include "ui/cardpack.h"
#include "ui/image_button.h"

#include <cmath>
#include <csignal>
#include <functional>
#include <random>
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

    // send unique seed for card pack generation
    std::random_device* generator = new std::random_device();
    std::uniform_int_distribution<uint8_t>* distribution = new std::uniform_int_distribution<uint8_t>(0, 3);
    Cards* main_card_pack;

    if (mode == "server") {
        std::random_device r;
        uint32_t seed = r();
        uint8_t trump = (*distribution)(*generator);
        main_card_pack = new Cards(trump, seed);
        sf::Packet send_packet;
        send_packet << seed << trump;
        sf::TcpListener listener;
        listener.listen(55001);
        sf::TcpSocket socket;
        listener.accept(socket);
        socket.send(send_packet);
    } else {
        sf::Packet receive_packet;
        sf::TcpSocket socket;
        socket.connect(TCP::serverIp, 55001);
        socket.receive(receive_packet);
        uint32_t seed;
        uint8_t trump;
        receive_packet >> seed >> trump;
        main_card_pack = new Cards(trump, seed);
        socket.disconnect();
    }
    delete distribution;
    delete generator;
    // end sending

    cardpack side_card_pack(&(*main_card_pack)[35], window.getSize());
    Button_With_Image temp(&(*main_card_pack)[0], window.getSize(), sf::Vector2f{350, 370});

    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            switch (Event.type) {
            case sf::Event::Closed: {
                TCP::quit = true;
                TCP_Listener->terminate();
                delete TCP_Listener;
                window.close();
            } break;
            case sf::Event::MouseMoved: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (temp.clickable.getGlobalBounds().contains(mousePosF)) {
                    temp.clickable.setFillColor(sf::Color(255, 255, 0, 63.f));
                } else {
                    temp.clickable.setFillColor(sf::Color(0, 0, 0, 0));
                }

            } break;
            case sf::Event::MouseButtonPressed: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (temp.clickable.getGlobalBounds().contains(mousePosF)) {
                    std::cout << "Clicked" << std::endl
                              << std::flush;
                }

            } break;
            default:
                break;
            }
        }
        if (mode == "server") {
            if (PacketClock.getElapsedTime().asSeconds() >= 1) {
                packet_counter = 0;
                PacketClock.restart();
            } else if ((PacketClock.getElapsedTime().asMilliseconds() / 33) > packet_counter) {
                // now = ::time(0);
                // dt = ctime(&now);

                // TCP::serverPacket << main_card_pack;
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

        window.clear();
        window.draw(background);
        window.draw(side_card_pack);
        window.draw(temp);
        window.display();

        time = Clock.restart();
    }

    return 0;
}

// Destroying the object
Application::~Application() {
    std::cout << "Exited the app" << std::endl;
}