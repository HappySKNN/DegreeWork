#ifndef REVERSE_CUTHILL_MCKEE_ORDERING_REVERSE_CUTHILL_MCKEE_H
#define REVERSE_CUTHILL_MCKEE_ORDERING_REVERSE_CUTHILL_MCKEE_H

#include <iostream>
#include <vector>

typedef std::vector<std::pair<size_t, std::vector<size_t>>> adj_list;

std::vector<size_t> get_degrees(const adj_list &_array, const size_t &_size, std::vector<bool> &_visited,
                                std::vector<size_t> &R, size_t &_node_index, size_t &_insertion_index);

std::vector<size_t> get_permutation_array(const adj_list &_array, const size_t &_size);

void reorder_matrix(adj_list &_array, const std::vector<size_t> &R);

void reverse_cuthill_mckee(const size_t &_size, const std::string &_file);

#endif //REVERSE_CUTHILL_MCKEE_ORDERING_REVERSE_CUTHILL_MCKEE_H