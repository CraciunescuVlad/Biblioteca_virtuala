#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>
#include <vector>
#include "Cos.h"
using namespace std;

class Utilizator {
private:
    Cos cos;
public:
    Utilizator();

    void vizualizareCos() const;
    void adaugaCarte(const string& isbn, int nr, bool afiseazaMesaj = true);
    void modificaCarte(const string& isbn, int nouNr, bool afiseazaMesaj = true);
    void stergeCarte(const string& isbn, bool afiseazaMesaj = true);
    void imprumuta(const string& numeUtilizator, bool afiseazaMesaj = true);
    vector<string> getCos() const;
    map<string, int> getCosMap() const { return cos.getCarti(); }
};



#endif //UTILIZATOR_H
