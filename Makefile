CC = gcc
CFLAGS = -lpthread
BUILD_DIR ?= build

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=$(BUILD_DIR)/%)
ASMS := $(SRCS:%.c=$(BUILD_DIR)/%.asm)
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(BINS)
asm: $(BUILD_DIR) $(ASMS)
obj: $(BUILD_DIR) $(OBJS)

%: $(BUILD_DIR)/%
	@:

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: %.c | $(BUILD_DIR)
	$(CC) $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%.asm: %.c | $(BUILD_DIR)
	$(CC) -S $< -o $@ -masm=intel $(CFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)


run: $(BUILD_DIR)/main
	$(BUILD_DIR)/main

strace: $(BUILD_DIR)/main
	strace $(BUILD_DIR)/main

dumpexec: $(BUILD_DIR)/main
	hexdump -C $(BUILD_DIR)/main

dumpobj: $(BUILD_DIR)/main.o
	hexdump -C $(BUILD_DIR)/main.o

helgrind: $(BUILD_DIR)/main
	valgrind --tool=helgrind $(BUILD_DIR)/main

list-builds:
	ls $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all run clean strace dumpobj dumpexec helgrind asm obj list-builds
