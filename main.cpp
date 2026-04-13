// COMSC-210 | Lab 26 | Barsbek
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

const int NUM_RUNS{12}; // repeat tests so time is noticeable
const int NUM_SIM{15}; // number of simulations
const int NUM_OPER{4}; // read, sort, insert, delete
const int NUM_DS{3}; // vector, list, set

long inputVector(const vector<string>& data);
long inputList(const vector<string>& data);
long inputSet(const vector<string>& data);

long sortVector(vector<string> data);
long sortList(list<string> data);
// no need std::sort for set, set alr sorted

long insertVector(vector<string> data);
long insertList(list<string> data);
long insertSet(set<string> data);

long deleteVector(vector<string> data);
long deleteList(list<string> data);
long deleteSet(set<string> data);

int main() {
    ifstream fileInput{"codes.txt"};
    if (!fileInput) { // check if file opens
        cerr << "File not found\n";
        return 1;
    }

    vector<string> data{};
    string line{};
    while (getline(fileInput, line)) {
        data.push_back(line);
    }

    list<string> dataList{data.begin(), data.end()};
    set<string> dataSet{data.begin(), data.end()};

    long results[NUM_SIM][NUM_OPER][NUM_DS]{}; // 3D array to store results

    cout << "Running...\n";
    for (auto& result : results) {
        // read
        result[0][0] = inputVector(data);
        result[0][1] = inputList(data);
        result[0][2] = inputSet(data);

        // sort
        result[1][0] = sortVector(data);
        result[1][1] = sortList(dataList);
        result[1][2] = 0;

        // insert
        result[2][0] = insertVector(data);
        result[2][1] = insertList(dataList);
        result[2][2] = insertSet(dataSet);

        // delete
        result[3][0] = deleteVector(data);
        result[3][1] = deleteList(dataList);
        result[3][2] = deleteSet(dataSet);
    }

    long sum[NUM_OPER][NUM_DS]{};  // total times

    for (int i{0}; i < NUM_SIM; ++i) {
        for (int j{0}; j < NUM_OPER; ++j) {
            for (int k{0}; k < NUM_DS; ++k) {
                sum[j][k] += results[i][j][k];
            }
        }
    }

    long avg[NUM_OPER][NUM_DS]; // average times

    for (int i{0}; i < NUM_OPER; ++i) {
        for (int j{0}; j < NUM_DS; ++j) {
            avg[i][j] = sum[i][j] / NUM_SIM;
        }
    }

    // final output
    cout << "Number of simulations: " << NUM_SIM << "\n";

    cout << right << setw(10) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << "\n";

    cout << right << setw(10) << "Read"
         << setw(10) << avg[0][0]
         << setw(10) << avg[0][1]
         << setw(10) << avg[0][2] << "\n";

    cout << right << setw(10) << "Sort"
         << setw(10) << avg[1][0]
         << setw(10) << avg[1][1]
         << setw(10) << -1 << "\n";

    cout << right << setw(10) << "Insert"
         << setw(10) << avg[2][0]
         << setw(10) << avg[2][1]
         << setw(10) << avg[2][2] << "\n";

    cout << right << setw(10) << "Delete"
         << setw(10) << avg[3][0]
         << setw(10) << avg[3][1]
         << setw(10) << avg[3][2] << "\n";

    return 0;
}

// READ
long inputVector(const vector<string>& data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i)
        vector<string> vec{data.begin(), data.end()};

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

long inputList(const vector<string>& data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i)
        list<string> myList{data.begin(), data.end()};

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

long inputSet(const vector<string>& data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i)
        set<string> st{data.begin(), data.end()};

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// SORT
// sort vec
long sortVector(vector<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        vector<string> temp{data};
        sort(temp.begin(), temp.end());
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// sort list
long sortList(list<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        list<string> temp{data};
        temp.sort();
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// INSERT
// insert vec
long insertVector(vector<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        vector<string> temp{data};
        temp.insert(temp.begin() + temp.size() / 2, "TESTCODE");
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

long insertList(list<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        list<string> temp{data};

        auto it = temp.begin(); // iterator
        int mid = temp.size() / 2;

        for (int j{0}; j < mid; ++j) { // half
            ++it;
        }

        temp.insert(it, "TESTCODE");
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// insert set
long insertSet(set<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        set<string> temp{data};
        temp.insert("TESTCODE");
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// delete
long deleteVector(vector<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        vector<string> temp{data};
        temp.erase(temp.begin() + temp.size()/2);
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

long deleteList(list<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        list<string> temp{data};

        auto it = temp.begin();
        for (int j{0}; j < temp.size()/2; ++j) {
            ++it;
        }

        temp.erase(it);
    }

    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

long deleteSet(set<string> data) {
    auto start{high_resolution_clock::now()};

    for (int i{0}; i < NUM_RUNS; ++i) {
        set<string> temp{data};
        temp.insert("TESTCODE");
        temp.erase("TESTCODE");
    }
    auto end{high_resolution_clock::now()};
    return duration_cast<milliseconds>(end - start).count();
}

// IGNORE:
/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/