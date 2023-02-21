TARGET = exec
CC = g++
CFLAG = -c -Wall
LDFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET) clean

$(TARGET): *.o
	$(CC) $(LDFLAGS) *.o -o $(TARGET) $(LDLIBS)

*cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

