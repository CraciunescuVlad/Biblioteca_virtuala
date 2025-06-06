#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <vector>
#include "Carte.h"
using namespace std;

class Administrator {
public:
    Administrator() = default;
    void vizualizareCarti() const;
    void adaugaCarte(const Carte &carte, bool afiseazaMesaj = true);
    void stergeCarte(const string &isbn, bool afiseazaMesaj = true);
    void modificaStoc(const string &isbn, int nouStoc, bool afiseazaMesaj = true);
    void vizualizeazaImprumuturi() const;
    vector<Carte> getCarti() const;
    vector<string> getImprumuturi() const;
private:
    vector<Carte> incarcaCarti() const;
    void salveazaCarti(const vector<Carte>& carti) const;
};



#endif //ADMINISTRATOR_H
