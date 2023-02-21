CC=g++
CFLAGS = -c
TARGET = exec
INC_DIR = 
SRC_DIR = 
LDLIBS = 
HEADER = 

SRC_CPP = $(shell find ./ -name '*.cxx')

OBJ = $(SRC_CPP:%=%.o)

all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

%.cxx.o: %.cxx $(HEADER)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.cxx.o