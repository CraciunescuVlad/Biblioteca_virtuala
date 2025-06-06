#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <iostream>
using namespace std;

class Carte {
private:
    string isbn;
    string titlu;
    string autor;
    int stoc;
public:
    Carte();
    Carte(const string& isbn, const string& titlu, const string& autor, int stoc);
    string getISBN() const;
    string getTitlu() const;
    string getAutor() const;
    int getStoc() const;
    void setStoc(int nouStoc);
    void afiseaze() const;
};



#endif //CARTE_H
ostream& operator<<(ostream& out, const Carte& carte);