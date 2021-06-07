#pragma once
#include "array_custom.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// beauty constant for N/A values
const int N_A = 99999999;

struct bellman {
    array_custom<string> cities; // vertices with the cities' name
    int** cost_matrix;  // adjacency matrix is stored travels' cost
    int cities_count = 0;
}_data;

// allocate cost_matrix
void allocate_matrix() {
    _data.cost_matrix = new int* [_data.cities_count];   // allocate adjacency matrix
    for (int i = 0; i < _data.cities_count; i++) {
        _data.cost_matrix[i] = new int[_data.cities_count];
        for (int j = 0; j < _data.cities_count; j++) {
            _data.cost_matrix[i][j] = N_A;
            if (i == j) _data.cost_matrix[i][j] = 0;
        }
    }
}

void print_matrix() {
    cout << "Matrix cost: " << endl;
    int size = _data.cities_count;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (_data.cost_matrix[i][j] != N_A)
                cout << _data.cost_matrix[i][j] << "\t";
            else
                cout << "N/A" << "\t";
        }
        cout << endl;
    }
}

// explores text for some base values like cities count
void explore_text() {
    ifstream in("input.txt"); // open the file for reading
    if (in.is_open()) {
        string line = "";
        while (getline(in, line)) {
            size_t next_pos = line.find(';', 0);
            string city_a = line.substr(0, next_pos);
            size_t old_pos = next_pos + 1;
            next_pos = line.find(';', old_pos);
            string city_b = line.substr(old_pos, next_pos - old_pos);
            //            old_pos = next_pos + 1;
            //            next_pos = line.find(';', old_pos);
            //            int cost_a = N_A;
            //            if (line[old_pos] != 'N') {
            //                cost_a = stoi(line.substr(old_pos, next_pos - old_pos));
            //            }
            //            old_pos = next_pos + 1;
            //            int cost_b = N_A;
            //            if (line[old_pos] != 'N') {
            //                cost_b = stoi(line.substr(old_pos, line.size() - old_pos));
            //            }
            _data.cities.push_unique(city_a);    /// set analogue
            _data.cities.push_unique(city_b);
        }
    }
    in.close();

    _data.cities_count = _data.cities.get_size();
    if (_data.cities_count == 0) {
        throw invalid_argument("empty input");
    }
}


// reads the text and parse all data
void read_text() {
    string line;

    ifstream in("input.txt"); // окрываем файл для чтения

    if (in.is_open()) {
        string line = "";
        while (getline(in, line)) {
            size_t next_pos = line.find(';', 0);
            string city_a = line.substr(0, next_pos);
            size_t old_pos = next_pos + 1;
            next_pos = line.find(';', old_pos);
            string city_b = line.substr(old_pos, next_pos - old_pos);
            old_pos = next_pos + 1;
            next_pos = line.find(';', old_pos);
            int cost_a = N_A;
            if (line[old_pos] != 'N') {
                cost_a = stoi(line.substr(old_pos, next_pos - old_pos));
            }
            old_pos = next_pos + 1;
            int cost_b = N_A;
            if (line[old_pos] != 'N') {
                cost_b = stoi(line.substr(old_pos, line.size() - old_pos));
            }

            size_t index_city_A = _data.cities.find(city_a); // find index of city A
            size_t index_city_B = _data.cities.find(city_b); // find index of city B

            _data.cost_matrix[index_city_A][index_city_B] = cost_a;  // matrix initialize
            _data.cost_matrix[index_city_B][index_city_A] = cost_b;  // matrix initialize
        }
    }
    in.close();
}


// bellman_ford algorithm
int bellman_path(int start, int end) {
    if (start == end) return 0;    // don't need to travel...

    array_custom<int> distances(_data.cities_count, N_A);
    distances[start] = 0;   // start point is zero by default
    int size = _data.cities_count;
    for (int i = 0; i < size - 1; ++i) {
        // cost_matrix search
        bool any_change = false;
        for (int x = 0; x < size; ++x)      // cost_matrix[x] - start
            for (int y = 0; y < size; ++y) {    // cost_matrix[x][y] - dest
                if (x == y) continue;   // skip nulls
                if (_data.cost_matrix[x][y] == N_A) continue;    // skip N/A
                distances[y] = min(distances[y], distances[x] + _data.cost_matrix[x][y]);
                any_change = true;
            }
        if (!any_change)    // stop iterations without changes
            break;

    }

    for (int i = 0; i < distances.get_size(); ++i) {
        cout << "distances[" << i << "] =" << distances[i] << endl;
    }
    cout << endl;
    distances.clear();
    return distances[end];
}
