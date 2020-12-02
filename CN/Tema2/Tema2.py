import numpy as np
import proceduri as proc

def Ex2V4():
    d, f, c, n = 9, -3, -3, 15
    sistem = np.zeros((n, n), int)
    sistem[range(n), range(n)] = d
    sistem[range(1, n), range(n - 1)] = c
    sistem[range(n - 1), range(1, n)] = f

    termeni_liberi = np.ones((n, 1), int)
    termeni_liberi[0, 0] = termeni_liberi[n - 1, 0] = 2

    tol = 10 ** -16
    L, U, w = proc.FactLU(sistem, termeni_liberi, tol)

    termeni_liberi_noi = np.copy(termeni_liberi)
    for i in range(n):
        termeni_liberi_noi[i] = termeni_liberi[w[i]]

    y = proc.metSubAsc(L, termeni_liberi_noi, tol)
    x = proc.metSubDesc(U, y, tol)
    print(f'Solutia sistemului: \n {x}')

def Ex3v4():
    sistem = np.array([[1, 1, 5], [2, 17, 20], [2, 7, 13]])
    termeni_liberi = np.array([[4], [33], [16]])

    det, A_invers = proc.InvDet(sistem)

    print("Determinantul matricei este %d\nInversa matricei este:\n" % det, A_invers)
    print("Solutia sistemului este:\n", A_invers@termeni_liberi)

def Ex4V4():
    n = 6
    b = np.array(([i ** 4 for i in range(1, n + 1)],)).T
    a = np.array(([4 ** i for i in range(n, 0, -1)]))
    A = np.zeros((n,n))
    for lin in range(n):
        for col in range(n):
            A[lin][col] = a[abs(lin-col) % n]
    a = a.reshape((6,1))

    #1) Vectorul a si matricea A
    print(a)
    print(A.astype(int), '\n')

    #2) trecem prin toti minorii principali
    A_aux = np.copy(A)
    if proc.Det(A_aux) < 0:
        print("Matricea nu este pozitiv definita, conform criteriului lui Sylvester.\n")
    else:
        for i in range(n-1, 0, -1):
            A_aux = np.delete(A_aux, i, 0)
            A_aux = np.delete(A_aux, i, 1)
            if proc.Det(A_aux) < 0:
                print("Matricea nu este pozitiv definita, conform criteriului lui Sylvester.\n")
        if i == 1 and A_aux[0][0] > 0:
            print("Matricea este pozitiv definita, conform criteriului lui Sylvester.\n")

    #3 + 4) Functia pentru factorizarea Cholesky, cat si L si L.T
    L = proc.FactCholesky(A.astype(int), b)
    print("L:\n", L)
    print("L.T:\n", L.T)

    if ((L@L.T).astype(int) == A.astype(int)).all():
        print("Verificare facuta!!")

    #6) Matricea L si solutia sistemului Ly = b, care vor fi afisate mai jos.
    y = proc.metSubAsc(L, b, tol = 10 ** (-20))
    #5) Solutia sistemului Ax = b
    x = proc.metSubDesc(L.T, y, tol = 10 ** (-20))

    print("Solutia sistemului Ax = b este:\n", x)

    print("L:\n", L)
    print("Solutia sistemului Ly = b este:\n", y)


if __name__ == '__main__':
    # Ex2V4()
    # Ex3v4()
    # Ex4V4()