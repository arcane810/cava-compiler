#include "Token.hpp"
#include <string>
#include <vector>

class Element {
    std::string identifier;
};

class NonTerminal : public Element {};

class Terminal : public Element {
    Token *token;
};

class GrammarRule {
    NonTerminal lhs;
    std::vector<Element *> rhs;

  public:
    GrammarRule(std::string);
};