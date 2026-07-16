CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -IIncludes
LDLIBS  = -lm

SRC     = main.c $(wildcard Src/*.c)
OBJ     = $(SRC:.c=.o)
TARGET  = airplane

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
