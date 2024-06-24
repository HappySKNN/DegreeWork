#include "../headers/reverse_cuthill_mckee.h"
#include "../headers/routines.h"
#include <queue>
#include <map>
#include <algorithm>
#include <sys/time.h>

using namespace std;

vector<size_t> get_degrees(const adj_list &_array, const size_t &_size, vector<bool> &_visited, vector<size_t> &R,
                           size_t &_node_index, size_t &_insertion_index) {
    vector<size_t> degrees(_size);

    for (size_t i = 0; i < _size; i++) {
        degrees[i] = _array[i].second.size();
        if (degrees[i] == 0) {
            R[_size - 1 - _insertion_index++] = i;
            _visited[i] = true;
            _node_index++;
        }
    }

    return degrees;
}

vector<size_t> get_permutation_array(const adj_list &_array, const size_t &_size) {
    adj_list array_sorted_first = _array;
    adj_list array_sorted_second = _array;
    queue<size_t> Q;
    size_t node_index = 0;
    size_t insertion_index = 0;
    vector<bool> visited_nodes(_size, false);
    vector<size_t> R(_size);
    vector<size_t> degrees = get_degrees(_array, _size, visited_nodes, R, node_index, insertion_index);
    bool node_found;

    for (auto &i: array_sorted_second) {
        sort(i.second.begin(), i.second.end(),
             [&degrees](const size_t &left, const size_t &right) {
                 return degrees[left] < degrees[right];
             });
    }

    sort(array_sorted_first.begin(), array_sorted_first.end(),
         [&degrees](const pair<size_t, vector<size_t>> &left, const pair<size_t, vector<size_t>> &right) {
             return (degrees[left.first] == degrees[right.first] ?
                     left.first < right.first :
                     degrees[left.first] < degrees[right.first]);
         });

    while (true) {
        node_found = false;
        for (; node_index < _size; node_index++) {
            if (!visited_nodes[array_sorted_first[node_index].first]) {
                node_found = true;
                break;
            }
        }

        if (!node_found) {
            break;
        }

        Q.push(array_sorted_first[node_index].first);
        visited_nodes[array_sorted_first[node_index].first] = true;

        while (!Q.empty()) {
            for (auto &i: array_sorted_second[Q.front()].second) {
                if (!visited_nodes[i]) {
                    Q.push(i);
                    visited_nodes[i] = true;
                }
            }

            R[_size - 1 - insertion_index++] = Q.front();
            Q.pop();
        }

        node_index++;
    }
    return R;
}

void reorder_matrix(adj_list &_array, const vector<size_t> &R) {
    map<size_t, size_t> reordering_map;

    for (size_t i = 0; i < R.size(); i++) {
        reordering_map[R[i]] = i;
    }

    adj_list result_array(_array.size());

    for (size_t i = 0; i < _array.size(); i++) {
        result_array[i] = _array[R[i]];
    }

    _array = result_array;

    for (auto &i: _array) {
        for (auto &j: i.second) {
            j = reordering_map[j];
        }
    }
}

void reverse_cuthill_mckee(const size_t &_size, const string &_file) {
    struct timeval start{}, end{};

    adj_list array = read_adjacency_list(_file);

    cout << "Reverse Cuthill-McKee ordering:" << endl;

// -- UNCOMMENT IF BANDWIDTH OUTPUT IS NEEDED -- //
    get_bandwidth(array, "before");

    gettimeofday(&start, nullptr);
    vector<size_t> R = get_permutation_array(array, _size);
    gettimeofday(&end, nullptr);

// -- UNCOMMENT IF YOU NEED TO CHANGE INDEXES -- //
    reorder_matrix(array, R);

// -- UNCOMMENT IF BANDWIDTH OUTPUT IS NEEDED -- //
    get_bandwidth(array, "after");

    double time =
            (static_cast<double> ((end.tv_sec * 1e6 + end.tv_usec) - (start.tv_sec * 1e6 + start.tv_usec))) * 1e-6;

    cout << " >>> ExecutingTime: " << time << " sec" << "\n\n";
}