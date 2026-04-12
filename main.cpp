// COMSC-210 | Lab 25 | Barsbek
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

const int NUM_RUNS{100}; // repeat tests so time is noticeable

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

    long vecRead {inputVector(data)};
    long listRead {inputList(data)};
    long setRead {inputSet(data)};

    long vecSort{sortVector(data)};
    long listSort{sortList(dataList)};

    long vecInsert{insertVector(data)};
    long listInsert{insertList(dataList)};
    long setInsert{insertSet(dataSet)};

    long vecDelete{deleteVector(data)};
    long listDelete{deleteList(dataList)};
    long setDelete{deleteSet(dataSet)};

    cout << right << setw(10) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << "\n";

    cout << right << setw(10) << "Read"
         << setw(10) << vecRead
         << setw(10) << listRead
         << setw(10) << setRead << "\n";

    cout << right << setw(10) << "Sort"
         << setw(10) << vecSort
         << setw(10) << listSort
         << setw(10) << -1 << "\n";

    cout << right << setw(10) << "Insert"
         << setw(10) << vecInsert
         << setw(10) << listInsert
         << setw(10) << setInsert << "\n";

    cout << right << setw(10) << "Delete"
         << setw(10) << vecDelete
         << setw(10) << listDelete
         << setw(10) << setDelete << "\n";

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