#include "app.h"

#include "rules/cards.h"
#include "ui/cardpack.h"
// #include "ui/handstack.h"
#include "ui/image_button.h"

#include <spdlog/spdlog.h>

#include <cmath>
#include <csignal>
#include <functional>
#include <random>
#include <thread>

// Creating the object
Application::Application(uint16_t width, uint16_t height)
        : video_mode({width, height})
        , style(sf::Style::Close)
        , title("Durak-SFML")
        , cards_directory("assets/cards/") {
    settings.antiAliasingLevel = 4;
}

// Starting the main window
int8_t Application::start() {
    sf::RenderWindow window(video_mode,
                            std::string(title),
                            style,
                            sf::State::Windowed,
                            settings);
    window.setFramerateLimit(48);
    window.setPosition(sf::Vector2<int>(20, 40));

    // scale backround
    sf::Vector2<uint32_t> texture_size;
    sf::Vector2<uint32_t> window_size;
    sf::Texture texture;

    texture.setSmooth(true);
    std::unique_ptr<sf::Sprite> background;

    if (texture.loadFromFile("assets/background.jpg")) {
        texture_size = texture.getSize();
        window_size = window.getSize();

        float ScaleX =
                static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
        float ScaleY =
                static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);

        background = std::make_unique<sf::Sprite>(texture);
        background->setScale({ScaleX, ScaleY});
    } else {
        return -1;
    }
    // end scaling

    // send unique seed for card pack generation
    std::random_device generator;
    std::uniform_int_distribution<uint8_t> distribution(0, 3);
    uint8_t trump = distribution(generator);

    std::random_device r;
    uint32_t seed = r();
    std::unique_ptr<Cards> main_card_pack = std::make_unique<Cards>(trump, seed);

    CardPack side_card_pack(&(*main_card_pack)[35], window.getSize());
    ImageButton temp(&(*main_card_pack)[0], window.getSize(), sf::Vector2f{350, 370});
    // handstack temp(6, window_size);

    while (window.isOpen()) {
        std::optional<sf::Event> event;
        while ((event = window.pollEvent())) {
            event->visit([&](auto const& e) {
                using T = std::decay_t<decltype(e)>;

                if constexpr (std::is_same_v<T, sf::Event::Closed>) {
                    window.close();
                } else if constexpr (std::is_same_v<T, sf::Event::MouseMoved>) {
                    sf::Vector2i mousePos = e.position;
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                                           static_cast<float>(mousePos.y));
                    if (temp.clickable.getGlobalBounds().contains(mousePosF)) {
                        temp.clickable.setFillColor(sf::Color(255, 255, 0, 63.f));
                    } else {
                        temp.clickable.setFillColor(sf::Color(0, 0, 0, 0));
                    }
                } else if constexpr (std::is_same_v<T, sf::Event::MouseButtonPressed>) {
                    sf::Vector2i mousePos = e.position;
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                                           static_cast<float>(mousePos.y));
                    if (temp.clickable.getGlobalBounds().contains(mousePosF)) {
                        spdlog::info("Clicked");
                    }
                }
            });
        }

        window.clear();
        window.draw(*background);
        window.draw(side_card_pack);
        window.draw(temp);
        window.display();
    }

    return 0;
}

// Destroying the object
Application::~Application() {
    std::cout << "Exited the app" << std::endl;
}
