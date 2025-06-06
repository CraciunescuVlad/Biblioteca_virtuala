#ifndef GESTIONAREFISIERE_H
#define GESTIONAREFISIERE_H

#include <vector>
#include <map>
#include <string>
#include "../administrator/Carte.h"
#include "../utilizator/Data.h"
#include "../utilizator/Imprumut.h"
using namespace std;

/*
 * Clasa GestionareFisiere oferă metode statice pentru manipularea fișierelor
 * necesare aplicației: carti.txt, cos_utilizator.txt și imprumuturi.txt.
 * Funcțiile includ operații de încărcare și salvare pentru fiecare dintre aceste entități.
 */
class GestionareFisiere {
public:
    // === Gestiunea cărților ===

    // Încarcă vectorul de cărți din fișierul specificat (implicit "carti.txt")
    static vector<Carte> incarcaCarti(const string& numeFisier = "carti.txt");

    // Salvează vectorul de cărți în fișierul specificat (implicit "carti.txt")
    static void salveazaCarti(const vector<Carte>& carti, const string& numeFisier = "carti.txt");

    // === Gestiunea coșului utilizatorului ===

    // Încarcă coșul utilizatorului dintr-un fișier mapând ISBN-ul la numărul de exemplare
    static map<string, int> incarcaCos(const string& numeFisier = "cos_utilizator.txt");

    // Salvează conținutul coșului în fișierul specificat
    static void salveazaCos(const map<string, int>& cos, const string& numeFisier = "cos_utilizator.txt");

    // === Gestiunea fișelor de împrumut ===

    // Salvează o fișă de împrumut într-un fișier text, în mod implicit "imprumuturi.txt"
    static void salveazaImprumut(const Imprumut& imprumut, const string& numeFisier = "imprumuturi.txt");
};

#endif //GESTIONAREFISIERE_H
