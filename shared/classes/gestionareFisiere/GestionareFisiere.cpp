#include "GestionareFisiere.h"
#include "../administrator/Carte.h"
#include "../utilizator/Imprumut.h"
#include <fstream>
#include <iostream>
using namespace std;

// === Încarcă toate cărțile dintr-un fișier specificat ===
vector<Carte> GestionareFisiere::incarcaCarti(const string &numeFisier) {
    vector<Carte> carti;
    ifstream fin(numeFisier);  // Deschide fișierul pentru citire
    if (!fin.is_open()) {
        cerr << "Eroare la deschiderea fisierului " << numeFisier << endl;
        return carti;
    }

    int n;
    fin >> n;           // Numărul total de cărți
    fin.ignore();       // Ignoră caracterul newline rămas

    for (int i = 0; i < n; i++) {
        string isbn, titlu, autor;
        int stoc;
        getline(fin, isbn);
        getline(fin, titlu);
        getline(fin, autor);
        fin >> stoc;
        fin.ignore();
        carti.emplace_back(isbn, titlu, autor, stoc);  // Adaugă cartea în vector
    }

    return carti;
}

// === Salvează toate cărțile într-un fișier specificat ===
void GestionareFisiere::salveazaCarti(const vector<Carte> &carti, const string &numeFisier) {
    ofstream fout(numeFisier);  // Deschide fișierul pentru scriere
    if (!fout.is_open()) {
        cerr << "Eroare la scrierea in fisierul " << numeFisier << endl;
        return;
    }

    fout << carti.size() << "\n";  // Scrie numărul de cărți
    for (const auto& carte : carti) {
        fout << carte.getISBN() << "\n";
        fout << carte.getTitlu() << "\n";
        fout << carte.getAutor() << "\n";
        fout << carte.getStoc() << "\n";
    }
}

// === Încarcă coșul utilizatorului din fișier sub formă de map<ISBN, nr_exemplare> ===
map<string, int> GestionareFisiere::incarcaCos(const string &numeFisier) {
    map<string, int> cos;
    ifstream fin(numeFisier);  // Deschide fișierul pentru citire
    if (!fin.is_open()) {
        return cos;  // Returnează coșul gol dacă fișierul nu există
    }

    string isbn;
    int numar;
    while (fin >> isbn >> numar) {
        cos[isbn] = numar;
    }

    return cos;
}

// === Salvează coșul utilizatorului într-un fișier ===
void GestionareFisiere::salveazaCos(const map<string, int> &cos, const string &numeFisier) {
    ofstream fout(numeFisier);  // Deschide fișierul pentru scriere
    if (!fout.is_open()) {
        cerr << "Eroare la scrierea cosului in " << numeFisier << "\n";
        return;
    }

    for (const auto& [isbn, nr] : cos) {
        fout << isbn << " " << nr << "\n";  // Scrie fiecare pereche ISBN - număr exemplare
    }
}

// === Salvează o fișă de împrumut într-un fișier (se adaugă la final) ===
void GestionareFisiere::salveazaImprumut(const Imprumut &imprumut, const string &numeFisier) {
    ofstream fout(numeFisier, ios::app);  // Deschide fișierul în mod append
    if (!fout.is_open()) {
        cerr << "Eroare la deschiderea fisierului " << numeFisier << " pentru scriere.\n";
        return;
    }

    // Scrie numele utilizatorului
    fout << imprumut.getNumeUtilizator() << '\n';

    // Scrie data împrumutului
    fout << imprumut.getData().getZi() << " "
         << imprumut.getData().getLuna() << " "
         << imprumut.getData().getAn() << '\n';

    // Scrie lista ISBN-urilor împrumutate
    for (const auto& carte : imprumut.getCarti()) {
        fout << carte.getISBN() << " ";
    }

    fout << '\n';
}
