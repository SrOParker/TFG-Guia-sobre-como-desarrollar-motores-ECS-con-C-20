CC = g++
CFLAGS = -std=c++20 -Wall -Wextra #-fsanitize=address
LDFLAGS = -L./lib -Wl,-rpath=./lib -lraylib #-fsanitize=address

SOURCES = main.cpp game.cpp sys/renderSys.cpp sys/inputSys.cpp sys/positionSys.cpp sys/collisionSys.cpp sys/iaSys.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(patsubst %, obj/%, $(OBJECTS))
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE)

clean:
	rm -rf obj
	rm -f $(EXECUTABLE)