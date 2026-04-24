CC ?= gcc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Iinclude -I../drivers/include
AR ?= ar
SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
OUT := ../out/libui.a
all: $(OUT)
$(OUT): $(OBJ)
	mkdir -p ../out
	$(AR) rcs $@ $^
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f src/*.o $(OUT)
