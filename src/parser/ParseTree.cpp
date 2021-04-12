#include "ParseTree.hpp"

ParseTree::ParseTree(Token *token, std::string token_string)
    : token(token), token_string(token_string) {}
ParseTree::ParseTree(Token *token, std::string token_string,
                     std::vector<ParseTree *> children)
    : token(token), token_string(token_string), children(children) {}

void ParseTree::addChild(ParseTree *child) { children.push_back(child); }

void ParseTree::inorder_traversal() {
    std::cout << token_string << std::endl;
    for (auto it : children) {
        it->inorder_traversal();
    }
}