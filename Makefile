CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror  -O2 -g 
LDFLAGS = -lm

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
HFILE = $(wildcard *.h)

all: banhammer

%.o: %.c $(HFILE)
	$(CC) $(CFLAGS) -c $<

banhammer: $(OBJECTS) banhammer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

tidy:
	rm -rf $(wildcard *.o)
clean: tidy
	rm -rf banhammer
format:
	clang-format -i -style=file *.[c,h]

