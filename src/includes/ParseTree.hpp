/** @file */

#include "Token.hpp"
#include <iostream>
#include <utility>
#include <vector>

/**
 * A class to store the parse tree as nodes
 */
class ParseTree {
    /**
     *  If the Node represents a token this contains the pointer to the token
     * object, otherwise it stores nullptr
     */
    Token *token;

  public:
    /**
     * string representation of the token (which was used in
     * parsing)
     */
    std::string token_string;
    /**
     * A vector containing the pointers to the children of the parse tree
     */
    std::vector<ParseTree *> children;
    /**
     * Constructor which makes a parse tree node without any children
     * @param token contains the token for token nodes, nullptr otherwise
     * @param token_string string representation of the token (which was used in
     * parsing)
     */
    ParseTree(Token *token, std::string token_string);
    /**
     * Constructor which makes a parse tree node with children
     * @param token contains the token for token nodes, nullptr otherwise
     * @param token_string string representation of the token (which was used in
     * parsing)
     * @param children vector of pointers to children
     */
    ParseTree(Token *token, std::string token_string,
              std::vector<ParseTree *> children);
    /**
     * A method to add a child to the node
     * @param child pointer to the child that is to be added
     */
    void addChild(ParseTree *child);
    /**
     * A function used to print the inorder traversal of the tree
     */
    void inorder_traversal();
    /**
     * A function used to create a graph in form of edges and labels which can
     * be used with libraries such as graph viz
     * @param edges a vector of edges passed by reference to which edges will be
     * added
     * @param node_num a node number for the nodes (should be 0 when called
     * externally)
     * @param labels a vector which stores the string labels of the nodes
     */
    void inorder_traversal_g(std::vector<std::pair<int, int>> &edges,
                             int &node_num, std::vector<std::string> &labels);
};