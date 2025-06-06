#include "Data.h"

Data::Data() : zi(1), luna(1), an(1) {}

Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

int Data::getZi() const {
    return zi;
}

int Data::getLuna() const {
    return luna;
}

int Data::getAn() const {
    return an;
}

void Data::setZi(int zi) {
    this->zi = zi;
}

void Data::setLuna(int luna) {
    this->luna = luna;
}

void Data::setAn(int an) {
    this->an = an;
}
