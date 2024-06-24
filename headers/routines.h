#ifndef REVERSE_CUTHILL_MCKEE_ORDERING_ROUTINES_H
#define REVERSE_CUTHILL_MCKEE_ORDERING_ROUTINES_H

#include <iostream>
#include <vector>

typedef std::vector<std::pair<size_t, std::vector<size_t>>> adj_list;

adj_list generate_adjacency_list(const size_t &_size, const double &_sparse);

void write_adjacency_list(const adj_list &_array, const std::string &_file);

adj_list read_adjacency_list(const std::string &_file);

void write_matrix(const adj_list &_array, const std::string &_file, const size_t &_size);

void get_bandwidth(const adj_list &_array, const std::string &_prefix_text);

void convert_to_triplets(const std::string &_file_in, const std::string &_file_out);

#endif //REVERSE_CUTHILL_MCKEE_ORDERING_ROUTINES_H