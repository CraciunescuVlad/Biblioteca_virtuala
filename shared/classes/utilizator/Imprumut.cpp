#include "Imprumut.h"
#include "Data.h"
#include "../administrator/Carte.h"
#include <iostream>
using namespace std;

// Constructor implicit – initializează data cu valorile implicite și numele utilizatorului cu "Necunoscut"
Imprumut::Imprumut() : data(), numeUtilizator("Necunoscut") {}

// Constructor complet – primește un nume de utilizator, o dată și o listă de cărți
Imprumut::Imprumut(const string &numeUtilizator, const Data &data, const vector<Carte> &carti)
    : carti(carti), data(data), numeUtilizator(numeUtilizator) {}

// Returnează numele utilizatorului care a efectuat împrumutul
string Imprumut::getNumeUtilizator() const {
    return numeUtilizator;
}

// Returnează data la care s-a efectuat împrumutul
Data Imprumut::getData() const {
    return data;
}

// Returnează vectorul cu cărțile împrumutate
vector<Carte> Imprumut::getCarti() const {
    return carti;
}

// Setează numele utilizatorului
void Imprumut::setNumeUtilizator(const string &nume) {
    numeUtilizator = nume;
}

// Setează o nouă dată pentru împrumut
void Imprumut::setData(const Data &dataNoua) {
    data = dataNoua;
}

// Setează lista de cărți împrumutate
void Imprumut::setCarti(const vector<Carte> &cartiNoi) {
    carti = cartiNoi;
}

// Afișează toate detaliile împrumutului în consolă (numele utilizatorului, data și lista de cărți)
void Imprumut::afisare() const {
    cout << "Utilizator: " << numeUtilizator << "\n";
    cout << "Data: " << data.getZi() << "/" << data.getLuna() << "/" << data.getAn() << "\n";
    cout << "Carti imprumutate:\n";
    for (const auto& carte : carti) {
        carte.afiseaze(); // Afișează fiecare carte folosind metoda dedicată
    }
}
