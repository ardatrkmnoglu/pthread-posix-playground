CC = gcc
CFLAGS = -lpthread
GDBFLAGS = -ex "break _start" -ex "layout asm"
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

build_%: %.c
	$(CC) $< -o $(BUILD_DIR)/main

assemble_%: %.asm
	./assemble.sh $< main


run: $(BUILD_DIR)/main
	$<

strace: $(BUILD_DIR)/main
	strace $<

dumpexec: $(BUILD_DIR)/main
	hexdump -C $<

dumpobj: $(BUILD_DIR)/main.o
	hexdump -C $<

gdb: $(BUILD_DIR)/main
	gdb $(GDBFLAGS) $<

helgrind: $(BUILD_DIR)/main
	valgrind --tool=helgrind $<

list-builds:
	ls $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all build assemble run clean strace dumpobj dumpexec helgrind asm obj list-builds
