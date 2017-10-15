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
	@$(rm) $(OBJECTS) $(TARGET) gmon.out 00.out 01.out 02.out 03.out 04.out 07.out
	@echo "Cleanup complete!"

.PHONY: run
run:
	@./$(TARGET) < tests/00-enunciado.in > 00.out
	@./$(TARGET) < tests/01-pequeno.in > 01.out
	@./$(TARGET) < tests/02-ins-rems.in > 02.out