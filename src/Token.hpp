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
    TokenType tokenType;
};

enum OperatorType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    ASSIGNMENT,
    EQUIALITY,
};

class Operator : public Token {
    OperatorType operatorType;
};

enum KeywordType {
    INT,
    FLOAT,
    BOOL,
    STRING,
    WHILE,
    IF,
    ELSE,
    TRUE,
    FALSE,
    BREAK,
    FOR,
    CONTINUE
};

class Keyword : public Token {
    KeywordType keywordType;
};

class Identifier : public Token {
    std::string identifier_name;
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