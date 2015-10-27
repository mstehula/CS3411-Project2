# Makefile for Project 1 for cs3411
#
# author Mitchell Stehula

CC= cc
CFLAGS= -c -g
LFLAGS=
FILES=asort 
OBJECTS= $(addsuffix .o, $(FILES))
EXECUTABLE= asort

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
