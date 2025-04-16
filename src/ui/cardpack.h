#pragma once
#include "../rules/cards.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class CardPack : public sf::Drawable {
    std::list<sf::Sprite> cards;
    sf::Vector2<uint32_t> texture_size;
    sf::Texture card_texture, trump_texture;

public:
    CardPack(Card*, sf::Vector2<uint32_t>);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};
