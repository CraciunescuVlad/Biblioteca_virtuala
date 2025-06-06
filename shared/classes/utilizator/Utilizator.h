#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>
#include <vector>
#include <map>
#include "Cos.h"
using namespace std;

/**
 * Clasa Utilizator reprezintă un utilizator al bibliotecii virtuale
 * care poate adăuga, modifica, vizualiza și împrumuta cărți dintr-un coș propriu.
 */
class Utilizator {
private:
    Cos cos;  // Coșul de cărți asociat utilizatorului

public:
    // Constructor – încarcă datele coșului din fișier
    Utilizator();

    // Afișează conținutul coșului în consolă
    void vizualizareCos() const;

    /**
     * Adaugă o carte în coș
     * @param isbn - codul ISBN al cărții
     * @param nr - numărul de exemplare
     * @param afiseazaMesaj - specifică dacă se afișează mesaje în consolă
     */
    void adaugaCarte(const string& isbn, int nr, bool afiseazaMesaj = true);

    /**
     * Modifică numărul de exemplare pentru o carte deja existentă în coș
     * @param isbn - codul ISBN al cărții
     * @param nouNr - noul număr de exemplare
     * @param afiseazaMesaj - specifică dacă se afișează mesaje în consolă
     */
    void modificaCarte(const string& isbn, int nouNr, bool afiseazaMesaj = true);

    /**
     * Șterge o carte din coș, dacă există
     * @param isbn - codul ISBN al cărții
     * @param afiseazaMesaj - specifică dacă se afișează mesaje în consolă
     */
    void stergeCarte(const string& isbn, bool afiseazaMesaj = true);

    /**
     * Realizează un împrumut din cărțile aflate în coș
     * @param numeUtilizator - numele persoanei care împrumută
     * @param afiseazaMesaj - specifică dacă se afișează mesaje în consolă
     */
    void imprumuta(const string& numeUtilizator, bool afiseazaMesaj = true);

    /**
     * Returnează conținutul coșului sub formă de vector de stringuri (pentru afișare)
     */
    vector<string> getCos() const;

    /**
     * Returnează coșul ca map (isbn -> număr exemplare)
     * Folosit pentru validări sau procesări ulterioare.
     */
    map<string, int> getCosMap() const { return cos.getCarti(); }
};

#endif //UTILIZATOR_H
