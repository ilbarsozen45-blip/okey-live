CC ?= gcc
CFLAGS ?= -I/usr/include/efi -I/usr/include/efi/x86_64 -Iinclude -fpic -fshort-wchar -mno-red-zone -Wall -Wextra -std=c11
LDFLAGS ?= -nostdlib -znocombreloc -T /usr/lib/elf_x86_64_efi.lds -shared -Bsymbolic -L/usr/lib -lefi -lgnuefi

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
OUT := ../out/bootx64.efi

all: $(OUT)

$(OUT): $(OBJ)
	mkdir -p ../out
	ld $(LDFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(OUT)
