SOURCES=plateau.c gounki.c pion.c liste.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS= -Wall -std=c89 -pedantic
EXECUTABLE=gounki

$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
