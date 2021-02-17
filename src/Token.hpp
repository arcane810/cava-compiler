#pragma once
#include <string>

enum TokenType {
    IDENTIFIER,
    OPERATOR,
    KEYWORD,
    STRING_LITERAL,
    FLOATING_POINT_LITERAL,
    INTEGER_LITERAL
};

class Token {
  public:
    TokenType tokenType;
    Token(TokenType tokenType);
};

enum OperatorType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    ASSIGNMENT,
    EQUAL_TO,
    NOT_EQUAL,
    MODULO,
    ADD_EQUAL,
    SUB_EQUAL,
    MUL_EQUAL,
    DIV_EQUAL,
    MOD_EQUAL,
    INCREMENT,
    DECREMENT,
    BOOL_AND,
    BOOL_OR,
    BOOL_NOT,
    GREATER,
    LESSER,
    GREAT_EQUAL,
    LESS_EQUAL,
    TERTIARY_Q,
    TERTIARY_C
};

class Operator : public Token {
    OperatorType operatorType;
};

enum KeywordType {
    INT,
    BOOL,
    STRING,
    FLOAT,
    FOR,
    WHILE,
    IF,
    ELSE,
    TRUE,
    FALSE,
    BREAK,
    CONTINUE
};

class Keyword : public Token {
  public:
    KeywordType keywordType;
    Keyword(KeywordType keywordType);
};

class Identifier : public Token {
  public:
    std::string identifier_name;
    Identifier(std::string identifier_name);
};

class FloatingPointLiteral : public Token {
    long double value;
};

class IntegerLiteral : public Token {
    int64_t value;
};

class StringLiteral : public Token {
    std::string value;
};

Token *resolveIdentifier(std::string id);