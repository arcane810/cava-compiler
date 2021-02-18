#include "Lexer.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "cava-lex: fatal error: no input file\n";
        std::cerr << "Usage: cava-lex [input file]\n";
    }

    FILE *inputFile;
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        std::cerr << "invalid input file\n";
        return 1;
    }
    Lexer lexer = Lexer(inputFile);
    std::vector<Token *> tokens;
    Token *newToken = lexer.nextToken();
    while (newToken != NULL) {
        // std::cout << "IN LOOP\n";
        switch (newToken->tokenType) {
        case IDENTIFIER:
            std::cout << ((Identifier *)newToken)->identifier_name << "\n";
            break;
        case INTEGER_LITERAL:
            std::cout << ((IntegerLiteral *)newToken)->value << "\n";
            break;
        case OPERATOR:
            std::cout << ((Operator *)newToken)->operatorString << "\n";
            break;

        default:
            break;
        }
        newToken = lexer.nextToken();
    }
}