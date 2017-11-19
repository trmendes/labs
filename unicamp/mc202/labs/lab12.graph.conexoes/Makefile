# project name (generate executable with this name)
TARGET   = lab

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -g -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -std=c99 -g -I. -lm

# change these to proper directories where each file should be
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:%.c=%.o)
rm       = rm -f


$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): %.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS) $(TARGET)
	@echo "Cleanup complete!"