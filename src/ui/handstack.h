#pragma once

#include "../rules/cards.h"
#include "../ui/image_button.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class handstack : public sf::Drawable {
    std::vector<Button_With_Image> cards;
    uint8_t limit_set_by_rules;
    sf::Vector2<uint32_t> window_size;

public:
    handstack(uint8_t, sf::Vector2<uint32_t>);
    void operator+=(const Card&);
    Button_With_Image operator[](uint8_t);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};