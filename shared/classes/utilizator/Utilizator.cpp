#include "Utilizator.h"
#include "../utilizator/Data.h"
#include "../utilizator/Imprumut.h"
#include "../gestionareFisiere/GestionareFisiere.h"
#include "../administrator/Carte.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;


Utilizator::Utilizator() {
    //incarca cosul din fisier
    cos.setCarti(GestionareFisiere::incarcaCos());
}

void Utilizator::vizualizareCos() const {
    cos.vizualizeazaCos();
}

void Utilizator::adaugaCarte(const string &isbn, int nr, bool afiseazaMesaj) {
    if (nr <= 0) {
        if (afiseazaMesaj) cerr << "Numarul de exemplare trebuie sa fie pozitiv.\n";
        return;
    }
    auto carti = GestionareFisiere::incarcaCarti();
    auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c) { return c.getISBN() == isbn; });

    if (it == carti.end()) {
        if (afiseazaMesaj) cerr << "Cartea nu exista in biblioteca.\n";
        return;
    }
    int dejaInCos = cos.getCarti()[isbn];
    if (dejaInCos + nr > it->getStoc()) {
        if (afiseazaMesaj) cerr << "Nu sunt suficiente exemplare in stoc.\n";
        return;
    }
    cos.adaugaCarte(isbn, nr);
    GestionareFisiere::salveazaCos(cos.getCarti());
    if (afiseazaMesaj) cout << "Carte adaugata in cos.\n";
}

void Utilizator::modificaCarte(const string &isbn, int nouNr, bool afiseazaMesaj) {
    if (nouNr < 0) {
        if (afiseazaMesaj) cerr << "Numarul de exemplare nu poate fi negativ.\n";
        return;
    }

    auto cosCarti = cos.getCarti();
    if (cosCarti.find(isbn) == cosCarti.end()) {
        if (afiseazaMesaj) cerr << "Cartea nu exista in cos.\n";
        return;
    }
    auto carti = GestionareFisiere::incarcaCarti();
    auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c) { return c.getISBN() == isbn; });
    if (it == carti.end()) {
        if (afiseazaMesaj) cerr << "Cartea nu mai exista in biblioteca.\n";
        return;
    }

    if (nouNr > it->getStoc()) {
        if (afiseazaMesaj) cerr << "Stoc insuficient pentru a modifica la " << nouNr << " exemplare.\n";
        return;
    }
    cos.modificareCarte(isbn, nouNr);
    GestionareFisiere::salveazaCos(cos.getCarti());
    if (afiseazaMesaj) cout << "Carte modificata in cos.\n";
}


void Utilizator::stergeCarte(const string &isbn, bool afiseazaMesaj) {
    auto cartiCos = cos.getCarti();
    if (cartiCos.find(isbn) == cartiCos.end()) {
        if (afiseazaMesaj) cout << "Eroare: Cartea nu se afla in cos.\n";
        return;
    }
    cos.stergeCarte(isbn);
    GestionareFisiere::salveazaCos(cos.getCarti());
    if (afiseazaMesaj) cout << "Carte stearsa din cos.\n";
}

void Utilizator::imprumuta(const string &numeUtilizator, bool afiseazaMesaj) {
    auto cosCurent = cos.getCarti();

    // NU permite împrumutul dacă coșul e gol
    if (cosCurent.empty()) {
        if (afiseazaMesaj) {
            cerr << "Nu poti realiza un imprumut cu un cos gol.\n";
        }
        return;
    }

    auto toateCartile = GestionareFisiere::incarcaCarti();
    vector<Carte> cartiImprumutate;

    for (const auto& [isbn, nr] : cosCurent) {
        auto it = find_if(toateCartile.begin(), toateCartile.end(), [&](const Carte& c) {return c.getISBN() == isbn;});

        if (it != toateCartile.end() && it->getStoc() >= nr) {
            it->setStoc(it->getStoc() - nr);
            for (int i=0; i<nr; i++) {
                cartiImprumutate.push_back(*it);
            }
        }
        else {
            if (afiseazaMesaj) cerr<<"Eroare: stoc insuficient sau carte inexistenta pentru ISBN: "<<isbn<<'\n';
        }
    }

    // Nu salva nimic dacă nu s-au împrumutat cărți valide
    if (cartiImprumutate.empty()) {
        if (afiseazaMesaj) cerr << "Nicio carte validă pentru împrumut.\n";
        return;
    }

    //Cream data curenta
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    Data dataCurenta(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

    Imprumut imprumut(numeUtilizator, dataCurenta, cartiImprumutate);

    // Salvează fisa de imprumut si actualizează fișierele
    GestionareFisiere::salveazaImprumut(imprumut);
    GestionareFisiere::salveazaCarti(toateCartile);
    GestionareFisiere::salveazaCos({}); // golește coșul

    if (afiseazaMesaj) cout << "Imprumut realizat cu succes!\n";
}


vector<string> Utilizator::getCos() const {
    map<string, int> cos_map = GestionareFisiere::incarcaCos();
    vector<string> rezultat;
    for (const auto& [isbn, nr] : cos_map) {
        rezultat.push_back(isbn + " x" + to_string(nr));
    }
    return rezultat;
}