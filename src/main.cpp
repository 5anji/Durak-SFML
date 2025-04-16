#include "app.h"
// #include "valid_input.h"
#include <spdlog/fmt/fmt.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <algorithm>

namespace {

inline bool is_number(std::string_view str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

constexpr uint16_t str2int(char const* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

inline constexpr auto help_text = R"(Usage:

Durak-SFML [OPTIONS...]

Options:
    -h, --help                         Display this help
    -d, --display <width> <height>     Set custom window size

)";

}  // namespace

int main(int argc, char const** argv) {
    auto logger = spdlog::stdout_color_mt("console");
    uint16_t width(1024), height(768);

    if (argc > 0) {
        for (uint8_t i = 1; i < static_cast<uint8_t>(argc); i++) {
            switch (str2int(argv[i])) {
            case str2int("-d"):
            case str2int("--display"): {
                if (!((i + 2) < argc)) {
                    spdlog::warn(
                            "Not enough arguments for --display option. Using 1024x768");
                }

                if (!is_number(argv[i + 1]) || !is_number(argv[i + 2])) {
                    spdlog::warn("Height or width is not number. Using 1024x768");
                }
                uint16_t temp_width = std::stoi(argv[i + 1]);
                uint16_t temp_height = std::stoi(argv[i + 2]);

                float ratio =
                        static_cast<float>(temp_width) / static_cast<float>(temp_height);
                bool rep_condition = (temp_width >= 200) && (temp_height >= 200)
                                     && (0.5f < ratio) && (ratio < 2.f);

                if (!rep_condition) {
                    spdlog::warn("Inacceptable window size ratio. Using 1024x768");
                }

                width = temp_width;
                height = temp_height;
                break;
            }
            case str2int("-h"):
            case str2int("--help"): {
                fmt::print("{}", help_text);
                return 0;
            }
            }
        }
    }

    Application app(width, height);
    spdlog::info("Starting UI");
    return app.start();
}
