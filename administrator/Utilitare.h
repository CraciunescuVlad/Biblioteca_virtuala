#ifndef UTILITARE_H
#define UTILITARE_H

#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void afiseazaElemente(const vector<T>& v) {
    for (const auto& el : v) {
        cout << el << endl;
    }
}

#endif // UTILITARE_H
