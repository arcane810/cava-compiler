/**
 * Group 12 - Cava
 * Akul Singhal - 2018A7PS0193H
 * Rohan Daniel - 2018A7PS0584H
 * Pranav Rajagopalan - 2018A7PS0177H
 * Akshay Tiwari - 2018A7PS0201H
 */

#include "Lexer.hpp"
#include "Token.hpp"
#include <iomanip>
/**
 * The driver function for the lexer. It initializes the lexer object, consumes
 * and prints tokens produced by the lexer.
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "cava-lex: fatal error: no input file\n";
        std::cerr << "Usage: cava-lex [input file]\n";
    }

    FILE *inputFile;

    // Read file name from arguments
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        std::cerr << "invalid input file\n";
        return 1;
    }

    // Init Token object.
    Lexer lexer = Lexer(inputFile);
    std::vector<Token *> tokens;
    // Consume tokens produced
    Token *newToken = lexer.nextToken();
    while (newToken != NULL) {
        std::pair<int, int> pos = lexer.getTokenStartPosition();
        std::cout << "Token At " << pos.first << ":" << pos.second << " < "
                  << TokenTypeNames[(int)newToken->tokenType] << ", ";
        switch (newToken->tokenType) {
        case KEYWORD:
            std::cout << KeywordNames[(int)((Keyword *)newToken)->keywordType];
            break;
        case IDENTIFIER:
            std::cout << ((Identifier *)newToken)->identifier_name;
            break;
        case INTEGER_LITERAL:
            std::cout << ((IntegerLiteral *)newToken)->value;
            break;
        case FLOATING_POINT_LITERAL:
            std::cout << std::setprecision(13)
                      << ((FloatingPointLiteral *)newToken)->value;
            break;
        case OPERATOR:
            std::cout
                << OperatorNames[(int)((Operator *)newToken)->operatorType];
            break;
        case STRING_LITERAL:
            std::cout << ((StringLiteral *)newToken)->value;
            break;
        case DELIMITER:
            std::cout
                << DelimiterNames[(int)((Delimiter *)newToken)->delimiterType];
            break;
        case ERROR_TOKEN:
            std::cout << ((ErrorToken *)newToken)->error_message;
            break;
        default:
            break;
        }
        std::cout << " >\n";
        newToken = lexer.nextToken();
    }
}