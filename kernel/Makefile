CC ?= gcc
CXX ?= g++
CFLAGS ?= -ffreestanding -fno-stack-protector -fno-pic -m64 -std=c11 -Wall -Wextra -Iinclude -I../lib/include
CXXFLAGS ?= -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -m64 -std=c++17 -Wall -Wextra -Iinclude -I../lib/include
LDFLAGS ?= -nostdlib -T linker.ld

C_SRC := $(shell find src -name '*.c')
CPP_SRC := $(shell find src -name '*.cpp')
OBJ := $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)
OUT := ../out/kernel.elf

all: $(OUT)

$(OUT): $(OBJ)
	mkdir -p ../out
	ld $(LDFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)
