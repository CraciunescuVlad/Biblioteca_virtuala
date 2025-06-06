#include "GestionareFisiere.h"
#include "Carte.h"
#include "../utilizator/Imprumut.h"
#include <fstream>
#include <iostream>
using namespace std;

vector<Carte> GestionareFisiere::incarcaCarti(const string &numeFisier) {
    vector<Carte> carti;
    ifstream fin(numeFisier);
    if (!fin.is_open()) {
        cerr<<"Eroare la deschiderea fisierului "<<numeFisier<<endl;
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

void GestionareFisiere::salveazaCarti(const vector<Carte> &carti, const string &numeFisier) {
    ofstream fout(numeFisier);
    if (!fout.is_open()) {
        cerr<<"Eroare la scrierea in fisierul "<< numeFisier<<endl;
        return;
    }

    fout<<carti.size()<<"\n";
    for (const auto& carte : carti) {
        fout<<carte.getISBN()<<"\n";
        fout<<carte.getTitlu()<<"\n";
        fout<<carte.getAutor()<<"\n";
        fout<<carte.getStoc()<<"\n";
    }
}

map<string, int> GestionareFisiere::incarcaCos(const string &numeFisier) {
    map<string, int> cos;
    ifstream fin(numeFisier);
    if (!fin.is_open()) {
        return cos;
    }

    string isbn;
    int numar;
    while (fin>>isbn>>numar) {
        cos[isbn] = numar;
    }
    return cos;
}

void GestionareFisiere::salveazaCos(const map<string, int> &cos, const string &numeFisier) {
    ofstream fout(numeFisier);
    if (!fout.is_open()) {
        cerr<<"Eroare la scrierea cosului in "<<numeFisier<<"\n";
        return;
    }
    for (const auto& [isbn, nr] : cos) {
        fout<<isbn<<" "<<nr<<"\n";
    }
}

void GestionareFisiere::salveazaImprumut(const Imprumut &imprumut, const string &numeFisier) {
    ofstream fout(numeFisier, ios::app);
    if (!fout.is_open()) {
        cerr<<"Eroare la deschiderea fisierului "<<numeFisier<<" pentru scriere.\n";
        return;
    }
    fout<<imprumut.getNumeUtilizator()<<'\n';
    fout<<imprumut.getData().getZi()<<" "<<imprumut.getData().getLuna()<<" "<<imprumut.getData().getAn()<<'\n';
    for (const auto& carte : imprumut.getCarti()) {
        fout<<carte.getISBN()<<" ";
    }
    fout<<'\n';
}
