CC = gcc

CFLAGS = -Wall -std=c++17

LIBS = -lX11 -lcairo

TARGET = build/taskbar

SRC = src/main.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f build/$(TARGET)

all: $(TARGET)

