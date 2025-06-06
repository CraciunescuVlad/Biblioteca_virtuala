#include "Carte.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor implicit – inițializează membrii cu valori default (vide sau 0)
Carte::Carte() : isbn(""), titlu(""), autor(""), stoc(0) {}

// Constructor parametrizat – permite inițializarea completă a unei cărți
Carte::Carte(const string &isbn, const string &titlu, const string &autor, int stoc)
    : isbn(isbn), titlu(titlu), autor(autor), stoc(stoc) {}

// Returnează codul ISBN al cărții
string Carte::getISBN() const {
    return isbn;
}

// Returnează numele autorului
string Carte::getAutor() const {
    return autor;
}

// Returnează titlul cărții
string Carte::getTitlu() const {
    return titlu;
}

// Returnează numărul de exemplare disponibile în stoc
int Carte::getStoc() const {
    return stoc;
}

// Setează un nou număr de exemplare disponibile pentru carte
void Carte::setStoc(int nouStoc) {
    stoc = nouStoc;
}

// Afișează detaliile cărții într-un format clar
void Carte::afiseaze() const {
    cout << "ISBN: " << isbn
         << ", Titlu: " << titlu
         << ", Autor: " << autor
         << ", Stoc: " << stoc << '\n';
}

// Supraincarcă operatorul de inserare << pentru afișarea unei cărți
ostream& operator<<(ostream& out, const Carte& carte) {
    out << "ISBN: " << carte.getISBN()
        << ", Titlu: " << carte.getTitlu()
        << ", Autor: " << carte.getAutor()
        << ", Stoc: " << carte.getStoc();
    return out;
}
