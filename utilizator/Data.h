#ifndef DATA_H
#define DATA_H



class Data {
private:
    int zi;
    int luna;
    int an;
public:
    Data();
    Data(int zi, int luna, int an);

    int getZi() const;
    int getLuna() const;
    int getAn() const;

    void setZi(int zi);
    void setLuna(int luna);
    void setAn(int an);
};



#endif //DATA_H
