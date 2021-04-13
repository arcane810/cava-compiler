/** @file */

#include "ParseTree.hpp"

ParseTree::ParseTree(Token *token, std::string token_string)
    : token(token), token_string(token_string) {}
ParseTree::ParseTree(Token *token, std::string token_string,
                     std::vector<ParseTree *> children)
    : token(token), token_string(token_string), children(children) {}

void ParseTree::addChild(ParseTree *child) { children.push_back(child); }

void ParseTree::inorder_traversal() {
    std::cout << token_string;
    if (token) {
        std::cout << " " << token->toString();
    }
    std::cout << std::endl;
    for (auto it : children) {
        it->inorder_traversal();
    }
}
void ParseTree::inorder_traversal_g(std::vector<std::pair<int, int>> &edges,
                                    int &node_num,
                                    std::vector<std::string> &labels) {
    // std::cout << token_string << std::endl;
    std::string label = token_string;
    if (token) {
        label += "\n";
        label += token->toString();
    }
    int cnn = node_num;
    labels.push_back(label);
    for (auto it : children) {
        node_num++;
        edges.push_back(std::make_pair(cnn, node_num));
        // std::cout<<token_string<<" "<<it->token_string<<"\n";
        // edges.push_back(std::make_pair(token_string,it->token_string));
        it->inorder_traversal_g(edges, node_num, labels);
    }
}