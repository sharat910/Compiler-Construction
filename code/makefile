CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
OBJFILES =parser.o stackadt.o stack_ptr.o rule_table.o parseTable.o codegen.o type_checker.o semantic_checker.o driver.o ast.o lexer.o symbolTable.o 
TARGET = toycompiler
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) assembly.o