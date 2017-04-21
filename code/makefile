CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
OBJFILES =parser.o stackadt.o stack_ptr.o rule_table.o parseTable.o codegen.o driver.o lexer.o symbolTable.o type_checker.o semantic_checker.o ast.o 
TARGET = stage1exe
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)