#include <iostream>
#include <string>
#include "shared/classes/utilizator/Utilizator.h"
using namespace std;

int main(int argc, char* argv[]) {
    Utilizator utilizator;
    if (argc<2) {
        cout<<"Comenzi disponibile:\n";
        cout<<" vizualizare cos\n";
        cout<<" adaugare carte <ISBN> <nr_exemplare>\n";
        cout<<" modifica carte <ISBN> <nou_nr_exemplare>\n";
        cout<<" sterge carte <ISBN>\n";
        cout<<" imprumuta <nume_utilizator>\n";
        return 1;
    }

    string comanda = argv[1];

    if (comanda == "vizualizare" && argc >= 3 && string(argv[2]) == "cos") {
        utilizator.vizualizareCos();
    }
    else if (comanda == "adauga" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nr = stoi(argv[4]);
        utilizator.adaugaCarte(isbn, nr);
    }
    else if (comanda == "modifica" && argc >= 5 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        int nouNr = stoi(argv[4]);
        utilizator.modificaCarte(isbn, nouNr);
    }
    else if (comanda == "sterge" && argc >= 4 && string(argv[2]) == "carte") {
        string isbn = argv[3];
        utilizator.stergeCarte(isbn);
    }
    else if (comanda == "imprumuta" && argc >= 3) {
        string nume;
        for (int i=2; i<argc; ++i) {
            if (i>2) nume += " ";
            nume += argv[i];
        }
        utilizator.imprumuta(nume);
    }
    else {
        cerr<<"Comanda necunoscuta sau argumente insuficiente.\n";
    }
    return 0;
}