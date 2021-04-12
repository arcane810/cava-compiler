/**
 * Group 12 - Cava
 * Akul Singhal - 2018A7PS0193H
 * Rohan Daniel - 2018A7PS0584H
 * Pranav Rajagopalan - 2018A7PS0177H
 * Akshay Tiwari - 2018A7PS0201H
 */
#include "Token.hpp"
#include <iostream>

Token::Token(TokenType tokenType) : tokenType(tokenType) {}

Keyword::Keyword(KeywordType keywordType)
    : Token(KEYWORD), keywordType(keywordType) {}

Delimiter::Delimiter(DelimiterType delimiterType)
    : Token(DELIMITER), delimiterType(delimiterType) {}

Identifier::Identifier(std::string identifier_name)
    : Token(IDENTIFIER), identifier_name(identifier_name) {}

IntegerLiteral::IntegerLiteral(int64_t value)
    : Token(INTEGER_LITERAL), value(value) {}

FloatingPointLiteral::FloatingPointLiteral(long double value)
    : Token(FLOATING_POINT_LITERAL), value(value) {}

Operator::Operator(OperatorType operatorType)
    : Token(OPERATOR), operatorType(operatorType) {}

StringLiteral::StringLiteral(std::string value)
    : Token(STRING_LITERAL), value(value) {}

ErrorToken::ErrorToken(std::string error_message)
    : Token(ERROR_TOKEN), error_message(error_message) {}

Token *resolveIdentifier(std::string id) {
    if (id == "int") {
        return new Keyword(INT);
    } else if (id == "bool") {
        return new Keyword(BOOL);
    } else if (id == "string") {
        return new Keyword(STRING);
    } else if (id == "float") {
        return new Keyword(FLOAT);
    } else if (id == "for") {
        return new Keyword(FOR);
    } else if (id == "while") {
        return new Keyword(WHILE);
    } else if (id == "if") {
        return new Keyword(IF);
    } else if (id == "else") {
        return new Keyword(ELSE);
    } else if (id == "true") {
        return new Keyword(TRUE);
    } else if (id == "false") {
        return new Keyword(FALSE);
    } else if (id == "break") {
        return new Keyword(BREAK);
    } else if (id == "continue") {
        return new Keyword(CONTINUE);
    } else if (id == "return") {
        return new Keyword(RETURN);
    } else if (id == "void") {
        return new Keyword(VOID);
    } else if (id == "main") {
        return new Keyword(MAIN);
    } else if (id == "do") {
        return new Keyword(DO);
    } else {
        return new Identifier(id);
    }
}

Token *resolveInteger(std::string integer_string) {
    int64_t ans = 0;
    for (char c : integer_string) {
        ans *= 10LL;
        ans += (c - '0');
    }
    return new IntegerLiteral(ans);
}

Token *resolveFloat(std::string float_string) {
    long double ans = 0;
    int i = 0;
    for (; i < float_string.length(); i++) {
        char c = float_string[i];
        if (c == '.') {
            i++;
            break;
        }
        ans *= 10LL;
        ans += (c - '0');
    }
    long double mult = 0.1;
    for (; i < float_string.length(); i++) {
        int d = float_string[i] - '0';
        ans += d * mult;
        mult /= 10LL;
    }
    return new FloatingPointLiteral(ans);
}

std::string Operator::to_terminal_string() {
    return OperatorTerminalNames[operatorType];
}

std::string Keyword::to_terminal_string() {
    return KeywordTerminalNames[keywordType];
}

std::string Delimiter::to_terminal_string() {
    return DelimiterTerminalNames[delimiterType];
}

std::string Identifier::to_terminal_string() { return "TK-VAR-ID"; }

std::string FloatingPointLiteral::to_terminal_string() {
    return "TK-FLOAT-LITERAL";
}

std::string IntegerLiteral::to_terminal_string() { return "TK-INT-LITERAL"; }
std::string StringLiteral::to_terminal_string() { return "TK-STRING-LITERAL"; }