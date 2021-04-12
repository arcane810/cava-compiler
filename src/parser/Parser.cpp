#include "Parser.hpp"
#include <cassert>
#include <cstring>
#include <iostream>

bool parse_file(FILE *inputFile) {
    std::stack<std::string> st;
    st.push("0");
    Lexer lexer = Lexer(inputFile);
    Token *newToken;
    ParseTable parse_table = ParseTable("src/parser/parse_table");
    std::vector<GrammarRule> grammar_rules =
        grammarRules("src/parser/grammar_lalr.txt");

    while ((newToken = lexer.nextToken()) != NULL) {
        std::string token_element;
        switch (newToken->tokenType) {
        case KEYWORD:
            token_element = ((Keyword *)newToken)->to_terminal_string();
            break;
        case IDENTIFIER:
            token_element = ((Identifier *)newToken)->to_terminal_string();
            break;
        case INTEGER_LITERAL:
            token_element = ((IntegerLiteral *)newToken)->to_terminal_string();
            break;
        case FLOATING_POINT_LITERAL:
            token_element =
                ((FloatingPointLiteral *)newToken)->to_terminal_string();
            break;
        case OPERATOR:
            token_element = ((Operator *)newToken)->to_terminal_string();
            break;
        case STRING_LITERAL:
            token_element = ((StringLiteral *)newToken)->to_terminal_string();
            break;
        case DELIMITER:
            token_element = ((Delimiter *)newToken)->to_terminal_string();
            break;
        case ERROR_TOKEN:
            throw "Error Token Encountered";
            break;
        default:
            break;
        }
        std::pair<char, int> operation =
            parse_table.transitions[stoi(st.top())][token_element];
        std::cout << token_element << std::endl;
        while (operation.first == 'r') {
            int to_pop = 2 * grammar_rules[operation.second].rhs.size();

            for (int i = 0; i < to_pop; i++) {
                if (st.empty())
                    return false;
                st.pop();
            }
            int prev_state = stoi(st.top());
            st.push(grammar_rules[operation.second].lhs);
            st.push(std::to_string(
                parse_table.transitions[prev_state][st.top()].second));
            operation = parse_table.transitions[stoi(st.top())][token_element];
        }
        if (operation.first == 's') {
            st.push(token_element);
            st.push(std::to_string(operation.second));
        } else if (operation.first == 'a') {
            return true;
        } else {
            throw "parse error";
        }
    }

    std::string token_element = "$";
    std::pair<char, int> operation =
        parse_table.transitions[stoi(st.top())][token_element];

    while (operation.first == 'r') {
        int to_pop = 2 * grammar_rules[operation.second].rhs.size();

        for (int i = 0; i < to_pop; i++) {
            if (st.empty()) {
                return false;
            }
            st.pop();
        }
        int prev_state = stoi(st.top());
        st.push(grammar_rules[operation.second].lhs);
        st.push(std::to_string(
            parse_table.transitions[prev_state][st.top()].second));
        operation = parse_table.transitions[stoi(st.top())][token_element];
    }
    if (operation.first == 'a') {
        return true;
    } else {
        return false;
    }

    return false;
}