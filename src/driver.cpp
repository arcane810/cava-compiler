#include "Lexer.hpp"
#include "Token.hpp"
#include <iomanip>

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
        std::pair<int, int> pos = lexer.getTokenStartPosition();
        std::cout << "Token At " << pos.first << ":" << pos.second << " ";
        switch (newToken->tokenType) {

        case KEYWORD:
            std::cout << KeywordNames[(int)((Keyword *)newToken)->keywordType]
                      << "\n";
            break;
        case IDENTIFIER:
            std::cout << ((Identifier *)newToken)->identifier_name << "\n";
            break;
        case INTEGER_LITERAL:
            std::cout << ((IntegerLiteral *)newToken)->value << "\n";
            break;
        case FLOATING_POINT_LITERAL:
            std::cout << std::setprecision(13)
                      << ((FloatingPointLiteral *)newToken)->value << "\n";
            break;
        case OPERATOR:
            std::cout
                << OperatorNames[(int)((Operator *)newToken)->operatorType]
                << "\n";
            break;
        case STRING_LITERAL:
            std::cout << ((StringLiteral *)newToken)->value << "\n";
            break;
        case DELIMITER:
            std::cout
                << DelimiterNames[(int)((Delimiter *)newToken)->delimiterType]
                << "\n";
            break;
        case ERROR_TOKEN:
            std::cout << ((ErrorToken *)newToken)->error_message << "\n";
            break;
        default:
            break;
        }
        newToken = lexer.nextToken();
    }
}