#include "../headers/approximate_minimum_degree_test.h"
#include "../headers/routines.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

void approximate_minimum_degree(const char *_file, int _size) {
    struct timeval start{}, end{};

    int P[_size], Pinv[_size], i, j, k, result;

    double Control[AMD_CONTROL], Info[AMD_INFO];

    int **array;
    array = (int **) malloc(2 * sizeof(int *));

    int cnt_j = 0;
    adj_list _arr = read_adjacency_list("adj_input.txt");
    for (i = 0; i < _arr.size(); i++) {
        for (j = 0; j < _arr[i].second.size(); j++) {
            cnt_j++;
        }
    }

    array[0] = (int *) malloc(cnt_j * sizeof(int));
    array[1] = (int *) malloc((_size + 1) * sizeof(int));

    cnt_j = 0;
    for (i = 0; i < _arr.size(); i++) {
        array[1][i] = cnt_j;
        for (j = 0; j < _arr[i].second.size(); j++) {
            array[0][cnt_j] = _arr[i].second[j];
            cnt_j++;
        }
    }
    array[1][i] = cnt_j;

    int *Ap = array[1], *Ai = array[0];

    amd_defaults(Control);

    cout << "Approximate minimum degree ordering:" << endl;

    gettimeofday(&start, nullptr);
    result = amd_order(_size, Ap, Ai, P, Control, Info);
    gettimeofday(&end, nullptr);

    if (result != AMD_OK) {
        printf("AMD failed\n");
        exit(1);
    }

// -- UNCOMMENT IF YOU NEED TO CHANGE INDEXES -- //
//    for (k = 0; k < _size; k++) {
//        j = P[k];
//        Pinv[j] = k;
//    }

    double time =
            (static_cast<double> ((end.tv_sec * 1e6 + end.tv_usec) - (start.tv_sec * 1e6 + start.tv_usec))) * 1e-6;

    cout << " >>> ExecutingTime: " << time << " sec" << endl;

}
