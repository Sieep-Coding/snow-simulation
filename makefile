CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lraylib -lm -lpthread -ldl -lGL -lX11

TARGET = snowfall

all: $(TARGET)

$(TARGET): raylib_app.c
	$(CC) $(CFLAGS) -o $(TARGET) raylib_app.c $(LDFLAGS)

clean:
	rm -f $(TARGET)