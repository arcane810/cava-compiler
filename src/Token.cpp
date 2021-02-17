#include "Token.hpp"

Token::Token(TokenType tokenType) : tokenType(tokenType) {}

Keyword::Keyword(KeywordType keywordType)
    : Token(KEYWORD), keywordType(keywordType) {}

Identifier::Identifier(std::string identifier_name)
    : Token(IDENTIFIER), identifier_name(identifier_name) {}

IntegerLiteral::IntegerLiteral(int64_t value)
    : Token(INTEGER_LITERAL), value(value) {}

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