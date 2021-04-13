/** @file */

#pragma once
#include "Lexer.hpp"
#include "ParseTable.hpp"
#include "ParseTree.hpp"
#include <algorithm>
#include <stack>

/**
 * A function to parse the code in the file passed
 * @param file pointer to the file containing the code
 */
ParseTree *parse_file(FILE *file);