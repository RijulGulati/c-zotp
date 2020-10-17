ifeq ($(PREFIX),)
	PREFIX = /usr/local
endif

VERSION = 0.0.1

OUT_DIR = bin
SRC_DIR = cli
MKDIR = mkdir -p $(OUT_DIR)
BIN_NAME = zotp

CC = gcc
CFLAGS = -g -Wall
LIBS = -lzotp
SRCS = $(wildcard $(SRC_DIR)/*.c)

.PHONY: all install uninstall clean directories

all: directories $(OUT_DIR)/$(BIN_NAME)

$(OUT_DIR)/$(BIN_NAME): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

install:
	install $(OUT_DIR)/$(BIN_NAME) $(PREFIX)/bin

uninstall:
	rm -rf $(PREFIX)/bin/$(BIN_NAME) 

clean:
	rm -rf $(OUT_DIR)/

directories:
	$(MKDIR)

