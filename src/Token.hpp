#pragma once
#include <string>

enum TokenType {
    IDENTIFIER,
    OPERATOR,
    KEYWORD,
    STRING_LITERAL,
    FLOATING_POINT_LITERAL,
    INTEGER_LITERAL,
    DELIMITER,
    UNIDENTIFIED_TOKEN
};

class Token {
  public:
    int char_number;
    int line_number;
    TokenType tokenType;
    Token(TokenType tokenType);
};

enum OperatorType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,
    ASSIGNMENT,
    EQUAL_TO,
    NOT_EQUAL_TO,
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
  public:
    OperatorType operatorType;
    std::string operatorString;
    Operator(OperatorType operatorType, std::string operatorString);
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

enum DelimiterType {
    SEMICOLON,
    COMMA,
    PARANTHESES_OPEN,
    PARANTHESIS_CLOSE,
    BRACE_OPEN,
    BRACE_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE
};

class Delimiter : public Token {
  public:
    DelimiterType delimiterType;
    Delimiter(DelimiterType delimiterType);
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
  public:
    int64_t value;
    IntegerLiteral(int64_t value);
};

class StringLiteral : public Token {
    std::string value;
};

class UnidentifiedToken : public Token {
    std::string value;
};

Token *resolveIdentifier(std::string id);
Token *resolveInteger(std::string integer_string);