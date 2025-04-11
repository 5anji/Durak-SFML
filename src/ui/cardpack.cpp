#include "cardpack.h"

#include "../rules/cards.h"

cardpack::cardpack(Card* trump_card, sf::Vector2<uint32_t> window_size) {
    card_texture.setSmooth(true);
    trump_texture.setSmooth(true);

    if (card_texture.loadFromFile("assets/cards/back.png")) {
        texture_size = card_texture.getSize();

        float ScaleX = (static_cast<float>(window_size.x - 80) / 7.5)
                       / static_cast<float>(texture_size.x);

        back_card.setTexture(card_texture);
        back_card.setScale(ScaleX, ScaleX);

        for (size_t i = 0; i < 3; i++) {
            back_card.setPosition(
                    (static_cast<float>(window_size.x - texture_size.x * ScaleX) / 7.5),
                    (static_cast<float>(window_size.y) / 2 - 10 + i * 10
                     - texture_size.y * ScaleX / 2));
            cards.push_back(back_card);
        }
    } else {
        exit(-1);
    }
    if (trump_texture.loadFromFile(trump_card->get_filename())) {
        texture_size = trump_texture.getSize();
        float ScaleX = (static_cast<float>(window_size.x - 80) / 7.5)
                       / static_cast<float>(texture_size.x);
        back_card.setTexture(trump_texture);
        back_card.setScale(ScaleX, ScaleX);
        back_card.setTexture(trump_texture);
        back_card.setRotation(90);
        back_card.setPosition(back_card.getPosition().x + texture_size.y * ScaleX + 10,
                              window_size.y / 2 - texture_size.x * ScaleX / 2);
        cards.push_front(back_card);
    } else {
        exit(-1);
    }
}

void cardpack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto&& i : cards) {
        target.draw(i, states);
    }
}
