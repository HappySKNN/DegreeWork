#include "../headers/king_boost_test.h"
#include "../headers/routines.h"
#include <sys/time.h>

using namespace std;

void king_boost(const size_t &_size, const string &_file) {
    struct timeval start{}, end{};

    adj_list array = read_adjacency_list(_file);

    Graph G(_size);

    for (auto &i: array) {
        for (auto &j: i.second) {
            add_edge(i.first, j, G);
        }
    }

    graph_traits<Graph>::vertex_iterator ui, ui_end;

    property_map<Graph, vertex_degree_t>::type deg = get(vertex_degree, G);

    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui) {
        deg[*ui] = degree(*ui, G);
    }

    property_map<Graph, vertex_index_t>::type index_map = get(vertex_index, G);

    cout << "King Boost ordering:" << endl;

// -- UNCOMMENT IF BANDWIDTH OUTPUT IS NEEDED -- //
//    cout << " >>> Bandwidth before: " << bandwidth(G) << endl;

    vector<Vertex> inv_perm(num_vertices(G));
    vector<size_type> perm(num_vertices(G));

    gettimeofday(&start, nullptr);
    king_ordering(G, inv_perm.rbegin(), get(vertex_color, G), make_degree_map(G), get(vertex_index, G));
    gettimeofday(&end, nullptr);

// -- UNCOMMENT IF YOU NEED TO CHANGE INDEXES -- //
//    for (size_type c = 0; c != inv_perm.size(); ++c) {
//        perm[index_map[inv_perm[c]]] = c;
//    }

// -- UNCOMMENT IF BANDWIDTH OUTPUT IS NEEDED -- //
//    cout << " >>> Bandwidth after: " << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0])) << endl;

    double time =
            (static_cast<double> ((end.tv_sec * 1e6 + end.tv_usec) - (start.tv_sec * 1e6 + start.tv_usec))) * 1e-6;

    cout << " >>> ExecutingTime: " << time << " sec" << "\n\n";
}
