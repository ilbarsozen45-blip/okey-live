CC ?= gcc
CXX ?= g++
AR ?= ar
LD ?= ld
AS ?= as

COMMON_WARNINGS := -Wall -Wextra -Wshadow -Wconversion -Wundef
COMMON_OPT := -O2

export CC CXX AR LD AS COMMON_WARNINGS COMMON_OPT
