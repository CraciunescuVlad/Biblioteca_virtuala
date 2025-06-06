#ifndef UTILITARE_H
#define UTILITARE_H

#include <vector>
#include <iostream>
using namespace std;

// Șablon de funcție generică pentru afișarea elementelor dintr-un vector.
// Tipul elementelor este dat de parametrul de tip T.
template <typename T>
void afiseazaElemente(const vector<T>& v) {
    // Parcurge fiecare element al vectorului și îl afișează la consolă.
    // Este necesar ca tipul T să suprascrie operatorul << pentru ostream.
    for (const auto& el : v) {
        cout << el << endl;
    }
}

#endif // UTILITARE_H
