CC     := gcc
CFLAGS := -Wall -g
LIBS   := -lallegro -lallegro_image -lallegro_primitives

TARGET := $(shell basename $(shell pwd))
OBJ    := $(patsubst src/%.c,obj/%.o, $(wildcard src/*/*.c) src/main.c)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

$(OBJ): obj/%.o : src/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(filter-out src/main.o, $(OBJ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

