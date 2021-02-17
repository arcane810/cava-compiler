#include "Lexer.hpp"

bool isDelim(char c) {
    if (c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']' ||
        c == ';' || c == ',')
        return true;
    else
        return false;
}

void Lexer::consumeWhitespace() {
    while (last_scanned == ' ' || last_scanned == '\n' ||
           last_scanned == '\t' || last_scanned == '\r') {
        if (last_scanned == ' ' || last_scanned == '\t' || last_scanned == '\r')
            char_number++;
        else {
            char_number = 1;
            line_number++;
        }
        scanned_string = "";
        last_scanned = fgetc(inputFile);
    }
}

Lexer::Lexer(FILE *inputFile) : inputFile(inputFile) {
    last_scanned = fgetc(inputFile);
    scanned_string += last_scanned;
    line_number = 1;
    char_number = 1;
    done = false;
    state = START_STATE;
}

Token *Lexer::nextToken() {
    std::cout << "NEXT TOKEN CALL\n";
    if (last_scanned == EOF) {
        done = true;
        return NULL;
    }
    Token *newToken = consumeCharacter();
    while (newToken == NULL) {
        std::cout << "IN LOOP";
        newToken = consumeCharacter();
    }
    return newToken;
}

Token *Lexer::consumeCharacter() {
    switch (state) {
    case START_STATE:
        handleStartState();
        break;
    case IDENTIFIER_STATE:
        if (isalpha(last_scanned) || isdigit(last_scanned) ||
            last_scanned == '_') {
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            Token *res = resolveIdentifier(scanned_string);
            scanned_string = "" + last_scanned;
            return res;
        }
        break;
        // case INTEGER_STATE:
        //    if (isdigit(last_scanned)) {
        //        state = INTEGER_STATE;
        //    }
    }

    last_scanned = fgetc(inputFile);
}

void Lexer::handleStartState() {
    consumeWhitespace();
    if (isalpha(last_scanned) || last_scanned == '_') {
        state = IDENTIFIER_STATE;
    } else if (isdigit(last_scanned)) {
        state = INTEGER_STATE;
    } else if (last_scanned == '+') {
        state = ADD_STATE;
    } else if (last_scanned == '-') {
        state = SUB_STATE;
    } else if (last_scanned == '*') {
        state = MUL_STATE;
    } else if (last_scanned == '/') {
        state = DIV_STATE;
    } else if (last_scanned == '\"') {
        state = OPEN_STRING;
    } else if (last_scanned == '|') {
        state = PIPE_STATE;
    } else if (last_scanned == '&') {
        state = AMP_STATE;
    } else if (last_scanned == '=') {
        state = ASSIGN_STATE;
    } else if (last_scanned == '>') {
        state = GREATER_STATE;
    } else if (last_scanned == '<') {
        state = LESSER_STATE;
    } else if (last_scanned == '!') {
        state = NOT_STATE;
    } else if (isDelim(last_scanned)) {
        state = DELIM_STATE;
    } else {
        state = ERROR_STATE;
    }
}