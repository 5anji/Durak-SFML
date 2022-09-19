#include "button.h"

Button::Button(
        sf::Vector2<float> size,
        sf::Vector2<float> position,
        sf::Font& font,
        const char* string,
        sf::Color button_color,
        sf::Color overlay_color,
        sf::Color text_color,
        const int font_size)
        : size(size)
        , position(position)
        , font(font) {

    button.setSize(size);
    overlay.setSize(size);
    button.setPosition(position);
    overlay.setPosition(position);
    button.setFillColor(button_color);
    overlay.setFillColor(overlay_color);

    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setString(string);
    text.setFillColor(text_color);
    text.setCharacterSize(font_size);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    text.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(button, states);
    target.draw(overlay, states);
    target.draw(text, states);
}