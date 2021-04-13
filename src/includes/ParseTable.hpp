/** @file */

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

/**
 * A class to store the LR parse table
 */
class ParseTable {
  public:
    /**
     * A vector of maps to store the transitions.
     * A map stored at index i stores the transitions from that state
     */
    std::vector<std::map<std::string, std::pair<char, int>>> transitions;
    /**
     * A constructor which takes in the path to the parse table and parses the
     * file into the transitions variable
     */
    ParseTable(std::string filename);
};