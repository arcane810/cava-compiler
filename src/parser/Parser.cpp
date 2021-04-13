/** @file */

#include "Parser.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdlib.h>

ParseTree *parse_file(FILE *inputFile) {
    std::stack<std::pair<std::string, ParseTree *>> st;
    st.push({"0", nullptr});
    Lexer lexer = Lexer(inputFile);
    Token *newToken;
    ParseTable parse_table = ParseTable("src/parser/parse_table");
    std::vector<GrammarRule> grammar_rules =
        grammarRules("src/parser/grammar_lalr.txt");
    bool error_state = 0;
    while ((newToken = lexer.nextToken()) != NULL) {
        std::string token_element = newToken->toParseString();
        std::pair<char, int> operation =
            parse_table.transitions[stoi(st.top().first)][token_element];
        // std::cout << token_element << std::endl;
        while (operation.first == 'r') {
            error_state = 0;
            int to_pop = 2 * grammar_rules[operation.second].rhs.size();
            std::vector<ParseTree *> children;
            for (int i = 0; i < to_pop; i++) {
                if (st.empty())
                    return nullptr;
                if (st.top().second)
                    children.push_back(st.top().second);
                st.pop();
            }
            std::reverse(children.begin(), children.end());
            int prev_state = stoi(st.top().first);
            st.push({grammar_rules[operation.second].lhs,
                     new ParseTree(nullptr, grammar_rules[operation.second].lhs,
                                   children)});
            st.push({std::to_string(
                         parse_table.transitions[prev_state][st.top().first]
                             .second),
                     nullptr});
            operation =
                parse_table.transitions[stoi(st.top().first)][token_element];
        }
        if (operation.first == 's') {
            error_state = 0;
            st.push({token_element, new ParseTree(newToken, token_element)});
            st.push({std::to_string(operation.second), nullptr});
        } else {
            if (error_state)
                continue;
            std::cerr << "Error Unexpected token: " << newToken->toString()
                      << std::endl;
            error_state = 1;
        }
    }

    std::string token_element = "$";
    std::pair<char, int> operation =
        parse_table.transitions[stoi(st.top().first)][token_element];

    while (operation.first == 'r') {
        error_state = 0;
        int to_pop = 2 * grammar_rules[operation.second].rhs.size();
        std::vector<ParseTree *> children;
        for (int i = 0; i < to_pop; i++) {
            if (st.empty())
                return nullptr;
            if (st.top().second)
                children.push_back(st.top().second);
            st.pop();
        }
        std::reverse(children.begin(), children.end());
        int prev_state = stoi(st.top().first);
        st.push({grammar_rules[operation.second].lhs,
                 new ParseTree(nullptr, grammar_rules[operation.second].lhs,
                               children)});
        st.push(
            {std::to_string(
                 parse_table.transitions[prev_state][st.top().first].second),
             nullptr});
        operation =
            parse_table.transitions[stoi(st.top().first)][token_element];
    }
    if (operation.first == 'a') {
        st.pop();
        return st.top().second;
    } else {
        std::cerr << "Unsuccessful Parsing" << std::endl;
        st.pop();
        return st.top().second;
    }

    return nullptr;
}