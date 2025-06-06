#include <iostream>
#include <string>
#include "shared/classes/administrator/Administrator.h"
#include "shared/classes/administrator/Carte.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Se creează un obiect de tip Administrator pentru a gestiona cărțile și împrumuturile
    Administrator admin;

    // Dacă nu sunt furnizate argumente în linia de comandă, se afișează lista de comenzi disponibile
    if (argc < 2) {
        cout<<"Comenzi disponibile:\n"
            <<"  vizualizare carti\n"
            <<"  adauga carte <ISBN> <TITLU> <AUTOR> <STOC>\n"
            <<"  sterge carte <ISBN>"
            <<"  modifica carte <ISBN> <nou_stoc>\n"
            <<"  vizualizare imprumuturi\n";
        return 1; // Termină programul pentru că nu s-a dat nicio comandă
    }

    // Se extrage comanda principală din argumente (ex: "adauga", "sterge", etc.)
    string comanda = argv[1];

    // === Comanda: vizualizare carti ===
    if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "carti") {
        admin.vizualizareCarti();
    }

    // === Comanda: adauga carte <ISBN> <TITLU> <AUTOR> <STOC> ===
    else if (comanda == "adauga" && argc >= 7 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        string titlu = argv[4];
        string autor = argv[5];
        int stoc = stoi(argv[6]); // conversie din string în int

        Carte carte(isbn, titlu, autor, stoc); // creează obiectul carte
        admin.adaugaCarte(carte);             // adaugă în bibliotecă
        cout << "Carte adaugata cu succes.\n";
    }

    // === Comanda: sterge carte <ISBN> ===
    else if (comanda == "sterge" && argc >= 4 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        admin.stergeCarte(isbn);
        cout << "Carte stearsa cu succes (daca a existat).\n";
    }

    // === Comanda: modifica carte <ISBN> <nou_stoc> ===
    else if (comanda == "modifica" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nouStoc = stoi(argv[4]); // conversie din string în int
        admin.modificaStoc(isbn, nouStoc);
        cout << "Stoc modificat (daca ISBN-ul a existat).\n";
    }

    // === Comanda: vizualizare imprumuturi ===
    else if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "imprumuturi") {
        admin.vizualizeazaImprumuturi();
    }

    // === Comanda necunoscută sau argumente greșite ===
    else {
        cerr << "Comanda necunoscuta sau argumente insuficiente.\n";
    }

    return 0; // Termină programul cu succes
}
