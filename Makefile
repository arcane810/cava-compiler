CC = g++
OUT_DIR = build
CFLAGS = -c -std=c++17 -O2
INC = -I src/includes
.PHONY: test clean
all : dir build/parse.o

build/parse.o : build/main.o build/Parser.o build/ParseTree.o build/ParseTable.o build/GrammarRule.o build/Lexer.o build/Token.o
		$(CC) build/main.o build/Parser.o build/ParseTree.o build/ParseTable.o build/GrammarRule.o build/Lexer.o build/Token.o -o build/parse

build/main.o : src/parser/driver.cpp
			$(CC) $(CFLAGS) src/parser/driver.cpp -o build/main.o $(INC)

build/Parser.o : src/parser/Parser.cpp
			$(CC) $(CFLAGS) src/parser/Parser.cpp -o build/Parser.o $(INC)

build/ParseTree.o : src/parser/ParseTree.cpp
			$(CC) $(CFLAGS) src/parser/ParseTree.cpp -o build/ParseTree.o $(INC)

build/ParseTable.o : src/parser/ParseTable.cpp
			$(CC) $(CFLAGS) src/parser/ParseTable.cpp -o build/ParseTable.o $(INC)

build/GrammarRule.o : src/parser/GrammarRule.cpp
			$(CC) $(CFLAGS) src/parser/GrammarRule.cpp -o build/GrammarRule.o $(INC)

build/Lexer.o : src/lexer/Lexer.cpp
			$(CC) $(CFLAGS) src/lexer/Lexer.cpp -o build/Lexer.o $(INC)

build/Token.o : src/lexer/Token.cpp
			$(CC) $(CFLAGS) src/lexer/Token.cpp -o build/Token.o $(INC)


dir:
			@mkdir -p $(OUT_DIR)

test:
			./scripts/test

clean : 
			rm -rf $(OUT_DIR)
			@mkdir -p $(OUT_DIR)
			
