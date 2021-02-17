#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <vector>

enum State {
    START_STATE,
    IDENTIFIER_STATE,
    INTEGER_STATE,
    TEMP_FLOAT_STATE,
    FLOAT_STATE,
    ADD_STATE,
    SUB_STATE,
    MUL_STATE,
    DIV_STATE,
    OPEN_STRING,
    PIPE_STATE,
    AMP_STATE,
    ASSIGN_STATE,
    GREATER_STATE,
    LESSER_STATE,
    NOT_STATE,
    DELIM_STATE,
    ERROR_STATE
};

class Lexer {
    FILE *inputFile;
    char last_scanned;
    bool done;
    int line_number;
    int char_number;
    State state;
    std::string scanned_string;
    void consumeWhitespace();
    Token *consumeCharacter();
    void handleStartState();

  public:
    Lexer(FILE *inputFile);
    Token *nextToken();
};
