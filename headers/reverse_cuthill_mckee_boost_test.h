#ifndef REVERSE_CUTHILL_MCKEE_ORDERING_REVERSE_CUTHILL_MCKEE_BOOST_TEST_H
#define REVERSE_CUTHILL_MCKEE_ORDERING_REVERSE_CUTHILL_MCKEE_BOOST_TEST_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/king_ordering.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>
#include <boost/graph/cuthill_mckee_ordering.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_color_t, default_color_type,
        property<vertex_degree_t, int>>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertices_size_type size_type;

typedef std::vector<std::pair<size_t, std::vector<size_t>>> adj_list;

void reverse_cuthill_mckee_boost(const size_t &_size, const std::string &_file);

#endif