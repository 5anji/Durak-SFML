#include "app.h"

#include <cmath>
#include <fstream>

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

    sf::Vector2<unsigned int> TextureSize;
    sf::Vector2<unsigned int> WindowSize;
    sf::Texture texture;

    texture.setSmooth(true);
    sf::Sprite background;

    if (texture.loadFromFile("assets/background.jpg")) {
        TextureSize = texture.getSize();
        WindowSize = window.getSize();

        float ScaleX = static_cast<float>(WindowSize.x) / static_cast<float>(TextureSize.x);
        float ScaleY = static_cast<float>(WindowSize.y) / static_cast<float>(TextureSize.y);

        background.setTexture(texture);
        background.setScale(ScaleX, ScaleY);
    } else {
        return -1;
    }

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