#pragma once
#include <SFML/Network.hpp>
#include <iostream>

void validate_input(std::string& mode,
                    sf::IpAddress& serverIp,
                    bool mode_check,
                    bool is_manual,
                    bool ip_check) {
    auto ip_input = [](sf::IpAddress& ip, bool is_manual, bool ip_check) {
        if (is_manual) {
            if (!ip_check) {
                do {
                    std::cout << "Type the IPv4 address or name of the server to connect "
                                 "to: ";
                    std::cin >> ip;
                } while (ip == sf::IpAddress::None);
            }
        } else {
            ip = sf::IpAddress::getLocalAddress();
        }
    };

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
                ip_input(serverIp, is_manual, ip_check);
            }
        }

        if (tolower(input) == 's') {
            mode = "server";
        }
    } else {
        if (mode == "client") {
            ip_input(serverIp, is_manual, ip_check);
        }
    }
    std::cout << "Selected input: " << mode << std::endl;
}
