#include "image_button.h"

ImageButton::ImageButton(Card* card,
                         sf::Vector2<uint32_t> window_size,
                         sf::Vector2<float> position)
        : position(position) {
    texture.setSmooth(true);
    if (texture.loadFromFile(card->get_filename())) {
        sf::Vector2<uint32_t> texture_size(texture.getSize());
        float ScaleX = (static_cast<float>(window_size.x - 80) / 7.5)
                       / static_cast<float>(texture_size.x);
        image = std::make_unique<sf::Sprite>(texture);
        image->setScale({ScaleX, ScaleX});
        image->setTexture(texture);
        image->setPosition(position);
        clickable.setFillColor(sf::Color(0, 0, 0, 0));
        clickable.setPosition(position);
        clickable.setSize(sf::Vector2f(texture_size.x * ScaleX, texture_size.y * ScaleX));
    } else {
        exit(-1);
    }
}

void ImageButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*image, states);
    target.draw(clickable, states);
}
