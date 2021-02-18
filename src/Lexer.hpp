#pragma once
#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <utility>
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
    MOD_STATE,
    OPEN_STRING_STATE,
    PIPE_STATE,
    AMP_STATE,
    OR_STATE,
    AND_STATE,
    ASSIGN_STATE,
    GREATER_STATE,
    LESSER_STATE,
    NOT_STATE,
    DELIM_STATE,
    ERROR_STATE,
    INCREMENT_STATE,
    DECREMENT_STATE,
    ADD_EQUAL_STATE,
    SUB_EQUAL_STATE,
    MUL_EQUAL_STATE,
    DIV_EQUAL_STATE,
    MOD_EQUAL_STATE,
    GREATER_EQUAL_STATE,
    LESSER_EQUAL_STATE,
    COMMENT_SINGLE_STATE,
    COMMENT_MULTI_STATE,
    COMMENT_MULTI_PSEUDOEND_STATE,
    EQUAL_TO_STATE,
    NOT_EQUAL_TO_STATE,
    TERTIARY_Q_STATE,
    TERTIARY_C_STATE,
    OPEN_STRING_ESCAPE_STATE,
    CLOSE_STRING_STATE,
};

class Lexer {
    FILE *inputFile;
    char last_scanned;
    bool done;
    int line_number;
    int char_number;
    int token_start_line_number;
    int token_start_char_number;
    State state;
    std::string scanned_string;
    void consumeWhitespace();
    Token *consumeCharacter();
    void handleStartState();

  public:
    std::pair<int, int> getTokenStartPosition();
    Lexer(FILE *inputFile);
    Token *nextToken();
};
