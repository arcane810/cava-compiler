#include "Token.hpp"
#include <iostream>
#include <vector>

class ParseTree {
    Token *token;

  public:
    ParseTree(Token *token, std::string token_string);
    ParseTree(Token *token, std::string token_string,
              std::vector<ParseTree *> children);
    void addChild(ParseTree *child);
    std::vector<ParseTree *> children;
    std::string token_string;
    void inorder_traversal();
};