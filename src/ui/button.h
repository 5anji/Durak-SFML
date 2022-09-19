#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
    
    sf::Vector2<float> size;
    sf::Vector2<float> position;
    sf::Font font;

public:
    sf::RectangleShape button;
    sf::RectangleShape overlay;
    sf::Text text;

    Button(sf::Vector2<float>,
           sf::Vector2<float>,
           sf::Font&,
           const char*,
           sf::Color,
           sf::Color,
           sf::Color,
           const int);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};