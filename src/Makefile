# Variables
OBJS    = main.o starter.o cpu_tester.o
RES     = icon.res
OUT     = ../bin/drainage.exe
CC      = g++
FLAGS   = -g -Wall
LFLAGS  = 

# Default target
all: $(OUT)

# Rule to link object files and resource file into the executable
$(OUT): $(OBJS) $(RES) | bin
	$(CC) $(OBJS) $(RES) -o $(OUT) $(LFLAGS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

# Rule to compile .rc files into .res files
$(RES): icon.rc
	windres icon.rc -O coff -o $(RES)

# Create the bin directory if it doesn't exist
bin:
	if not exist ..\bin mkdir ..\bin

# Clean up generated files
clean:
	del $(OBJS) $(RES) 2>nul