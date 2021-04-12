#include "ParseTable.hpp"

ParseTable::ParseTable(std::string filename) {
    std::ifstream input_file_stream(filename);
    std::string cur_line_string;
    std::vector<std::string> elements;
    int current_line = 0;
    while (std::getline(input_file_stream, cur_line_string)) {
        std::stringstream input_line(cur_line_string);
        std::string next_id;
        int current_column = 0;
        std::map<std::string, std::pair<char, int>> cur_state_transistions;
        while (std::getline(input_line, next_id, '\t')) {
            if (current_line == 0) {
                elements.push_back(next_id);
            } else if (next_id != " ") {
                char operation_type = 'g';
                int next_int;
                if (next_id[0] == 'r' || next_id[0] == 's' ||
                    next_id[0] == 'a') {
                    operation_type = next_id[0];
                    if (next_id[0] == 'a') {
                        next_int = 0;
                    } else {
                        next_int =
                            stoi(next_id.substr(1, next_id.length() - 1));
                    }
                } else {
                    next_int = stoi(next_id);
                }
                cur_state_transistions[elements[current_column]] = {
                    operation_type, next_int};
            }
            // std::cout << current_line << "\t" << current_column << "\t"
            //           << ((next_id == " ") ? "NONE" : next_id) << std::endl;
            current_column++;
        }
        if (current_line > 0)
            transitions.push_back(cur_state_transistions);
        current_line++;
    }
}