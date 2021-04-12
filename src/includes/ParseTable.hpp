#pragma once
#include "GrammarRule.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class ParseTable {
  public:
    std::vector<std::map<std::string, std::pair<char, int>>> transitions;
    ParseTable(std::string filename);
};