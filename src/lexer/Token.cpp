/** @file */

#include "Token.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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
    for (; i < (int)float_string.length(); i++) {
        char c = float_string[i];
        if (c == '.') {
            i++;
            break;
        }
        ans *= 10LL;
        ans += (c - '0');
    }
    long double mult = 0.1;
    for (; i < (int)float_string.length(); i++) {
        int d = float_string[i] - '0';
        ans += d * mult;
        mult /= 10LL;
    }
    return new FloatingPointLiteral(ans);
}

std::string Token::toString() {
    std::stringstream ss;
    switch (tokenType) {
    case KEYWORD:
        ss << KeywordNames[(int)((Keyword *)this)->keywordType];
        break;
    case IDENTIFIER:
        ss << ((Identifier *)this)->identifier_name;
        break;
    case INTEGER_LITERAL:
        ss << ((IntegerLiteral *)this)->value;
        break;
    case FLOATING_POINT_LITERAL:
        ss << std::setprecision(13) << ((FloatingPointLiteral *)this)->value;
        break;
    case OPERATOR:
        ss << OperatorNames[(int)((Operator *)this)->operatorType];
        break;
    case STRING_LITERAL:
        ss << ((StringLiteral *)this)->value;
        break;
    case DELIMITER:
        ss << DelimiterNames[(int)((Delimiter *)this)->delimiterType];
        break;
    case ERROR_TOKEN:
        ss << ((ErrorToken *)this)->error_message;
        break;
    default:
        break;
    }
    return ss.str();
}

std::string Token::toParseString() {
    std::string token_element;
    switch (tokenType) {
    case KEYWORD:
        token_element = KeywordTerminalNames[((Keyword *)this)->keywordType];
        break;
    case IDENTIFIER:
        token_element = "TK-VAR-ID";
        break;
    case INTEGER_LITERAL:
        token_element = "TK-INT-LITERAL";
        break;
    case FLOATING_POINT_LITERAL:
        token_element = "TK-FLOAT-LITERAL";
        break;
    case OPERATOR:
        token_element = OperatorTerminalNames[((Operator *)this)->operatorType];
        break;
    case STRING_LITERAL:
        token_element = "TK-STRING-LITERAL";
        break;
    case DELIMITER:
        token_element =
            DelimiterTerminalNames[((Delimiter *)this)->delimiterType];
        break;
    case ERROR_TOKEN:
        throw "Error Token Encountered";
        break;
    default:
        break;
    }
    return token_element;
}