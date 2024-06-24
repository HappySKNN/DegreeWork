#include "../headers/routines.h"
#include "../headers/reverse_cuthill_mckee.h"
#include "../headers/reverse_cuthill_mckee_boost_test.h"
#include "../headers/king_boost_test.h"
#include "../headers/approximate_minimum_degree_test.h"

using namespace std;

const size_t size_matrix = 10;
const double sparse_p = 1.0 - (1.0 / size_matrix);
const string adj_file = "adj_input.txt";

int main() {
    adj_list array = generate_adjacency_list(size_matrix, sparse_p);
    //adj_list array = read_adjacency_list(adj_file);
    write_adjacency_list(array, adj_file);
    //convert_to_triplets(adj_file, "bucky_7.txt");
    write_matrix(array, "input_matrix.txt", size_matrix);
    //reverse_cuthill_mckee(size_matrix, adj_file);
    //reverse_cuthill_mckee_boost(size_matrix, adj_file);
    //king_boost(size_matrix, adj_file);
    //approximate_minimum_degree(adj_file.c_str(), size_matrix);
}
