#pragma once
#include "../cards.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Button_With_Image : public sf::Drawable {
    sf::Vector2<float> position;
    sf::Texture texture;

public:
    sf::Sprite image;
    sf::RectangleShape clickable;

    Button_With_Image(Card* card, sf::Vector2<uint32_t> window_size, sf::Vector2<float> position)
            : position(position) {
        texture.setSmooth(true);
        if (texture.loadFromFile(card->get_filename())) {
            sf::Vector2<uint32_t> texture_size(texture.getSize());
            float ScaleX = (static_cast<float>(window_size.x - 80) / 7.5) / static_cast<float>(texture_size.x);
            image.setTexture(texture);
            image.setScale(ScaleX, ScaleX);
            image.setTexture(texture);
            image.setPosition(position);
            clickable.setFillColor(sf::Color(0, 0, 0, 0));;
            clickable.setPosition(position);
            clickable.setSize(sf::Vector2f(texture_size.x * ScaleX, texture_size.y * ScaleX));
        } else {
            exit(-1);
        }
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(image, states);
        target.draw(clickable, states);
    }
};