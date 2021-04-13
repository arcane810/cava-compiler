/** @file */

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
        scanned_string = "";
        last_scanned = fgetc(inputFile);
        if (last_scanned == ' ' || last_scanned == '\t' || last_scanned == '\r')
            char_number++;
        else if (last_scanned == '\n') {
            char_number = 1;
            line_number++;
        }
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

std::pair<int, int> Lexer::getTokenStartPosition() {
    return std::make_pair(token_start_line_number, token_start_char_number);
}

Token *Lexer::nextToken() {

    Token *newToken = consumeCharacter();
    while (newToken == NULL && state != EOF_STATE) {
        newToken = consumeCharacter();
    }
    return newToken;
}

Token *Lexer::consumeCharacter() {
    Token *newToken = NULL;
    switch (state) {
    case EOF_STATE:
        return NULL;
        break;
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
        } else if (isalpha(last_scanned)) {
            state = ERROR_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = resolveInteger(scanned_string);
            return newToken;
        }
        break;
    case TEMP_FLOAT_STATE:
        if (isdigit(last_scanned)) {
            state = FLOAT_STATE;
            scanned_string += last_scanned;
        } else {
            state = ERROR_STATE;
            scanned_string += last_scanned;
        }
        break;
    case FLOAT_STATE:
        if (isdigit(last_scanned)) {
            scanned_string += last_scanned;
        } else if (isalpha(last_scanned)) {
            state = ERROR_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = resolveFloat(scanned_string);
            return newToken;
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
            newToken = new Operator(ADDITION);
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
            newToken = new Operator(SUBTRACTION);
            return newToken;
        }
        break;
    case INCREMENT_STATE:
        state = START_STATE;
        newToken = new Operator(INCREMENT);
        return newToken;
        break;
    case DECREMENT_STATE:
        state = START_STATE;
        newToken = new Operator(DECREMENT);
        return newToken;
        break;
    case MUL_STATE:
        if (last_scanned == '=') {
            state = MUL_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(MULTIPLICATION);
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
            newToken = new Operator(DIVISION);
            return newToken;
        }
        break;
    case COMMENT_SINGLE_STATE:
        if (last_scanned == '\n') {
            state = START_STATE;
        }
        break;
    case COMMENT_MULTI_STATE:
        if (last_scanned == '*') {
            state = COMMENT_MULTI_PSEUDOEND_STATE;
        }
        break;
    case COMMENT_MULTI_PSEUDOEND_STATE:
        if (last_scanned == '/') {
            state = START_STATE;
        } else if (last_scanned != '*') {
            state = COMMENT_MULTI_STATE;
        }
        break;
    case MOD_STATE:
        if (last_scanned == '=') {
            state = MOD_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(MODULO);
            return newToken;
        }
        break;
    case ASSIGN_STATE:
        if (last_scanned == '=') {
            state = EQUAL_TO_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(ASSIGNMENT);
            return newToken;
        }
        break;
    case NOT_STATE:
        if (last_scanned == '=') {
            state = NOT_EQUAL_TO_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(BOOL_NOT);
            return newToken;
        }
        break;
    case ADD_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(ADD_EQUAL);
        return newToken;
        break;
    case SUB_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(SUB_EQUAL);
        return newToken;
        break;
    case MUL_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(MUL_EQUAL);
        return newToken;
        break;
    case DIV_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(DIV_EQUAL);
        return newToken;
        break;
    case MOD_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(MOD_EQUAL);
        return newToken;
        break;
    case EQUAL_TO_STATE:
        state = START_STATE;
        newToken = new Operator(EQUAL_TO);
        return newToken;
        break;
    case NOT_EQUAL_TO_STATE:
        state = START_STATE;
        newToken = new Operator(NOT_EQUAL_TO);
        return newToken;
        break;
    case GREATER_STATE:
        if (last_scanned == '=') {
            state = GREATER_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(GREATER);
            return newToken;
        }
        break;
    case LESSER_STATE:
        if (last_scanned == '=') {
            state = LESSER_EQUAL_STATE;
            scanned_string += last_scanned;
        } else {
            state = START_STATE;
            newToken = new Operator(LESSER);
            return newToken;
        }
        break;
    case GREATER_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(GREATER_EQUAL);
        return newToken;
        break;
    case LESSER_EQUAL_STATE:
        state = START_STATE;
        newToken = new Operator(LESSER_EQUAL);
        return newToken;
        break;
    case AMP_STATE:
        if (last_scanned == '&') {
            state = AND_STATE;
            scanned_string += last_scanned;
        } else {
            state = ERROR_STATE;
            scanned_string += last_scanned;
        }
        break;
    case PIPE_STATE:
        if (last_scanned == '|') {
            state = OR_STATE;
            scanned_string += last_scanned;
        } else {
            state = ERROR_STATE;
            scanned_string += last_scanned;
        }
        break;
    case AND_STATE:
        state = START_STATE;
        newToken = new Operator(BOOL_AND);
        return newToken;
        break;
    case OR_STATE:
        state = START_STATE;
        newToken = new Operator(BOOL_OR);
        return newToken;
        break;
    case OPEN_STRING_STATE:
        if (last_scanned == '\"') {
            state = CLOSE_STRING_STATE;
        } else if (last_scanned == '\\') {
            state = OPEN_STRING_ESCAPE_STATE;
        } else if (last_scanned == '\n') {
            scanned_string = "\"" + scanned_string;
            state = ERROR_STATE;
        } else {
            scanned_string += last_scanned;
        }
        break;
    case CLOSE_STRING_STATE:
        state = START_STATE;
        newToken = new StringLiteral(scanned_string);
        return newToken;
        break;
    case OPEN_STRING_ESCAPE_STATE:
        state = OPEN_STRING_STATE;
        if (last_scanned == 'a') {
            scanned_string += '\a';
        } else if (last_scanned == 'b') {
            scanned_string += '\b';
        } else if (last_scanned == 'f') {
            scanned_string += '\f';
        } else if (last_scanned == 'n') {
            scanned_string += '\n';
        } else if (last_scanned == 'r') {
            scanned_string += '\r';
        } else if (last_scanned == 't') {
            scanned_string += '\t';
        } else if (last_scanned == 'v') {
            scanned_string += '\v';
        } else if (last_scanned == '\'') {
            scanned_string += '\'';
        } else if (last_scanned == '\"') {
            scanned_string += '\"';
        } else if (last_scanned == '\\') {
            scanned_string += '\\';
        } else {
            state = ERROR_STATE;
            scanned_string = "";
        }
        break;
    case TERTIARY_Q_STATE:
        state = START_STATE;
        newToken = new Operator(TERTIARY_Q);
        return newToken;
        break;
    case TERTIARY_C_STATE:
        state = START_STATE;
        newToken = new Operator(TERTIARY_C);
        return newToken;
        break;
    case DELIM_STATE:
        state = START_STATE;
        switch (scanned_string[0]) {
        case (';'):
            newToken = new Delimiter(SEMICOLON);
            break;
        case (','):
            newToken = new Delimiter(COMMA);
            break;
        case ('('):
            newToken = new Delimiter(PARANTHESES_OPEN);
            break;
        case (')'):
            newToken = new Delimiter(PARANTHESES_CLOSE);
            break;
        case ('['):
            newToken = new Delimiter(SQUARE_OPEN);
            break;
        case (']'):
            newToken = new Delimiter(SQUARE_CLOSE);
            break;
        case ('{'):
            newToken = new Delimiter(BRACE_OPEN);
            break;
        case ('}'):
            newToken = new Delimiter(BRACE_CLOSE);
            break;
        }
        return newToken;
        break;
    case ERROR_STATE:
        if (isdigit(scanned_string.back()) || isalpha(scanned_string.back())) {
            if (isdigit(last_scanned) || isalpha(last_scanned)) {
                scanned_string += last_scanned;
            } else {
                state = START_STATE;
                return new ErrorToken("Invalid Token: " + scanned_string);
            }
        } else {
            state = START_STATE;
            return new ErrorToken("Invalid Token: " + scanned_string);
        }
        break;
    }

    if (last_scanned == EOF)
        return NULL;

    last_scanned = fgetc(inputFile);
    if (last_scanned == '\n') {
        line_number++;
        char_number = 0;
    }
    char_number++;
    return NULL;
}

void Lexer::handleStartState() {
    consumeWhitespace();
    scanned_string = "";
    scanned_string += last_scanned;
    token_start_line_number = line_number;
    token_start_char_number = char_number;
    if (last_scanned == EOF) {
        state = EOF_STATE;
    } else if (isalpha(last_scanned) || last_scanned == '_') {
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
        state = OPEN_STRING_STATE;
        scanned_string = "";
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
    } else if (last_scanned == '?') {
        state = TERTIARY_Q_STATE;
    } else if (last_scanned == ':') {
        state = TERTIARY_C_STATE;
    } else {
        state = ERROR_STATE;
    }
    return;
}