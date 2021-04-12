#pragma once
#include "Lexer.hpp"
#include "ParseTable.hpp"
#include "ParseTree.hpp"
#include <algorithm>
#include <stack>

ParseTree *parse_file(FILE *file);