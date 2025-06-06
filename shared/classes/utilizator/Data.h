#ifndef DATA_H
#define DATA_H

// Clasa Data reprezintă o dată calendaristică
class Data {
private:
    int zi;     // Ziua lunii (1-31)
    int luna;   // Luna anului (1-12)
    int an;     // Anul (de ex., 2025)

public:
    // Constructor implicit – inițializează data cu valori implicite (0)
    Data();

    // Constructor cu parametri – inițializează data cu valorile primite
    Data(int zi, int luna, int an);

    // Getteri – returnează valorile curente ale câmpurilor
    int getZi() const;
    int getLuna() const;
    int getAn() const;

    // Setteri – actualizează valorile câmpurilor
    void setZi(int zi);
    void setLuna(int luna);
    void setAn(int an);
};

#endif //DATA_H
