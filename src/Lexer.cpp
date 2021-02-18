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
    scanned_string = last_scanned;
    line_number = 1;
    char_number = 1;
    done = false;
    state = START_STATE;
}

Token *Lexer::nextToken() {
    if (last_scanned == EOF) {
        done = true;
        return NULL;
    }
    Token *newToken = consumeCharacter();
    while (newToken == NULL) {
        newToken = consumeCharacter();
    }
    return newToken;
}

Token *Lexer::consumeCharacter() {
    Token *newToken = NULL;
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
            newToken = resolveIdentifier(scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case INTEGER_STATE:
        // handle error here
        if (isdigit(last_scanned)) {
            scanned_string += last_scanned;
        } else if (last_scanned == '.') {
            scanned_string += last_scanned;
            state = TEMP_FLOAT_STATE;
        } else {
            state = START_STATE;
            newToken = resolveInteger(scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case TEMP_FLOAT_STATE:
        if (isdigit(last_scanned)) {
            state = FLOAT_STATE;
            scanned_string += last_scanned;
        } else if (last_scanned) {
        }
        break;
    case ADD_STATE:
        if (last_scanned == '+') {
            state = INCREMENT_STATE;
            scanned_string += last_scanned;
        } else if (last_scanned == '=') {
            state = ADD_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(ADDITION, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case SUB_STATE:
        if (last_scanned == '-') {
            state = DECREMENT_STATE;
            scanned_string += last_scanned;
        } else if (last_scanned == '=') {
            state = SUB_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(SUBTRACTION, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case MUL_STATE:
        if (last_scanned == '=') {
            state = MUL_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(MULTIPLICATION, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case DIV_STATE:
        if (last_scanned == '=') {
            state = DIV_EQUAL_STATE;
            scanned_string += last_scanned;
        } else if (last_scanned == '/') {
            state = COMMENT_SINGLE_STATE;
            scanned_string = "";
        } else if (last_scanned == '*') {
            state = COMMENT_MULTI_STATE;
            scanned_string = "";
        } else {
            state = START_STATE;
            newToken = new Operator(DIVISION, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case MOD_STATE:
        if (last_scanned == '=') {
            state = MOD_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(MODULO, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case ASSIGN_STATE:
        if (last_scanned == '=') {
            state = EQUAL_TO_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(ASSIGNMENT, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case NOT_STATE:
        if (last_scanned == '=') {
            state = NOT_EQUAL_TO_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(BOOL_NOT, scanned_string);
            scanned_string = "";
            scanned_string += last_scanned;
            return newToken;
        }
        break;
    case ADD_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(ADD_EQUAL, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case SUB_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(SUB_EQUAL, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case MUL_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(MUL_EQUAL, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case DIV_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(DIV_EQUAL, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case MOD_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(MOD_EQUAL, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case EQUAL_TO_STATE:
        state = START_STATE;
        newToken = new Operator(EQUAL_TO, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    case NOT_EQUAL_TO_STATE:
        state = START_STATE;
        newToken = new Operator(NOT_EQUAL_TO, scanned_string);
        scanned_string = "";
        scanned_string += last_scanned;
        return newToken;
        break;
    }
    last_scanned = fgetc(inputFile);
    return NULL;
}

void Lexer::handleStartState() {
    consumeWhitespace();
    scanned_string = "";
    scanned_string += last_scanned;
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
    } else if (last_scanned == '%') {
        state = MOD_STATE;
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
    return;
}