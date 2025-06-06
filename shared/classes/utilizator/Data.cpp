#include "Data.h"

// Constructor implicit – inițializează data cu 1 ianuarie anul 1
Data::Data() : zi(1), luna(1), an(1) {}

// Constructor cu parametri – setează ziua, luna și anul cu valorile primite
Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

// Getter pentru zi
int Data::getZi() const {
    return zi;
}

// Getter pentru lună
int Data::getLuna() const {
    return luna;
}

// Getter pentru an
int Data::getAn() const {
    return an;
}

// Setter pentru zi – actualizează atributul zi
void Data::setZi(int zi) {
    this->zi = zi;
}

// Setter pentru lună – actualizează atributul luna
void Data::setLuna(int luna) {
    this->luna = luna;
}

// Setter pentru an – actualizează atributul an
void Data::setAn(int an) {
    this->an = an;
}
