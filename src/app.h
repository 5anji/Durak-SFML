#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

class Application {
    sf::ContextSettings settings;
    sf::VideoMode video_mode;
    uint8_t style;
    char const* title;
    char const* cards_directory;

public:
    Application(uint16_t, uint16_t);
    int8_t start(std::string&);
    ~Application();
};
