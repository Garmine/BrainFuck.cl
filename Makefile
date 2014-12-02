CC = clang

# ----- ----- ----- ----- ----- ----- #

# Binaries
BINDIR = bin
RELEASE_BIN = $(BINDIR)/brainfuck-cl
DEBUG_BIN = $(BINDIR)/brainfuck-cl-debug

# Source directories
SRCDIR = src
SRCDIR_HOST = $(SRCDIR)/host
SRCDIR_DEVICE = $(SRCDIR)/device
SRCDIR_SYSCALL = $(SRCDIR)/syscall

# Compilation directories
ODIR = build
ODIR_REL = $(ODIR)/rel # release build
ODIR_DBG = $(ODIR)/dbg # debug build

# Files
MAIN_FILES = bfio.c main.c util.c
HOST_FILES  = host-debug.c host.c host-instructions.c 
HOST_FILES += host-interpreter.c host-parser.c
DEVICE_FILES = #device-parser.c
SYSCALL_FILES = #syscall.c opencl_api.c file_api.c streaming_file_api.c

# Libraries
LIBS = m

# ----- ----- ----- ----- ----- ----- #

# INTERNAL!

# Source files
SRC_FILES  = $(addprefix $(SRCDIR)/, $(MAIN_FILES))
SRC_FILES += $(addprefix $(SRCDIR_HOST)/, $(HOST_FILES))
SRC_FILES += $(addprefix $(SRCDIR_DEVICE)/, $(DEVICE_FILES))
SRC_FILES += $(addprefix $(SRCDIR_SYSCALL)/, $(SYSCALL_FILES))

# Compiled files
OFILES = $(addsuffix .o, $(MAIN_FILES))
OFILES_REL = $(addprefix $(ODIR_REL), $(OFILES))
OFILES_DBG = $(addprefix $(ODIR_DBG), $(OFILES))

# Library flags
LFLAGS = $(addprefix -l, $(LIBS))
# Header flags
HFLAGS  = $(addprefix -I, $(SRCDIR))
HFLAGS += $(addprefix -I, $(SRCDIR_HOST))
HFLAGS += $(addprefix -I, $(SRCDIR_DEVICE))
HFLAGS += $(addprefix -I, $(SRCDIR_SYSCALL))
# Optimization flags
OFLAGS = 
# Extensions - like, why not?
EFLAGS = -msse -msse2 -msse3 -mmmx -m3dnow

# ----- ----- ----- ----- ----- ----- #

.PHONY: clean help

all: rel

# ----- #

help:
	@echo "Targets:
	@echo "    rel - release build"
	@echo "    dbg - debug build"

# ----- #

# Release target

release: rel

rel : CCFLAGS = $(OFLAGS) -O3 -fomit-frame-pointer -ffast-math $(EXTS)
rel: $(RELEASE_BIN)

# ----- #

# Debug target

debug: dbg

dbg : CCFLAGS = $(OFLAGS) -ggdb -g3 -fno-omit-frame-pointer -fno-inline
dbg: $(DEBUG_BIN)

# ----- #

clean:
	rm -f $(ODIR)/*/*
	rm -f $(BINDIR)/*

#EOF

