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

// Constructorul clasei Utilizator – încarcă automat coșul utilizatorului din fișier
Utilizator::Utilizator() {
    cos.setCarti(GestionareFisiere::incarcaCos());
}

// Afișează în consolă conținutul coșului
void Utilizator::vizualizareCos() const {
    cos.vizualizeazaCos();
}

// Adaugă o carte în coș, dacă există în bibliotecă și există stoc suficient
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

// Modifică numărul de exemplare pentru o carte deja existentă în coș
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

// Șterge o carte din coș, dacă există
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

// Realizează un împrumut, dacă coșul conține cărți valide și suficiente în stoc
void Utilizator::imprumuta(const string &numeUtilizator, bool afiseazaMesaj) {
    auto cosCurent = cos.getCarti();

    if (cosCurent.empty()) {
        if (afiseazaMesaj) {
            cerr << "Nu poti realiza un imprumut cu un cos gol.\n";
        }
        return;
    }

    auto toateCartile = GestionareFisiere::incarcaCarti();
    vector<Carte> cartiImprumutate;

    // Se verifică fiecare carte din coș pentru validitate și stoc
    for (const auto& [isbn, nr] : cosCurent) {
        auto it = find_if(toateCartile.begin(), toateCartile.end(), [&](const Carte& c) { return c.getISBN() == isbn; });

        if (it != toateCartile.end() && it->getStoc() >= nr) {
            it->setStoc(it->getStoc() - nr);
            for (int i = 0; i < nr; i++) {
                cartiImprumutate.push_back(*it);
            }
        } else {
            if (afiseazaMesaj) cerr << "Eroare: stoc insuficient sau carte inexistenta pentru ISBN: " << isbn << '\n';
        }
    }

    if (cartiImprumutate.empty()) {
        if (afiseazaMesaj) cerr << "Nicio carte validă pentru împrumut.\n";
        return;
    }

    // Se generează data curentă
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    Data dataCurenta(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

    // Se creează obiectul de tip Imprumut
    Imprumut imprumut(numeUtilizator, dataCurenta, cartiImprumutate);

    // Se salvează împrumutul și se actualizează stocul și coșul
    GestionareFisiere::salveazaImprumut(imprumut);
    GestionareFisiere::salveazaCarti(toateCartile);
    GestionareFisiere::salveazaCos({}); // goliți coșul

    if (afiseazaMesaj) cout << "Imprumut realizat cu succes!\n";
}

// Returnează un vector de stringuri cu cărțile din coș (format pentru afișare în interfață)
vector<string> Utilizator::getCos() const {
    map<string, int> cos_map = GestionareFisiere::incarcaCos();
    vector<string> rezultat;
    for (const auto& [isbn, nr] : cos_map) {
        rezultat.push_back(isbn + " x" + to_string(nr));
    }
    return rezultat;
}
