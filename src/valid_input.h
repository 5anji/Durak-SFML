#pragma once
#include <SFML/Network.hpp>
#include <iostream>

void validate_input(std::string& mode, sf::IpAddress& serverIp, bool mode_check, bool ip_check) {
    if (!mode_check) {
        char input(0);
    input_loop:
        std::cout << "[S]erver or [C]lient?\n";
        std::cin >> input;

        if (!(tolower(input) == 'c' || tolower(input) == 's')) {
            std::cout << "Invalid." << std::endl;
            goto input_loop;
        } else {
            if (tolower(input) == 'c') {
                mode = "client";
                if (!ip_check) {
                    do {
                        std::cout << "Type the IPv4 address or name of the server to connect to: ";
                        std::cin >> serverIp;
                    } while (serverIp == sf::IpAddress::None);
                }
            }
        }

        if (tolower(input) == 's') {
            mode = "server";
        }
    } else {
        if (mode == "client") {
            if (!ip_check) {
                do {
                    std::cout << "Type the IPv4 address or name of the server to connect to: ";
                    std::cin >> serverIp;
                } while (serverIp == sf::IpAddress::None);
            }
        }
    }
    std::cout << "Selected input: " << mode << std::endl;
}
