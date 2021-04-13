/** @file */
/**
 * Group 12 - Cava
 * Akul Singhal - 2018A7PS0193H
 * Rohan Daniel - 2018A7PS0584H
 * Pranav Rajagopalan - 2018A7PS0177H
 * Akshay Tiwari - 2018A7PS0201H
 */

#include "ParseTable.hpp"
#include <iostream>

#include "Parser.hpp"
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

#include <boost/graph/graphviz.hpp>
#include <fstream>
using std::ofstream;

enum files_e { dax_h, yow_h, N };

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
    std::vector<std::pair<int, int>> edges;
    try {
        ParseTree *res = parse_file(inputFile);
        res->inorder_traversal();
        int node_num = 0;
        std::vector<std::string> labels;
        res->inorder_traversal_g(edges, node_num, labels);

        std::cout << edges.size() << "\n";

        // edges.push_back(std::make_pair(0,1));

        const int num_edges = edges.size();
        int weights[num_edges];
        std::fill(weights, weights + num_edges, 1);

        using namespace boost;

        typedef adjacency_list<vecS, vecS, directedS,
                               property<vertex_color_t, default_color_type>,
                               property<edge_weight_t, int>>
            Graph;
        Graph g(edges.begin(), edges.end(), weights, labels.size());
        ofstream outa;
        outa.open("g.dot");
        if (!outa) {
            std::cerr << "Error: file could not be opened" << std::endl;
            exit(1);
        }

        const char *name[labels.size()];
        for (int i = 0; i < labels.size(); i++) {
            name[i] = labels[i].c_str();
        }
        write_graphviz(outa, g, make_label_writer(name));
        outa.close();

    } catch (...) {
        std::cout << "Parse Error";
    }
    return 0;
}