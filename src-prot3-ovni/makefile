CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -fsanitize=address
LDFLAGS = -lraylib -fsanitize=address

SOURCES = main.cpp man/entity.cpp cmp/renderCMP.cpp cmp/physicCMP.cpp sys/physicSystem.cpp sys/renderSystem.cpp cmp/inputCMP.cpp sys/inputSystem.cpp cmp/collisionCMP.cpp sys/collisionSystem.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(patsubst %, obj/%, $(OBJECTS))
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -f $(EXECUTABLE)