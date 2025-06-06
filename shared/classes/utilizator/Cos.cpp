#include "Cos.h"
#include <iostream>
using namespace std;

Cos::Cos() = default;

void Cos::adaugaCarte(const string &isbn, int numar) {
    carti[isbn] +=numar;
}

void Cos::modificareCarte(const string &isbn, int nouNumar) {
    if (carti.find(isbn) != carti.end()) {
        carti[isbn] = nouNumar;
    }
    else {
        cerr<<"Cartea cu ISBN "<<isbn<<" nu exista in cos.\n";
    }
}

void Cos::stergeCarte(const string &isbn) {
    carti.erase(isbn);
}

void Cos::vizualizeazaCos() const {
    if (carti.empty()) {
        cout<<"Cosul este gol.\n";
        return;
    }

    cout<<"Carti in cos:\n";
    for (const auto& [isbn, numar] : carti) {
        cout<<"ISBN: "<<isbn<<" | Nr. exemplare: "<<numar<<"\n";
    }
}

map<string, int> Cos::getCarti() const {
    return carti;
}

void Cos::setCarti(const map<string, int> &cartiNoi) {
    carti = cartiNoi;
}

