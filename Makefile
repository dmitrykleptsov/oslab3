CC = gcc
CFLAGC = -O0 -Wall
SOURCES = l3.c

OBJECT_FILES = $(addprefix obj/, $(SOURCES:.c=.o))
EXECUTABLE = l3

all: obj $(SOURCES) $(EXECUTABLE)

obj:
	mkdir obj

$(EXECUTABLE): $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -rf obj $(EXECUTABLE)