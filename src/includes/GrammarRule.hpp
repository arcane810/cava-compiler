#pragma once

#include "Token.hpp"
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

class GrammarRule {

  public:
    GrammarRule(std::string);
    std::string lhs;
    std::vector<std::string> rhs;
};

std::vector<GrammarRule> grammarRules(std::string grammar_file);