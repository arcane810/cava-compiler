/** @file */

#include "GrammarRule.hpp"
#include <iostream>

GrammarRule::GrammarRule(std::string rule_string) {
    std::stringstream input_line(rule_string);
    input_line >> lhs;
    std::string temp;
    input_line >> temp;
    while (input_line >> temp) {
        // std::cout << temp << std::endl;
        if (temp == "\'\'")
            continue;
        rhs.push_back(temp);
    }
}

std::vector<GrammarRule> grammarRules(std::string grammar_file) {
    std::vector<GrammarRule> grammar_rules;
    std::string rule_string;
    std::ifstream grammar_file_stream(grammar_file);
    while (std::getline(grammar_file_stream, rule_string)) {
        if (rule_string == "")
            continue;
        grammar_rules.push_back(GrammarRule(rule_string));
    }
    return grammar_rules;
}