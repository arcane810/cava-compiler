/** @file */
#pragma once

#include "Token.hpp"
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * A class to represent a grammar rule
 */
class GrammarRule {
  public:
    /**
     * Constructor which parses a string of the form lhs -> rhs (space
     * separated)
     * @param rule_string the string containing the grammar rule
     */
    GrammarRule(std::string rule_string);
    /// Left hand side of the grammar rule
    std::string lhs;
    /// A vector containing the elements of the right hand side of the rule
    std::vector<std::string> rhs;
};

/**
 * A function which takes in the path of a file to the grammar rules and parses
 * each line as a grammar rule and stores it into a vector
 * @param grammar_file the path to the grammar file
 */
std::vector<GrammarRule> grammarRules(std::string grammar_file);