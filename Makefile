CC = gcc
SDL = -framework SDL2

CCFLAGS = -g -Wall -Wextra -Werror -c -std=c99
LDFLAGS = $(SDL)
BINARY = QSDL

all: $(BINARY)

$(BINARY): QSDL.o
	   $(CC) $(LDFLAGS) $< -o $@
QSDL.o: QSDL.c
	$(CC) $(CCFLAGS) $< -o $@
clean:
	rm *.o && rm $(BINARY)
