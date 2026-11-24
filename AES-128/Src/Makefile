CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SRCS = main.c aes_key.c aes_core.c aes_debug.c
TARGET = aes128

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET) > ket_qua_aes128.txt

clean:
	rm -f $(TARGET) $(TARGET).exe