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