CC 	= /usr/bin/g++
CFLAGS 	= -Wall
LDFLAGS = -Wall -Wno-write-strings -c
FLAGS = -pg -lpthread
BUILD_DIR = ../../build
SRC_DIR = ..

#Parser/parserTest.cpp\
SRC 	=
	Scanner/Scanner.cpp Scanner/Information.cpp Scanner/List.cpp Scanner/ListElement.cpp  Scanner/Symtable.cpp Scanner/Token.cpp\
	IO/ConsoleOutBuffer.cpp IO/OutBuffer.cpp IO/ThreadFileOutBuffer.cpp IO/BufferMonitor.cpp IO/ThreadInBuffer.cpp\
	Container/ObjectContainer.cpp \
	Parser/Array.cpp  Parser/Decls.cpp  Parser/Exp.cpp    Parser/Nterm.cpp  Parser/Op_exp.cpp  Parser/Prog.cpp        Parser/Statements.cpp \
	Parser/Decl.cpp   Parser/Exp2.cpp   Parser/Index.cpp  Parser/Op.cpp     Parser/Parser.cpp  Parser/Statement.cpp 
		
OBJS = ${SRC:%.cpp=$(BUILD_DIR)/%.o}

scanner:  $(OBJS)
	$(CC) $(CFLAGS) $(FLAGS) -o Scanner $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(LDFLAGS) $(FLAGS) -o $@ $<

		
clean:
	rm -rf $(OBJS)

echo:
	@echo Source files
	@ echo $(SRC)
	@echo
	@echo Object files
	@ echo $(OBJS)
