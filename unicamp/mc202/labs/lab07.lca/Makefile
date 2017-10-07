# project name (generate executable with this name)
TARGET   = lab

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -g -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -g -I. -lm

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
	@$(rm) $(OBJECTS) $(TARGET) 01.out 02.out 03.out 04.out 05.out
	@echo "Cleanup complete!"

.PHONY: run
run:
	@./$(TARGET) < tests/01.in > 01.out
	@./$(TARGET) < tests/02.in > 02.out
	@./$(TARGET) < tests/03.in > 03.out
	@./$(TARGET) < tests/04.in > 04.out
	@./$(TARGET) < tests/05.in > 05.out