#include "Administrator.h"
#include "Utilitare.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <bits/ranges_algo.h>

using namespace std;

const string FISIER_CARTI = "carti.txt";
const string FISIER_IMPRUMUTURI = "imprumuturi.txt";

//Metoda care incarca toate cartile din fisier
vector<Carte> Administrator::incarcaCarti() const {
    ifstream fin("carti.txt");
    vector<Carte> carti;

    if (!fin.is_open()) {
        cerr<<"Eroare la deschiderea fisierului carti.txt\n";
        return carti;
    }

    int n;
    fin>>n;
    fin.ignore();
    for (int i=0; i<n; i++) {
        string isbn, titlu, autor;
        int stoc;
        getline(fin, isbn);
        getline(fin, titlu);
        getline(fin, autor);
        fin>>stoc;
        fin.ignore();
        carti.emplace_back(isbn, titlu, autor, stoc);
    }
    return carti;
}


//Salveaza toate cartile din fisier
void Administrator::salveazaCarti(const vector<Carte> &carti) const {
    ofstream fout(FISIER_CARTI);
    fout<<carti.size()<<'\n';
    for (const auto& carte:carti) {
        fout<<carte.getISBN()<<'\n'
            <<carte.getTitlu()<<'\n'
            <<carte.getAutor()<<'\n'
            <<carte.getStoc()<<'\n';
    }
}


//Vizualizeaza carti
void Administrator::vizualizareCarti() const {
    auto carti = incarcaCarti();
    afiseazaElemente(carti);  // funcție template
}

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

//Modifica stocul unei carti
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

//Vizualizeaza fisele de imprumut
void Administrator::vizualizeazaImprumuturi() const {
    ifstream fin(FISIER_IMPRUMUTURI);
    if (!fin.is_open()) {
        cerr<<"Eroare la deschiderea fisierului imprumuturi.txt";
        return;
    }
    string linie;
    while (getline(fin, linie)) {
        cout<<linie<<"\n";
    }
}

vector<Carte> Administrator::getCarti() const {
    return incarcaCarti();
}

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
