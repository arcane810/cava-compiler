#include "Token.hpp"
#include <iostream>
#include <vector>
#include <utility>


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
    void inorder_traversal_g(std::vector<std::pair<int,int> > &edges, int &node_num, std::vector<std::string> &labels);
};