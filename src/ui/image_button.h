#pragma once

#include "../rules/cards.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Button_With_Image : public sf::Drawable {
    sf::Vector2<float> position;
    sf::Texture texture;

public:
    std::unique_ptr<sf::Sprite> image;
    sf::RectangleShape clickable;

    Button_With_Image(Card*, sf::Vector2<uint32_t>, sf::Vector2<float>);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};
