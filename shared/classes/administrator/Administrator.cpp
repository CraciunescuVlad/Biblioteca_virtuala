#include "Administrator.h"
#include "Utilitare.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <bits/ranges_algo.h>  // Pentru funcții din C++20 (ex: ranges::sort)

using namespace std;

// Fișiere utilizate pentru persistență
const string FISIER_CARTI = "carti.txt";
const string FISIER_IMPRUMUTURI = "imprumuturi.txt";

/**
 * Încarcă toate cărțile din fișierul carti.txt într-un vector de obiecte Carte.
 * Returnează vectorul rezultat, indiferent dacă fișierul este gol sau nu.
 */
vector<Carte> Administrator::incarcaCarti() const {
    ifstream fin("carti.txt");
    vector<Carte> carti;

    if (!fin.is_open()) {
        cerr << "Eroare la deschiderea fisierului carti.txt\n";
        return carti;
    }

    int n;
    fin >> n;
    fin.ignore();
    for (int i = 0; i < n; i++) {
        string isbn, titlu, autor;
        int stoc;
        getline(fin, isbn);
        getline(fin, titlu);
        getline(fin, autor);
        fin >> stoc;
        fin.ignore();
        carti.emplace_back(isbn, titlu, autor, stoc);
    }
    return carti;
}

/**
 * Salvează toate cărțile din vectorul primit în fișierul carti.txt.
 * Suprascrie complet fișierul.
 */
void Administrator::salveazaCarti(const vector<Carte> &carti) const {
    ofstream fout(FISIER_CARTI);
    fout << carti.size() << '\n';
    for (const auto& carte : carti) {
        fout << carte.getISBN() << '\n'
             << carte.getTitlu() << '\n'
             << carte.getAutor() << '\n'
             << carte.getStoc() << '\n';
    }
}

/**
 * Afișează toate cărțile disponibile, utilizând funcția template afiseazaElemente.
 */
void Administrator::vizualizareCarti() const {
    auto carti = incarcaCarti();
    afiseazaElemente(carti);  // funcție template din Utilitare.h
}

/**
 * Adaugă o carte nouă în bibliotecă, validând mai întâi ca stocul să fie pozitiv.
 * @param carte - obiectul Carte de adăugat
 * @param afiseazaMesaj - dacă este true, se afișează mesaje în terminal
 */
void Administrator::adaugaCarte(const Carte &carte, bool afiseazaMesaj) {
    if (carte.getStoc() < 0) {
        if (afiseazaMesaj) cerr << "Eroare: Stocul nu poate fi negativ.\n";
        return;
    }
    auto carti = incarcaCarti();
    carti.push_back(carte);
    salveazaCarti(carti);
    if (afiseazaMesaj) cout << "Carte adaugata cu succes.\n";
}

/**
 * Șterge cartea cu ISBN-ul specificat.
 * @param isbn - codul identificator al cărții
 * @param afiseazaMesaj - dacă true, afișează mesaje despre reușita operației
 */
void Administrator::stergeCarte(const string &isbn, bool afiseazaMesaj) {
    auto carti = incarcaCarti();
    bool gasit = false;
    for (auto it = carti.begin(); it != carti.end(); ) {
        if (it->getISBN() == isbn) {
            it = carti.erase(it);
            gasit = true;
        } else ++it;
    }
    salveazaCarti(carti);
    if (afiseazaMesaj) {
        if (gasit) cout << "Carte stearsa cu succes.\n";
        else cerr << "Carte cu ISBN " << isbn << " nu a fost gasita.\n";
    }
}

/**
 * Modifică stocul unei cărți existente.
 * Verifică validitatea stocului și existența cărții.
 */
void Administrator::modificaStoc(const string &isbn, int nouStoc, bool afiseazaMesaj) {
    if (nouStoc < 0) {
        if (afiseazaMesaj) cerr << "Eroare: Stocul nu poate fi negativ.\n";
        return;
    }

    auto carti = incarcaCarti();
    bool gasit = false;
    for (auto& c : carti) {
        if (c.getISBN() == isbn) {
            c.setStoc(nouStoc);
            gasit = true;
            break;
        }
    }
    salveazaCarti(carti);
    if (afiseazaMesaj) {
        if (gasit) cout << "Stoc modificat cu succes.\n";
        else cerr << "Carte cu ISBN " << isbn << " nu a fost gasita.\n";
    }
}

/**
 * Afișează în terminal fișele de împrumut din imprumuturi.txt.
 */
void Administrator::vizualizeazaImprumuturi() const {
    ifstream fin(FISIER_IMPRUMUTURI);
    if (!fin.is_open()) {
        cerr << "Eroare la deschiderea fisierului imprumuturi.txt";
        return;
    }
    string linie;
    while (getline(fin, linie)) {
        cout << linie << "\n";
    }
}

/**
 * Returnează vectorul cu toate cărțile din bibliotecă (din fișier).
 */
vector<Carte> Administrator::getCarti() const {
    return incarcaCarti();
}

/**
 * Returnează conținutul fișierului imprumuturi.txt ca vector de linii.
 * Fiecare element este o linie din fișier.
 */
vector<string> Administrator::getImprumuturi() const {
    vector<string> imprumuturi;
    ifstream fin(FISIER_IMPRUMUTURI);
    if (!fin.is_open()) {
        imprumuturi.push_back("Eroare la deschiderea fisierului imprumuturi.txt");
        return imprumuturi;
    }

    string linie;
    while (getline(fin, linie)) {
        imprumuturi.push_back(linie);
    }
    return imprumuturi;
}
