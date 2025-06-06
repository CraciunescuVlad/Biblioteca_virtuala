#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <vector>
#include "Carte.h"
using namespace std;

/**
 * Clasa Administrator modelează comportamentul unui administrator al bibliotecii,
 * permițând gestionarea colecției de cărți și vizualizarea fișelor de împrumut.
 */
class Administrator {
public:
    /// Constructor implicit
    Administrator() = default;

    /**
     * Afișează toate cărțile existente în bibliotecă.
     * Conținutul este citit din fișierul carti.txt.
     */
    void vizualizareCarti() const;

    /**
     * Adaugă o carte în colecția bibliotecii.
     * @param carte - obiectul Carte care urmează să fie adăugat.
     * @param afiseazaMesaj - dacă este true, se afișează un mesaj de confirmare în terminal.
     */
    void adaugaCarte(const Carte &carte, bool afiseazaMesaj = true);

    /**
     * Șterge o carte din bibliotecă, identificată prin ISBN.
     * @param isbn - identificatorul unic al cărții.
     * @param afiseazaMesaj - dacă este true, se afișează un mesaj de confirmare în terminal.
     */
    void stergeCarte(const string &isbn, bool afiseazaMesaj = true);

    /**
     * Modifică stocul disponibil pentru o carte, identificată prin ISBN.
     * @param isbn - identificatorul unic al cărții.
     * @param nouStoc - noua valoare pentru stocul cărții.
     * @param afiseazaMesaj - dacă este true, se afișează un mesaj de confirmare în terminal.
     */
    void modificaStoc(const string &isbn, int nouStoc, bool afiseazaMesaj = true);

    /**
     * Afișează conținutul fișierului de împrumuturi.
     * Fiecare linie reprezintă o înregistrare.
     */
    void vizualizeazaImprumuturi() const;

    /**
     * Returnează toate cărțile existente în bibliotecă.
     * @return vector de obiecte Carte
     */
    vector<Carte> getCarti() const;

    /**
     * Returnează toate înregistrările de împrumuturi sub formă de vector de stringuri.
     * @return vector de stringuri corespunzătoare fișei de împrumut.
     */
    vector<string> getImprumuturi() const;

private:
    /**
     * Încarcă toate cărțile din fișierul carti.txt.
     * @return vector cu obiectele Carte citite din fișier.
     */
    vector<Carte> incarcaCarti() const;

    /**
     * Salvează în fișier lista actualizată de cărți.
     * @param carti - vectorul de cărți care trebuie salvat.
     */
    void salveazaCarti(const vector<Carte>& carti) const;
};

#endif //ADMINISTRATOR_H
