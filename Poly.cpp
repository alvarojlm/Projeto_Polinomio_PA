#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <limits>

#include "Poly.h"
using namespace std;

ostream& operator<<(ostream& Sd, const Poly& P){
if(P.D>0){
for(int i=P.D-1; i>=1; i--){
if(P.x[i]!=0){
if(P.x[i]!=1)Sd <<P.x[i];
Sd <<(P.x[i]!=1 ? "*x" : "x")<<(i!=1 ? "^" : "");
if(i!=1) Sd << i;
if(P.x[i-1]>0) Sd << " +";
if(P.x[i-1]==0) Sd << "";
   }
}
if(P.x[0]!=0) Sd << P.x[0];
}
if(P.D==1) Sd <<(P.x[0]<0 ? "-" : "") << P.x[0];
return Sd;
}
istream &operator>>(istream &Et, Poly &P){
int i=P.D-1;
if(P.D<=0) cerr << "Erro, grau invalido";
else{
    while(i>=0){
    cout << "Digite o coeficiente de x^" << i <<": ";
    Et >> P.x[i];
    if(P.x[P.D-1]==0){
            cerr << "O coefiente de maior grau nao pode ser nulo, digite novamente: ";
    Et >> P.x[P.D-1];
    }
    i--;
}
}
}
void Poly::criar(unsigned Dim){
limpar();
D=Dim;
x = (D>0 ? new float[D] : nullptr);
}
void Poly::copy(const Poly &P){
limpar();
criar(P.D);
for (int i = 0; i<D;i++) x[i]=P.x[i];
}
Poly::Poly(unsigned Dim){
criar(Dim);
if(Dim>0){
for (unsigned i = 0; i<Dim-1;i++) x[i]=0.0;
x[Dim-1]=1.0;
}
}
void Poly::limpar(){
if(x!=nullptr) delete [] x;
x=nullptr; D=0;
}
void Poly::recriar(unsigned grau){
Poly P_use;
P_use.D=grau+1;
P_use.criar(P_use.D);
if(P_use.D>0) {
for (int i = 0; i<P_use.D-1;i++) x[i]=0.0;
x[P_use.D-1]=1.0;
}
limpar();
copy(P_use);
}
int Poly::getGrau(){
if(D>0) return (D-1);
if(D=0) return -1;
}
float Poly::getCoef(unsigned i){
if(i>=D) return 0.0;
if(i<D && i>=0) return x[i];
}
float Poly::getValor(float valor){
float total=0, total_1=1;
int i=0, j;
do{
for(j=1;j<=i;j++){
    total_1=total_1*valor;
}
total= total_1*x[i];
total_1=1;
i++;
}while(i<=D-1);
total=total+x[0];
return total;
}
void Poly::setCoef(unsigned i, float novo){
if(i>=D) cerr << "Indice nao pode receber novo valor";
if(i<D-1) x[i]=novo;
if(i==D-1 && novo!=0 && D>1){
    x[i]=novo;
}
else if(i==D-1 && novo==0 && D==1){
        x[i]=novo;
}
}
bool Poly::salvar(string nome){
 ofstream arq_salvar;
 arq_salvar.open(nome.c_str());
 arq_salvar << "POLY " << D << endl;
 if(D>0){
 for(int i=0;i<D;i++) arq_salvar << x[i] <<' ';
 }
 arq_salvar << '\n';
 if(!arq_salvar.is_open()){
    return false;
 }
 else{
    return true;
 }
 arq_salvar.close();
}
bool Poly::ler(string nome){
ifstream arq_salvo;
arq_salvo.open(nome.c_str());
if(!arq_salvo.is_open()){
    cout <<"erro";
    return false;
}
 else{
string verifica;
getline(arq_salvo, verifica, ' ');
if(verifica!="POLY"){
cout << "Arquivo invalido no POLY";
exit(0);
}
arq_salvo >> D;
arq_salvo >> ws;
criar(D);
for(int i=0;i<(2*D);i++) arq_salvo >> x[i];
arq_salvo.close();
return true;
 }

}
void Poly::operator=(const Poly &P){
if(this != &P) limpar();
copy(P);
}
Poly Poly::operator+(const Poly &P) const{
Poly P_use;
int i;
if(D==P.D){
P_use.criar(D);
for(i=0;i<D;i++) P_use.x[i]= x[i]+P.x[i];
}
else if(D>P.D){
P_use.criar(D);
for(i=0;i<P.D;i++) P_use.x[i]= x[i]+P.x[i];
for(i=P.D;i<D;i++) P_use.x[i]= x[i];
}
else if(D<P.D){
P_use.criar(P.D);
for(i=0;i<D;i++) P_use.x[i]= x[i]+P.x[i];
for(i=D;i<P.D;i++) P_use.x[i]= P.x[i];
}
return P_use;
}
Poly Poly::operator-(const Poly &P) const{
Poly P_use;
int i;
if(D==P.D){
P_use.criar(D);
for(i=0;i<D;i++) P_use.x[i]= x[i]-P.x[i];
}
else if(D>P.D){
P_use.criar(D);
for(i=0;i<P.D;i++) P_use.x[i]= x[i]-P.x[i];
for(i=P.D;i<D;i++) P_use.x[i]= x[i];
}
else if(D<P.D){
P_use.criar(P.D);
for(i=0;i<D;i++) P_use.x[i]= x[i]-P.x[i];
for(i=D;i<P.D;i++) P_use.x[i]= -P.x[i];
}

return P_use;
}
Poly Poly::operator*(const Poly &P) const{
Poly P_use;
int i;
if(D==P.D){
P_use.criar(D);
for(i=0;i<D;i++) P_use.x[i]= x[i]*P.x[i];
}
else if(D<P.D){
P_use.criar(D);
for(i=0;i<P.D;i++) P_use.x[i]= x[i]*P.x[i];
}
else if(D>P.D){
P_use.criar(P.D);
for(i=0;i<D;i++) P_use.x[i]= x[i]*P.x[i];
}

return P_use;
}
Poly Poly::operator-() const{
Poly P_use;
P_use.criar(D);
for(int i=0;i<D;i++) P_use.x[i]= -1*x[i];
return P_use;
}
float Poly::operator[](unsigned i){
return getCoef(i);
}
float Poly::operator()(float valor){
return getValor(valor);
}

