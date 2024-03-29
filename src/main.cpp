#include "../libs/isNumber.h"
#include "../libs/str2int.h"
#include "app.h"
#include "valid_input.h"

int main(int argc, const char** argv) {
    uint16_t width(1024), height(768);
    std::string mode;
    sf::IpAddress ip;
    bool checkers[3]{false, false, false};

    if (argc > 0) {
        for (uint8_t i = 1; i < static_cast<uint8_t>(argc); i++) {
            switch (str2int(argv[i])) {
            case str2int("-d"):
            case str2int("--display"): {
                if ((i + 2) < argc) {
                    std::string square_width = argv[i + 1];
                    std::string square_height = argv[i + 2];
                    if (isNumber(square_width) && isNumber(square_height)) {
                        uint16_t temp_width = std::stoi(square_width);
                        uint16_t temp_height = std::stoi(square_height);

                        float ratio = static_cast<float>(temp_width) / static_cast<float>(temp_height);
                        bool rep_condition = (temp_width >= 200) && (temp_height >= 200) && (0.5f < ratio) && (ratio < 2.f);

                        if (rep_condition) {
                            width = temp_width;
                            height = temp_height;
                        } else {
                            std::cout << "Inacceptable window size. Using 1024x768" << std::endl;
                        }

                    } else {
                        std::cout << "Invalid expression. Using 1024x768" << std::endl;
                    }
                } else {
                    std::cout << "Invalid expression. Using 1024x768" << std::endl;
                }
                break;
            }
            case str2int("-t"):
            case str2int("--type"): {
                if ((i + 1) < argc) {
                    std::string input = argv[i + 1];
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                    if (input == "server" || input == "client") {
                        mode = input;
                        checkers[0] = true;
                    } else {
                        std::cout << "Wrong option" << std::endl;
                    }

                } else {
                    std::cout << "Invalid expression, requires 1 more argument" << std::endl;
                }
            } break;
            case str2int("-m"):
            case str2int("--manual"):
                checkers[2] = true;
                break;
            case str2int("-i"):
            case str2int("--ip"): {
                if ((i + 1) < argc) {
                    std::string input = argv[i + 1];
                    ip = input;
                    checkers[1] = true;

                } else {
                    std::cout << "Invalid expression, requires 1 more argument" << std::endl;
                }
            } break;
            case str2int("-h"):
            case str2int("--help"): {
                std::cout << "Usage:" << std::endl
                          << "\tDurak-SFML [OPTIONS...]" << std::endl
                          << "Options:" << std::endl
                          << "\t-h, --help\t\t\t\tDisplay this help" << std::endl
                          << "\t-d, --display <width> <height>\t\tSet custom window size" << std::endl
                          << "\t-t, --type <server/client>\t\tSet player type" << std::endl
                          << "\t-m, --manual\t\t\t\tManually input ip adress" << std::endl
                          << "\t-i, --ip <wi-fi IPv4 Address>\t\tSet IP Adress (for client mode)" << std::endl
                          << std::endl;
                return 0;
            }
            }
        }
    }

    validate_input(mode, ip, checkers[0], checkers[1], checkers[2]);

    Application app(width, height);
    return app.start(mode, ip);
}
