CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Kaynak dosyalar
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/shell.c $(SRC_DIR)/pipe.c $(SRC_DIR)/redirect.c $(SRC_DIR)/background.c
# Hedef dosyalar
OBJS = $(SRCS:.c=.o)

# Çıktı dosyası
TARGET = $(BIN_DIR)/my_shell

# Derleme hedefi
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Kaynak dosyalarını derleme
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Temizlik işlemi
clean:
	rm -f $(OBJS) $(TARGET)
