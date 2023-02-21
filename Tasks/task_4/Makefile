TARGET = exec
CC = g++
CFLAG = -c -Wall
LDFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET) clear

$(TARGET): *.o
	$(CC) $(LDFLAGS) *.o -o $(TARGET) $(LDLIBS)

*cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -f *.o