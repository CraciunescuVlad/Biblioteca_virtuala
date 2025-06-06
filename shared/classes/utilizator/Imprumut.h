#ifndef IMPRUMUT_H
#define IMPRUMUT_H
#include <vector>
#include <string>
#include "../administrator/Carte.h"
#include "../utilizator/Data.h"
using namespace std;


class Imprumut {
private:
    vector<Carte> carti;
    Data data;
    string numeUtilizator;
public:
    Imprumut();
    Imprumut(const string& numeUtilizator, const Data& data, const vector<Carte>& carti);

    string getNumeUtilizator() const;
    Data getData() const;
    vector<Carte> getCarti() const;

    void setNumeUtilizator(const string& nume);
    void setData(const Data& data);
    void setCarti(const vector<Carte>& carti);

    void afisare() const;
};


#endif //IMPRUMUT_H
