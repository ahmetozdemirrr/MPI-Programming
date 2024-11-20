# Programs
CC = mpicc
CFLAGS = -g -Wall


# Internal Flags
INTERNAL_CFLAGS = \
	-std=gnu99 \
	-D_GNU_SOURCE \
	-D_FILE_OFFSET_BITS=64 \
	-Iinclude \
	$(CFLAGS)
INTERNAL_LDFLAGS = $(LDFLAGS)
INTERNAL_LIBS = -lm $(LDLIBS)


# Variables
SRC_DIR = src
INCLUDE_DIR = include
MAIN_FILE = mpi_main.c
PROGRAM = mpi_run


OBJECTS = \
	$(SRC_DIR)/util.o

HEADERS = \
	$(INCLUDE_DIR)/util.h


# Targets
all: $(PROGRAM)

$(SRC_DIR)/util.o: $(SRC_DIR)/util.c $(HEADERS)
	$(CC) $(INTERNAL_CFLAGS) -c -o $@ $<

$(PROGRAM): $(OBJECTS) $(MAIN_FILE)
	$(CC) $(INTERNAL_LDFLAGS) -o $@ $(MAIN_FILE) $(OBJECTS) $(INTERNAL_LIBS)


# Clean generated files
clean:
	rm -f $(PROGRAM) $(SRC_DIR)/*.o


# Run the program
run: $(PROGRAM)
	mpiexec -n 4 ./$(PROGRAM)


.PHONY: all clean run
