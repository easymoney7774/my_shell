# 编译器设置
CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lreadline

# 目录设置
SRC_DIR = src
OBJ_DIR = obj
BIN = my_shell

# 源文件和对象文件
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# 默认目标：构建可执行文件
all: $(BIN)

# 链接目标文件生成最终程序
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# 编译每个 .c 文件为 .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -rf $(OBJ_DIR) $(BIN)
