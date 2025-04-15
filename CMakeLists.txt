cmake_minimum_required(VERSION 3.10)
project(DurakSFML)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define source files
set(SOURCES
    src/main.cpp
    src/app.cpp
    src/rules/card.cpp
    src/rules/cards.cpp
    # src/ui/button.cpp
    src/ui/cardpack.cpp
    src/ui/image_button.cpp
    # src/ui/handstack.cpp
)

# Add executable
add_executable(Durak-SFML ${SOURCES})

# Compile options for different build types
target_compile_options(Durak-SFML PRIVATE
    $<$<CONFIG:Debug>:-g -Og>
    $<$<CONFIG:Release>:-O3 -Wall -Wextra -Wdeprecated>
)

# Find and link SFML
# find_package(SFML 3.0 COMPONENTS graphics window system network REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(Durak-SFML PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    spdlog::spdlog
)
