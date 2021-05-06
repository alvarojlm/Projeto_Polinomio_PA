#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <limits>


using namespace std;

class Poly{
private:
    unsigned D;
    float *x;
    void criar(unsigned Dim);
    void copy(const Poly &P);

public:
    inline Poly() : D(0), x(nullptr){}
    inline Poly (const Poly &P){copy(P);}
    explicit Poly (unsigned Dim);
    void limpar();
    inline ~Poly() {limpar();};

    void recriar(unsigned grau);
    int getGrau();
    float getCoef(unsigned i);
    float getValor(float valor);
    void setCoef(unsigned i, float novo);
    bool salvar(string nome);
    bool ler(string nome);

    void operator=(const Poly &P);
    Poly operator+(const Poly &P) const;
    Poly operator-(const Poly &P) const;
    Poly operator*(const Poly &P) const;
    Poly operator-() const;
    float operator[](unsigned i);
    float operator() (float valor);


    friend ostream &operator<<(ostream &Sd, const Poly &P);
    friend istream &operator>>(istream &Et, Poly &P);


};
