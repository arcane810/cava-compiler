/** @file */

#pragma once
#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

// enum containing states
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
    EOF_STATE
};

// The Lexer Class
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
    /**
     *  A function that consumes whitespace characters until the next token
     * begins
     */
    void consumeWhitespace();
    /**
     *  A function that consumes characters until a token is identified.
     * @return A pointer to a token object if last consumed character is at the
     * end of the token, else NULL.
     */
    Token *consumeCharacter();
    /**
     * A function that handles the first consumed character of a token.
     */
    void handleStartState();

  public:
    /**
     * A function that returns the position of a token in the input stream
     * @return A pair with the values as the line number and character number
     * respectively in the input stream
     */
    std::pair<int, int> getTokenStartPosition();
    /**
     * Constructor for a lexer object.
     * @param inputFile input stream of file to tokenize.
     */
    Lexer(FILE *inputFile);
    /**
     * A function that returns a pointer to next token object in input stream
     * @return A pointer to next token. Returns NULL if no token is left.
     */
    Token *nextToken();
};
