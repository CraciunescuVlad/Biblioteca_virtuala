#include <iostream>
#include <string>
#include "shared/classes/utilizator/Utilizator.h"
using namespace std;

int main(int argc, char* argv[]) {
    Utilizator utilizator; // Creează un obiect utilizator care gestionează coșul și împrumuturile

    // Dacă nu s-a dat nicio comandă, afișăm lista completă de comenzi disponibile
    if (argc < 2) {
        cout << "Comenzi disponibile:\n";
        cout << " vizualizare cos\n";
        cout << " adaugare carte <ISBN> <nr_exemplare>\n";
        cout << " modifica carte <ISBN> <nou_nr_exemplare>\n";
        cout << " sterge carte <ISBN>\n";
        cout << " imprumuta <nume_utilizator>\n";
        return 1; // Termină execuția
    }

    string comanda = argv[1]; // Extrage comanda principală

    // === Comanda: vizualizare cos ===
    if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "cos") {
        utilizator.vizualizareCos();
    }

    // === Comanda: adaugare carte <ISBN> <nr_exemplare> ===
    else if (comanda == "adauga" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nr = stoi(argv[4]); // conversie din string în int
        utilizator.adaugaCarte(isbn, nr); // adaugă în coș
    }

    // === Comanda: modifica carte <ISBN> <nou_nr_exemplare> ===
    else if (comanda == "modifica" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nouNr = stoi(argv[4]);
        utilizator.modificaCarte(isbn, nouNr); // modifică nr de exemplare în coș
    }

    // === Comanda: sterge carte <ISBN> ===
    else if (comanda == "sterge" && argc >= 4 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        utilizator.stergeCarte(isbn); // șterge cartea din coș
    }

    // === Comanda: imprumuta <nume_utilizator> ===
    else if (comanda == "imprumuta" && argc >= 3) {
        // Concatenează numele utilizatorului din argumentele rămase
        string nume;
        for (int i = 2; i < argc; ++i) {
            if (i > 2) nume += " ";
            nume += argv[i];
        }
        utilizator.imprumuta(nume); // lansează împrumutul
    }

    // === Comandă necunoscută sau argumente insuficiente ===
    else {
        cerr << "Comanda necunoscuta sau argumente insuficiente.\n";
    }

    return 0; // Program încheiat cu succes
}
