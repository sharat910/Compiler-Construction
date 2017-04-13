CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES =parser.o stackadt.o stack_ptr.o rule_table.o parseTable.o lexer.o driver.o symbol_table.o
TARGET = stage1exe
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)