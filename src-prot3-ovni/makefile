CC = g++
CFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS = -lraylib

SOURCES = main.cpp man/entity.cpp cmp/renderCMP.cpp cmp/physicCMP.cpp sys/physicSystem.cpp sys/renderSystem.cpp
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