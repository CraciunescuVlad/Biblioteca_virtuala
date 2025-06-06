#ifndef IMPRUMUT_H
#define IMPRUMUT_H

#include <vector>
#include <string>
#include "../administrator/Carte.h"
#include "../utilizator/Data.h"
using namespace std;

/**
 * Clasa Imprumut modelează un împrumut de cărți efectuat de un utilizator la o anumită dată.
 * Aceasta conține informații despre utilizatorul care a efectuat împrumutul,
 * data împrumutului și lista de cărți împrumutate.
 */
class Imprumut {
private:
    vector<Carte> carti;          // Lista de cărți împrumutate
    Data data;                    // Data la care s-a realizat împrumutul
    string numeUtilizator;        // Numele utilizatorului care a împrumutat

public:
    // Constructor implicit – creează un împrumut gol
    Imprumut();

    // Constructor cu parametri – inițializează toate atributele cu valorile specificate
    Imprumut(const string& numeUtilizator, const Data& data, const vector<Carte>& carti);

    // Returnează numele utilizatorului
    string getNumeUtilizator() const;

    // Returnează data împrumutului
    Data getData() const;

    // Returnează lista cărților împrumutate
    vector<Carte> getCarti() const;

    // Setează numele utilizatorului
    void setNumeUtilizator(const string& nume);

    // Setează data împrumutului
    void setData(const Data& data);

    // Setează lista de cărți împrumutate
    void setCarti(const vector<Carte>& carti);

    // Afișează toate detaliile împrumutului (pentru debug sau vizualizare)
    void afisare() const;
};

#endif // IMPRUMUT_H
