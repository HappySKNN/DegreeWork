#ifndef REVERSE_CUTHILL_MCKEE_ORDERING_APPROXIMATE_MINIMUM_DEGREE_TEST_H
#define REVERSE_CUTHILL_MCKEE_ORDERING_APPROXIMATE_MINIMUM_DEGREE_TEST_H

extern "C" {
#include "amd.h"
}

#include <iostream>
#include <vector>

typedef std::vector<std::pair<size_t, std::vector<size_t>>> adj_list;

int **read_matrix(const char *_file, int _size);

void approximate_minimum_degree(const char *_file, int _size);

#endif //REVERSE_CUTHILL_MCKEE_ORDERING_APPROXIMATE_MINIMUM_DEGREE_TEST_H
