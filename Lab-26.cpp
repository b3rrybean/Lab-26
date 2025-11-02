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
using namespace std::chrono;

// Helper function to time operations
template <typename Func>
long long timeOperation(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    const int NUM_RUNS = 15;
    const int NUM_OPERATIONS = 4;
    const int NUM_CONTAINERS = 3;

    long long results[NUM_RUNS][NUM_OPERATIONS][NUM_CONTAINERS] = {0};

    // Read codes from file into a vector
    vector<string> allCodes;
    ifstream file("codes.txt");
    string code;

    while (file >> code) {
    allCodes.push_back(code);
    }
    file.close();

    // Operations names for output
    string operations[] = {"Read", "Sort", "Insert", "Delete"};

    // Loop through all simulation runs
    for (int run = 0; run < NUM_RUNS; run++) {
        cout << "Run #" << run + 1 << endl;

    // Containers for each race
    vector<string> v;
    list<string> l;
    set<string> s;

    // Race 1: Reading
    long long timeVectorRead = timeOperation([&]() {
        for (auto &str : allCodes) v.push_back(str);
    });

    long long timeListRead = timeOperation([&]() {
        for (auto &str : allCodes) l.push_back(str);
    });

    long long timeSetRead = timeOperation([&]() {
        for (auto &str : allCodes) s.insert(str);
    });

    // Race 2: Sorting
    long long timeVectorSort = timeOperation([&]() {
        sort(v.begin(), v.end());
    });

    long long timeListSort = timeOperation([&]() {
        l.sort();
    });

    long long timeSetSort = -1; // set is always sorted

    // Race 3: Inserting
    long long timeVectorInsert = timeOperation([&]() {
        v.insert(v.begin() + v.size() / 2, "TESTCODE");
    });

    long long timeListInsert = timeOperation([&]() {
        auto listMid = l.begin();
        advance(listMid, l.size() / 2);
        l.insert(listMid, "TESTCODE");
    });

    long long timeSetInsert = timeOperation([&]() {
        s.insert("TESTCODE");
    });

    // Race 4: Deleting
    long long timeVectorDelete = timeOperation([&]() {
        v.erase(v.begin() + v.size() / 2);
}   );

    long long timeListDelete = timeOperation([&]() {
        auto listDel = l.begin();
        advance(listDel, l.size() / 2);
        l.erase(listDel);
    });

    long long timeSetDelete = timeOperation([&]() {
        auto it = s.begin();
        advance(it, s.size() / 2);
        s.erase(it);
    });

    // Comput averages (reused and modified dummy sample from milestone 2)
    long long totals[NUM_OPERATIONS][NUM_CONTAINERS] = {0};

    for (int op = 0; op < NUM_OPERATIONS; op++) {
        for (int cont = 0; cont < NUM_CONTAINERS; cont++) {
            long long sum = 0;
            for (int run = 0; run < NUM_RUNS; run++) sum += results[run][op][cont];
            totals[op][cont] = sum / NUM_RUNS;
        }
        cout << endl;
    }

    // Output averages
    cout << "\nNumber of simulations: " << NUM_RUNS << endl;
    cout << setw(12) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << endl;

    for (int op = 0; op < NUM_OPERATIONS; op++) {
        cout << setw(12) << operations[op];
        for (int cont = 0; cont < NUM_CONTAINERS; cont++)
            cout << setw(10) << totals[op][cont];
        cout << endl;
    }

    return 0;

}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/