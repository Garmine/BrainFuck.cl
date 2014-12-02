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
SRCDIR_BFAPI = $(SRCDIR)/bfapi
SRCDIR_ALL  = $(SRCDIR) $(SRCDIR_HOST)
SRCDIR_ALL += $(SRCDIR_DEVICE) $(SRCDIR_BFAPI)

# Compilation directories
ODIR = build
ODIR_REL = $(ODIR)/rel
ODIR_DBG = $(ODIR)/dbg

# Files
MAIN_FILES = bfio main util
HOST_FILES  = host-debug host host-instructions 
HOST_FILES += host-interpreter host-parser
DEVICE_FILES = #device-parser
BFAPI_FILES = #opencl_api file_api streaming_file_api

# Libraries
LIBS = m

# ----- ----- ----- ----- ----- ----- #

# INTERNAL!

# Source files
SRC_FILES  = $(addsuffix .c, $(addprefix $(SRCDIR)/, $(MAIN_FILES)))
SRC_FILES += $(addsuffix .c, $(addprefix $(SRCDIR_HOST)/, $(HOST_FILES)))
SRC_FILES += $(addsuffix .c, $(addprefix $(SRCDIR_DEVICE)/, $(DEVICE_FILES)))
SRC_FILES += $(addsuffix .c, $(addprefix $(SRCDIR_BFAPI)/, $(BFAPI_FILES)))

# Compiled files
OFILES  = $(addsuffix .o, $(MAIN_FILES))
OFILES += $(addsuffix .o, $(HOST_FILES))
OFILES += $(addsuffix .o, $(DEVICE_FILES))
OFILES += $(addsuffix .o, $(BFAPI_FILES))
OFILES_REL = $(addprefix $(ODIR_REL)/, $(OFILES))
OFILES_DBG = $(addprefix $(ODIR_DBG)/, $(OFILES))

# Library flags
LFLAGS = $(addprefix -l, $(LIBS))
# Header flags
HFLAGS  = $(addprefix -I, $(SRCDIR))
HFLAGS += $(addprefix -I, $(SRCDIR_HOST))
HFLAGS += $(addprefix -I, $(SRCDIR_DEVICE))
HFLAGS += $(addprefix -I, $(SRCDIR_BFAPI))
# Compiler flags
CFLAGS = -Wall 
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

rel : CCFLAGS = $(CFLAGS) -O3 -fomit-frame-pointer -ffast-math $(EFLAGS)
rel: $(RELEASE_BIN)

$(ODIR_REL)/%.o: $(SRCDIR)/*/%.c
	$(CC) $(CCFLAGS) $(HFLAGS) -c -o $@ $<

$(ODIR_REL)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $(HFLAGS) -c -o $@ $<

$(RELEASE_BIN): $(OFILES_REL)
	$(CC) $(CCFLAGS) $(HFLAGS) -o $@ $^ $(LFLAGS)

# ----- #

# Debug target

debug: dbg

dbg : CCFLAGS = $(CFLAGS) -ggdb -g3 -fno-omit-frame-pointer -fno-inline
dbg: $(DEBUG_BIN)

$(ODIR_DBG)/%.o: $(SRCDIR)/*/%.c
	$(CC) $(CCFLAGS) $(HFLAGS) -c -o $@ $<

$(ODIR_DBG)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $(HFLAGS) -c -o $@ $<

$(DEBUG_BIN): $(OFILES_DBG)
	$(CC) $(CCFLAGS) $(HFLAGS) -o $@ $^ $(LFLAGS)

# ----- #

clean:
	rm -f $(ODIR)/*/*
	rm -f $(BINDIR)/*

#EOF

