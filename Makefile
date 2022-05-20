CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -O3 -march=native -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
CFLAGS_DEBUG=-std=c++17 -Og -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
SOURCES=src/main.cpp src/app.cpp src/tcp.cpp
EXECUTABLE=Durak-SFML

build: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

debug: $(SOURCES)
	$(CC) $(CFLAGS_DEBUG) $(SOURCES) -o $(EXECUTABLE)

clean: $(EXECUTABLE)
	rm *.out
