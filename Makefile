CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -O3 -march=native -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
CFLAGS_DEBUG=-std=c++17 -Og -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
SOURCES=src/main.cpp src/app.cpp src/rules/card.cpp src/rules/cards.cpp src/ui/button.cpp src/ui/cardpack.cpp src/ui/image_button.cpp
EXECUTABLE=Durak-SFML

build: $(SOURCES)
	mkdir -p build/
	$(CC) $(CFLAGS) $(SOURCES) -o build/$(EXECUTABLE)

debug: $(SOURCES)
	$(CC) $(CFLAGS_DEBUG) $(SOURCES) -o build$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -dfr ./build/
