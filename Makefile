CC = /opt/fil/bin/filcc

CFLAGS = -Wall -Iinclude -g -O0 

SRC_DIR = src
OBJ_DIR = build
TARGET = tiny-lisp

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)