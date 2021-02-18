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
    ERROR_TOKEN
};

const std::string TokenTypeNames[] = {"Identifier",
                                      "Operator",
                                      "Keyword",
                                      "String Literal",
                                      "Floating Point Literal",
                                      "Integer Literal",
                                      "Delimiter",
                                      "Error"};

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
    GREATER_EQUAL,
    LESSER_EQUAL,
    TERTIARY_Q,
    TERTIARY_C
};

const std::string OperatorNames[] = {
    "+",  "-",  "*",  "/",  "%",  "=", "==", "!=", "+=", "-=", "*=", "/=",
    "%=", "++", "--", "&&", "||", "!", ">",  "<",  ">=", "<=", "?",  ":"};

class Operator : public Token {
  public:
    OperatorType operatorType;
    Operator(OperatorType operatorType);
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
    CONTINUE,
    RETURN,
    VOID
};
const std::string KeywordNames[] = {
    "int",  "bool", "string", "float", "for",      "while",  "if",
    "else", "true", "false",  "break", "continue", "return", "void"};

class Keyword : public Token {
  public:
    KeywordType keywordType;
    Keyword(KeywordType keywordType);
};

enum DelimiterType {
    SEMICOLON,
    COMMA,
    PARANTHESES_OPEN,
    PARANTHESES_CLOSE,
    BRACE_OPEN,
    BRACE_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE
};
const std::string DelimiterNames[] = {";", ",", "(", ")", "{", "}", "[", "]"};

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
  public:
    long double value;
    FloatingPointLiteral(long double value);
};

class IntegerLiteral : public Token {
  public:
    int64_t value;
    IntegerLiteral(int64_t value);
};

class StringLiteral : public Token {
  public:
    std::string value;
    StringLiteral(std::string value);
};

class ErrorToken : public Token {
  public:
    std::string error_message;
    ErrorToken(std::string error_message);
};

Token *resolveIdentifier(std::string id);
Token *resolveInteger(std::string integer_string);
Token *resolveFloat(std::string float_string);