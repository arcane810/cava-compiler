#include "ParseTable.hpp"
#include <iostream>

#include "Parser.hpp"
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "cava-parse: fatal error: no input file\n";
        std::cerr << "Usage: cava-parse [input file]\n";
    }

    FILE *inputFile;

    // Read file name from arguments
    inputFile = fopen(argv[1], "r");

    if (inputFile == NULL) {
        std::cerr << "invalid input file\n";
        return 1;
    }
    try {
        std::cout << parse_file(inputFile);
    } catch (...) {
        std::cout << "Parse Error";
    }
    return 0;
}