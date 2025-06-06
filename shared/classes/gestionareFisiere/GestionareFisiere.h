#ifndef GESTIONAREFISIERE_H
#define GESTIONAREFISIERE_H

#include <vector>
#include <map>
#include <string>
#include "Carte.h"
#include "../utilizator/Data.h"
#include "../utilizator/Imprumut.h"
using namespace std;


class GestionareFisiere {
public:
    //Carti
    static vector<Carte> incarcaCarti(const string& numeFisier = "carti.txt");
    static void salveazaCarti(const vector<Carte>& carti, const string& numeFisier = "carti.txt");

    //Cos
    static map<string, int> incarcaCos(const string& numeFisier = "cos_utilizator.txt");
    static void salveazaCos(const map<string, int>& cos, const string& numeFisier = "cos_utilizator.txt");

    //Imprumut
    static void salveazaImprumut(const Imprumut& imprumut, const string& numeFisier = "imprumuturi.txt");
};



#endif //GESTIONAREFISIERE_H
