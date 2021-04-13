/** @file */

#pragma once
#include <string>

// enum for Operator Types
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
// String array for enum to string mapping of Tokentypes
const std::string TokenTypeNames[] = {"Identifier",
                                      "Operator",
                                      "Keyword",
                                      "String Literal",
                                      "Floating Point Literal",
                                      "Integer Literal",
                                      "Delimiter",
                                      "Error"};

// Base Class for all types of Tokens
class Token {
  public:
    // Type of the Token
    TokenType tokenType;
    /**
     * Constructor. Initializes the tokenType to the passed parameter
     *
     * @param tokenType The token type
     */
    Token(TokenType tokenType);
    /**
     * A function to get a presentable string form of the token
     */
    std::string toString();
    /**
     * A function to get a string which is used in parsing
     */
    std::string toParseString();
};

// enum for Operator Types
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

// String array for enum to string mapping of operator types
const std::string OperatorNames[] = {
    "+",  "-",  "*",  "/",  "%",  "=", "==", "!=", "+=", "-=", "*=", "/=",
    "%=", "++", "--", "&&", "||", "!", ">",  "<",  ">=", "<=", "?",  ":"};

// String array for enum to string (that is used in parsing) mapping of operator
// types
const std::string OperatorTerminalNames[] = {
    "TK-ADD",        "TK-SUB",        "TK-MUL",        "TK-DIV",
    "TK-MOD",        "TK-ASSIGN",     "TK-EQUAL",      "TK-NOTEQUAL",
    "TK-ADD-ASSIGN", "TK-SUB-ASSIGN", "TK-MUL-ASSIGN", "TK-DIV-ASSIGN",
    "TK-MOD-ASSIGN", "TK-INCREMENT",  "TK-DECREMENT",  "TK-LOGICAL-AND",
    "TK-LOGICAL-OR", "TK-NOT",        "TK-GREATER",    "TK-LESSER",
    "TK-GREATEREQ",  "TK-LESSEREQ",   "TK-QUESTION",   "TK-COLON"};

// Class for Operator tokens
class Operator : public Token {
  public:
    // Type of the Operator
    OperatorType operatorType;

    /**
     * Constructor. Initializes the operatorType to the passed parameter
     *
     * @param operatorType The operator type
     */
    Operator(OperatorType operatorType);
};

// enum for Keyword Types
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
    VOID,
    MAIN,
    DO
};

// String array for enum to string mapping of keyword types
const std::string KeywordNames[] = {
    "int",  "bool",  "string", "float",    "for",    "while", "if",   "else",
    "true", "false", "break",  "continue", "return", "void",  "main", "do"};

// String array for enum to string (that is used in parsing) mapping of keyword
// types
const std::string KeywordTerminalNames[] = {
    "TK-INT",    "TK-BOOL", "TK-STRING", "TK-FLOAT", "TK-FOR",   "TK-WHILE",
    "TK-IF",     "TK-ELSE", "TK-TRUE",   "TK-FALSE", "TK-BREAK", "TK-CONTINUE",
    "TK-RETURN", "TK-VOID", "TK-MAIN",   "TK-DO"};

// Class for Keyword tokens
class Keyword : public Token {
  public:
    // Type of the Keyword
    KeywordType keywordType;
    /**
     * Constructor. Initializes the keywordType to the passed parameter
     *
     * @param keywordType The keyword type
     */
    Keyword(KeywordType keywordType);
};

// enum for Delimiter Types
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

// String array for enum to string mapping of delimiter types
const std::string DelimiterNames[] = {";", ",", "(", ")", "{", "}", "[", "]"};

// String array for enum to string (that is used in parsing) mapping of
// delimiter types
const std::string DelimiterTerminalNames[] = {"TK-SC",  "TK-COMMA", "TK-RBO",
                                              "TK-RBC", "TK-CBO",   "TK-CBC",
                                              "TK-SBO", "TK-SBC"};

/**
 * Class for Delimiter tokens
 */
class Delimiter : public Token {
  public:
    // Type of Delimiter
    DelimiterType delimiterType;

    /**
     * Constructor. Initializes the delimiterType to the passed parameter
     *
     * @param delimiterType The delimiter type
     */
    Delimiter(DelimiterType delimiterType);
};

/**
 * Class for Identifier tokens
 */
class Identifier : public Token {
  public:
    // String containing the identifier name
    std::string identifier_name;
    /**
     * Constructor. Initializes the identifier_name to the passed parameter
     *
     * @param identifier_name The identifier name
     */
    Identifier(std::string identifier_name);
};

/**
 * Class for Float tokens
 */
class FloatingPointLiteral : public Token {
  public:
    // Contains the value of the float
    long double value;
    /**
     * Constructor. Initializes the value to the passed parameter
     *
     * @param value The value
     */
    FloatingPointLiteral(long double value);
};

/**
 * Class for Integer tokens
 */
class IntegerLiteral : public Token {
  public:
    // Contains the value of the integer
    int64_t value;
    /**
     * Constructor. Initializes the value to the passed parameter
     *
     * @param value The value
     */
    IntegerLiteral(int64_t value);
};

/**
 * Class for String tokens
 */
class StringLiteral : public Token {
  public:
    // Contains the string
    std::string value;
    /**
     * Constructor. Initializes the string to the passed parameter
     *
     * @param value The string
     */
    StringLiteral(std::string value);
};

/**
 * Class for Error tokens
 */
class ErrorToken : public Token {
  public:
    // String containing the error message
    std::string error_message;
    /**
     * Constructor. Initializes the error_message to the passed parameter
     *
     * @param error_message the error message
     */
    ErrorToken(std::string error_message);
};

/**
 * A function that returns an identifier or a keyword if the name matches a
 * keyword
 * @param id the name of identifier/keyword
 * @return a pointer to the identifier/keyword
 */
Token *resolveIdentifier(std::string id);

/**
 * A function that returns an integer token with its value parsed from the
 * string
 * @param integer_string the integer formatted as a string
 * @return a pointer to the integer token
 */
Token *resolveInteger(std::string integer_string);

/**
 * A function that returns an float token with its value parsed from the string
 * @param float_string the float formatted as a string
 * @return a pointer to the float token
 */
Token *resolveFloat(std::string float_string);