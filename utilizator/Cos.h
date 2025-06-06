#ifndef COS_H
#define COS_H

#include <map>
#include <string>
using namespace std;


class Cos {
private:
    map<string, int> carti;
public:
    Cos();

    void adaugaCarte(const string& isbn, int numar);
    void modificareCarte(const string& isbn, int nouNumar);
    void stergeCarte(const string& isbn);
    void vizualizeazaCos() const;

    map<string, int> getCarti() const;
    void setCarti(const map<string, int>& cartiNoi);
};



#endif //COS_H
