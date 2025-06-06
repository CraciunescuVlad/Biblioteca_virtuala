#include "Imprumut.h"
#include "Data.h"
#include "../administrator/Carte.h"
#include <iostream>
using namespace std;

Imprumut::Imprumut() : data(), numeUtilizator("Necunoscut") {}

Imprumut::Imprumut(const string &numeUtilizator, const Data &data, const vector<Carte> &carti) : carti(carti), data(data), numeUtilizator(numeUtilizator) {}

string Imprumut::getNumeUtilizator() const {
    return numeUtilizator;
}

Data Imprumut::getData() const {
    return data;
}

vector<Carte> Imprumut::getCarti() const {
    return carti;
}

void Imprumut::setNumeUtilizator(const string &nume) {
    numeUtilizator = nume;
}

void Imprumut::setData(const Data &dataNoua) {
    data = dataNoua;
}

void Imprumut::setCarti(const vector<Carte> &cartiNoi) {
    carti = cartiNoi;
}

void Imprumut::afisare() const {
    cout<<"Utilizator: "<<numeUtilizator<<"\n";
    cout<<"Data: "<<data.getZi()<<"/"<<data.getLuna()<<"/"<<data.getAn()<<"\n";
    cout<<"Carti imprumutate:\n";
    for (const auto& carte : carti) {
        carte.afiseaze();
    }
}
