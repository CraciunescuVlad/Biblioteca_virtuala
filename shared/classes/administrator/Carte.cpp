#include "Carte.h"
#include <iostream>
#include <string>
using namespace std;

Carte::Carte() : isbn(""), titlu(""), autor(""), stoc(0) {}

Carte::Carte(const string &isbn, const string &titlu, const string &autor, int stoc)
    : isbn(isbn), titlu(titlu), autor(autor), stoc(stoc) {}

string Carte::getISBN() const {
    return isbn;
}

string Carte::getAutor() const {
    return autor;
}

string Carte::getTitlu() const {
    return titlu;
}

int Carte::getStoc() const {
    return stoc;
}

void Carte::setStoc(int nouStoc) {
    stoc = nouStoc;
}

void Carte::afiseaze() const {
    cout<<"ISBN: "<<isbn<<", Titlu: "<<titlu<<", Autor: "<<autor<<", Stoc: "<<stoc<<'\n';
}

ostream& operator<<(ostream& out, const Carte& carte) {
    out << "ISBN: " << carte.getISBN()
        << ", Titlu: " << carte.getTitlu()
        << ", Autor: " << carte.getAutor()
        << ", Stoc: " << carte.getStoc();
    return out;
}