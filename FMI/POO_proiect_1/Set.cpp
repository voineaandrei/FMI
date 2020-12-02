#include "Set.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Set::Set()
{
    Numar=0;
    Multime=NULL;
}
Set::Set(const Set& obj)
{
    this->Numar=obj.Numar;
    this->Multime=(int *)(malloc(sizeof(int)*(this->Numar)));
    for (int i=0; i<this->Numar; i++)
        this->Multime[i]=obj.Multime[i];
}
Set::~Set()
{
    Numar=0;
    free(Multime);
}
ostream& operator << (ostream& out, const Set& obj)
{
    if (obj.Numar==0)
    {
        out<<"Multimea vida"<<endl;
        return out;
    }
    out<<obj.Numar<<" numar/numere:";
    for (int i=0; i<obj.Numar; i++)
        out<<obj.Multime[i]<<" ";
    out<<endl;
    return out;
}

istream& operator >> (istream& in, Set& obj)
{
    delete[] obj.Multime;
    in>>obj.Numar;
    obj.Multime=(int *)(malloc(sizeof(int)*obj.Numar));
    for (int i=0; i<obj.Numar; i++)
        in>>obj.Multime[i];
    return in;
}
void Set::Inserare(int x) // Se insereaza x la finalul vectorului
{
    Multime=(int *)(realloc(Multime,(sizeof(int)*(Numar+1))));
    Multime[Numar]=x;
    Numar++;
}
int Set::Cautare(int x) // Se cauta x in vector
{
    for (int i=0; i<Numar; i++)
        if (Multime[i]==x)
            return i;
    cout<<"Nu e in vector";
    return -1;
    //Am incercat sa fac cu throw, catch aici. Habar n-am.
}
void Set::Stergere(int x) // Se sterge x din vector
{
    for (int i=0; i<Numar; i++)
        if (Multime[i]==x)
        {
            for (int j=i; j<Numar-1; j++)
                Multime[j]=Multime[j+1];
            Numar--;
            Multime=(int *)(realloc(Multime,sizeof(int)*Numar));
            return; // Se considera ca functia Proprietate() se aplica inaintea functiei Stergere()
        }
}

void Set::Proprietate() //Se ordoneaza vectorul si se verifica pozitiile vecine v[i]!=v[i+1]
{
    Ordonare(Multime,0,Numar-1);
    for (int i=0; i<Numar-1; i++)
        if (Multime[i]==Multime[i+1])
        {
            for (int j=i; j<Numar-1; j++)
                Multime[j]=Multime[j+1];
            Numar--;
            i--;
        }
    Multime=(int *)realloc(Multime,sizeof(int)*Numar);
}

void Set::Ordonare(int v[], int st, int dr)  // qsort, se apeleaza cu A.GetMultime(),0,A.GetNumar()-1
{
    if (st>=dr)
        return;
    int pivot = v[dr];
    int poz=st-1;
    for (int i=st; i<dr; i++)
        if (v[i]<pivot)
        {
            poz++;
            swap(v[poz],v[i]);
        }
    swap(v[poz+1],v[dr]);
    Ordonare(v,st,poz);
    Ordonare(v,poz+2,dr);
}
Set& Set::operator = (const Set &Aux)
{
    this->Numar=Aux.Numar;
    this->Multime=(int *)(malloc(sizeof(int)*this->Numar));
    for (int i=0; i<Numar; i++)
        this->Multime[i]=Aux.Multime[i];
    return *this;
}
Set Set::operator + (const Set &Aux)
{
    Set Aux2;
    Aux2.Numar=this->Numar+Aux.Numar;
    Aux2.Multime=new int[this->Numar+Aux.Numar];
    for (int i=0; i<this->Numar; i++)
        Aux2.Multime[i]=this->Multime[i];
    for (int i=0; i<Aux.Numar; i++)
        Aux2.Multime[this->Numar+i]=Aux.Multime[i];
    Aux2.Proprietate();
    return Aux2;
}
int Set::operator < (const Set& Aux)
{
    if (this->Numar<Aux.Numar)
        return 1;
    return 0;
}
int Set::operator > (const Set& Aux)
{
    if (this->Numar>Aux.Numar)
        return 1;
    return 0;
}
int Set::operator [] (int index)
{
    return this->Multime[index];
}
Set Set::operator * (int scalar)
{
    Set Aux2;
    Aux2.Multime=(int *)(malloc(sizeof(int)*this->Numar));
    Aux2.Numar=this->Numar;
    for (int i=0; i<this->Numar; i++)
        Aux2.Multime[i]=this->Multime[i]*scalar;
    return Aux2;
}
void Set::Afisare()
{
    if (Numar==0)
    {
        cout<<"Multimea vida"<<endl;
        return;
    }
    cout<<Numar<<" numar/numere:";
    for (int i=0; i<Numar; i++)
        cout<<Multime[i]<<" ";
    cout<<endl;
}
int Set::Suma()
{
    int suma=0;
    for (int i=0; i<Numar; i++)
        suma+=Multime[i];
    return suma;
}
void Set::Numere_Pare_Impare()
{
    int *poz=new int[Numar];
    int k=0;
    cout<<"Numerele pare sunt: ";
    for (int i=0; i<Numar; i++)
        if (Multime[i]%2==0)
            cout<<Multime[i]<<" ";
        else
            poz[k++]=i;
    poz=(int *)realloc(poz,sizeof(int)*k);
    cout<<"\nNumerele impare sunt: ";
    for (int i=0; i<k; i++)
            cout<<Multime[poz[i]]<<" ";
    cout<<endl;
    delete[] poz;
}
int Set::GetNumar()
{
    return Numar;
}
int* Set::GetMultime()
{
    return Multime;
}
