#include <iostream>
#include <cassert>
#include "Set.h"

using namespace std;

void SetTests()
{
    Set A;
    assert(A.GetNumar()==0);
    assert(A.GetMultime()==NULL);
    A.Inserare(1);
    A.Inserare(2);
    A.Inserare(3);
    //A.Multime={1,2,3}
    assert(A.GetNumar()==3);
    assert(A[1]==2);
    assert(A.Cautare(2)==1);
    A.Stergere(2);
    //A.Multime={1,3}
    assert(A[1]==3);

    Set B(A);
    //B.Multime={1,3}
    assert(B.GetNumar()==2);
    B.Inserare(2);
    //B.Multime={1,3,2}
    assert(B[1]>B[2]);
    B.Ordonare(B.GetMultime(),0,B.GetNumar()-1);
    assert(B[1]<B[2]);
    B.Inserare(2);
    B.Inserare(1);
    B.Inserare(3);
    B.Inserare(4);
    assert(B.GetNumar()==7);
    B.Proprietate();
    assert(B.GetNumar()==4);
    //B.Multime={1,2,3,4}
    //A.Multime={1,3}
    assert(B.Suma()==10 && A.Suma()==4);
    A=A*3;
    assert(A[0]==3 && A[1]==9);
    Set C=A+B;
    //C.Multime={1,2,3,4,9}
    assert(C.GetNumar()==5 && C[4]==9);
    assert(A<B && C>B);
    cout<<C;
    C.Numere_Pare_Impare();
}
int main()
{
    SetTests();
    return 0;
}
