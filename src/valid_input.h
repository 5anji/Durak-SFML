#pragma once
#include <SFML/Network.hpp>
#include <iostream>

void validate_input(std::string& mode, sf::IpAddress& serverIp) {
    char input(0);

    while (!(tolower(input) == 'c' || tolower(input) == 's')) {
        std::cout << "[S]erver or [C]lient?\n";
        std::cin >> input;

        if (!(tolower(input) == 'c' || tolower(input) == 's')) {
            std::cout << "Invalid." << std::endl;
        } else {
            if (tolower(input) == 'c') {
                mode = "client";
                do {
                    std::cout << "Type the IPv4 address or name of the server to connect to: ";
                    std::cin >> serverIp;
                } while (serverIp == sf::IpAddress::None);
            }

            if (tolower(input) == 's') {
                mode = "server";
            }
            break;
        }
    }

    std::cout << "Selected input: " << mode << std::endl;
}