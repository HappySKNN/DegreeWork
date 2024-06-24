#include "../headers/routines.h"
#include <random>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

adj_list generate_adjacency_list(const size_t &_size, const double &_sparse) {
    random_device rd;
    mt19937_64 engine(rd());
    uniform_int_distribution<size_t> rnd(0, _size - 1);

    adj_list adjacency_list(_size);
    auto nodes_count = static_cast<size_t>((static_cast<long double>(_size * _size) * (1 - _sparse)));
    map<size_t, vector<size_t>> nodes_map;
    vector<size_t> left_nodes;
    vector<size_t> right_nodes;

    while (left_nodes.size() < nodes_count) {
        left_nodes.push_back(rnd(engine));
        right_nodes.push_back(rnd(engine));
    }

    for (size_t i = 0; i < nodes_count; i++) {
        nodes_map[left_nodes[i]].push_back(right_nodes[i]);
        nodes_map[right_nodes[i]].push_back(left_nodes[i]);
    }

    for (size_t i = 0; i < adjacency_list.size(); i++) {
        adjacency_list[i].first = i;
    }

    for (auto &it: nodes_map) {
        sort(it.second.begin(), it.second.end());
        auto right_bound = unique(it.second.begin(), it.second.end());
        it.second.erase(right_bound, it.second.end());
        adjacency_list[it.first].second = it.second;
    }

    return adjacency_list;
}

void write_adjacency_list(const adj_list &_array, const string &_file) {
    ofstream output(_file, ios::out);
    for (auto &i: _array) {
        for (auto &j: i.second) {
            output << to_string(j) << " ";
        }
        output << endl;
    }
    output.close();
}

adj_list read_adjacency_list(const string &_file) {
    ifstream input(_file, ios::in);
    adj_list array;
    string line;
    string digit;
    size_t i = 0;
    while (getline(input, line)) {
        vector<size_t> temp_vec;
        if (line.length()) {
            istringstream ss(line);
            while (ss >> digit) {
                temp_vec.push_back(stoull(digit));
            }
        }
        array.emplace_back(i, temp_vec);
        i++;
    }

    return array;
}

void write_matrix(const adj_list &_array, const string &_file, const size_t &_size) {
    ofstream output(_file, ios::out);
    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            if (find(_array[i].second.begin(), _array[i].second.end(), j) != _array[i].second.end()) {
                output << "1 ";
            } else {
                output << "0 ";
            }
        }
        output << endl;
    }
    output.close();
}

void get_bandwidth(const adj_list &_array, const string &_prefix_text) {
    size_t max_band = 0;
    for (long long i = 1; i < _array.size(); i++) {
        if (_array[i].second.empty())
            continue;
        size_t min_node = _array.size();
        for (auto &j: _array[i].second) {
            if (j < min_node && j < i) {
                min_node = j;
            }
        }
        if (min_node != _array.size()) {
            max_band = max(i - min_node, max_band);
        }
    }
    cout << " >>> Bandwidth " << _prefix_text << ": " << max_band << endl;
}

void convert_to_triplets(const string &_file_in, const string &_file_out) {
    ifstream in(_file_in, ios::in);
    string line;
    string digit;
    size_t n = 0, count = 0;
    while (getline(in, line)) {
        if (line.length()) {
            istringstream ss(line);
            while (ss >> digit) {
                count++;
            }
        }
        n++;
    }
    in.close();

    ifstream input(_file_in, ios::in);
    ofstream output(_file_out, ios::out);
    size_t i = 0;
    output << n << " " << n << " " << count << endl;
    while (getline(input, line)) {
        if (line.length()) {
            istringstream ss(line);
            while (ss >> digit) {
                output << i + 1 << " " << (stoull(digit) + 1) << " " << "1" << endl;
            }
        }
        i++;
    }
    output.close();
    input.close();
}