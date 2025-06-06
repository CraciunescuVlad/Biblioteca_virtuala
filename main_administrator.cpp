#include <iostream>
#include <string>
#include "shared/classes/administrator/Administrator.h"
#include "shared/classes/administrator/Carte.h"
using namespace std;
int main(int argc, char* argv[]) {
    Administrator admin;
    if (argc < 2) {
        cout<<"Comenzi disponibile:\n"
            <<"  vizualizare carti\n"
            <<"  adauga carte <ISBN> <TITLU> <AUTOR> <STOC>\n"
            <<"  sterge carte <ISBN>"
            <<"  modifica carte <ISBN> <nou_stoc>\n"
            <<"  vizualizare imprumuturi\n";
        return 1;
    }
    string comanda = argv[1];
    if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "carti") {
        admin.vizualizareCarti();
    }
    else if (comanda == "adauga" && argc >= 7 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        string titlu = argv[4];
        string autor = argv[5];
        int stoc = stoi(argv[6]);

        Carte carte(isbn, titlu, autor, stoc);
        admin.adaugaCarte(carte);
        cout<<"Carte adaugata cu succes.\n";
    }
    else if (comanda == "sterge" && argc >= 4 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        admin.stergeCarte(isbn);
        cout<<"Carte stearsa cu succes (daca a existat).\n";
    }
    else if (comanda == "modifica" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nouStoc = stoi(argv[4]);
        admin.modificaStoc(isbn, nouStoc);
        cout<<"Stoc modificat (daca ISBN-ul a existat).\n";
    }
    else if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "imprumuturi") {
        admin.vizualizeazaImprumuturi();
    }
    else {
        cerr<<"Comanda necunoscuta sau argumente insuficiente.\n";
    }
    return 0;
}