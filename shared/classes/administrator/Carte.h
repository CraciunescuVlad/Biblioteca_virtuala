#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <iostream>
using namespace std;

/**
 * Clasa Carte reprezintă o entitate fundamentală într-o bibliotecă,
 * care conține informații despre o carte: ISBN, titlu, autor și stocul disponibil.
 */
class Carte {
private:
    // Codul ISBN al cărții (identificator unic)
    string isbn;

    // Titlul cărții
    string titlu;

    // Numele autorului
    string autor;

    // Numărul de exemplare disponibile
    int stoc;

public:
    /**
     * Constructor implicit - inițializează câmpurile cu valori neutre.
     */
    Carte();

    /**
     * Constructor parametrizat - creează o carte cu informațiile oferite.
     * @param isbn - codul ISBN
     * @param titlu - titlul cărții
     * @param autor - autorul cărții
     * @param stoc - numărul de exemplare disponibile
     */
    Carte(const string& isbn, const string& titlu, const string& autor, int stoc);

    // Metode de acces (getteri) pentru a obține informațiile cărții
    string getISBN() const;
    string getTitlu() const;
    string getAutor() const;
    int getStoc() const;

    // Metodă pentru a actualiza stocul
    void setStoc(int nouStoc);

    // Metodă pentru afișarea informațiilor despre carte
    void afiseaze() const;
};

/**
 * Supraincarcarea operatorului de inserare (<<) pentru a permite
 * afișarea obiectelor de tip Carte folosind cout sau în fișiere.
 */
ostream& operator<<(ostream& out, const Carte& carte);

#endif // CARTE_H
