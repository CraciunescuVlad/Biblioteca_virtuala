#ifndef COS_H
#define COS_H

#include <map>
#include <string>
using namespace std;

// Clasa Cos reprezintă coșul de cărți al unui utilizator, utilizând un map
// unde cheia este ISBN-ul cărții și valoarea este numărul de exemplare
class Cos {
private:
    // Structură de date care reține ISBN-ul cărții și numărul de exemplare
    map<string, int> carti;

public:
    // Constructor implicit
    Cos();

    // Adaugă o carte în coș. Dacă cartea există deja, se adaugă la numărul curent
    void adaugaCarte(const string& isbn, int numar);

    // Modifică numărul de exemplare pentru o carte deja existentă în coș
    void modificareCarte(const string& isbn, int nouNumar);

    // Șterge complet o carte din coș după ISBN
    void stergeCarte(const string& isbn);

    // Afișează conținutul coșului în terminal (folosit în modul CLI)
    void vizualizeazaCos() const;

    // Returnează conținutul coșului
    map<string, int> getCarti() const;

    // Setează noul conținut al coșului (util în cazul încărcării din fișier)
    void setCarti(const map<string, int>& cartiNoi);
};

#endif //COS_H
