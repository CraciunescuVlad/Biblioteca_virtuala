#include "Cos.h"
#include <iostream>
using namespace std;

// Constructor implicit – inițializează un coș gol
Cos::Cos() = default;

// Adaugă o carte în coș pe baza ISBN-ului.
// Dacă ISBN-ul există deja, crește numărul de exemplare.
void Cos::adaugaCarte(const string &isbn, int numar) {
    carti[isbn] += numar;
}

// Modifică numărul de exemplare pentru un ISBN existent.
// Dacă ISBN-ul nu există, se afișează un mesaj de eroare.
void Cos::modificareCarte(const string &isbn, int nouNumar) {
    if (carti.find(isbn) != carti.end()) {
        carti[isbn] = nouNumar;
    } else {
        cerr << "Cartea cu ISBN " << isbn << " nu exista in cos.\n";
    }
}

// Șterge o carte din coș pe baza ISBN-ului.
// Nu afișează eroare dacă ISBN-ul nu există.
void Cos::stergeCarte(const string &isbn) {
    carti.erase(isbn);
}

// Afișează conținutul coșului în terminal.
// Dacă coșul este gol, se afișează un mesaj corespunzător.
void Cos::vizualizeazaCos() const {
    if (carti.empty()) {
        cout << "Cosul este gol.\n";
        return;
    }

    cout << "Carti in cos:\n";
    for (const auto& [isbn, numar] : carti) {
        cout << "ISBN: " << isbn << " | Nr. exemplare: " << numar << "\n";
    }
}

// Returnează conținutul actual al coșului
map<string, int> Cos::getCarti() const {
    return carti;
}

// Suprascrie conținutul coșului cu un nou set de date (util în încărcare din fișier)
void Cos::setCarti(const map<string, int> &cartiNoi) {
    carti = cartiNoi;
}
