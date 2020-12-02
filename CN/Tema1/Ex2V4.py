import numpy as np
import fractions

def met_subs_desc(A, b, tol):
    """
    :param A: Matrice patratica, superior triunghiulara, cu toate elementele de pe diagonala principala nenule
    :param b: Vectorul termenilor lieri
    :param tol: Valoare numerica foarte mica in raport cu care vom compara numerele apropiate de 0
    :return: Solutia sistemului
    """
    m, n = np.shape(A)
    if m != n:
        print("Matricea nu este patratica. Introduceti o alta matrice.")
        x = None
        return x

    # Verificam daca matricea este superior triunghiulara
    for i in range(m):
        for j in range(i):
            if abs(A[i][j]) > tol:
                print("Matricea nu este superior triunghiulara.")
                x = None
                return x

    # Verificam daca elementele de pe diagonala principala sunt nule
    for i in range(n):
        if A[i][i] == 0:
            print("Sistemul nu este compatibil determinat.")
            x = None
            return x

    x = np.zeros((n, 1))
    x[n - 1] = b[n - 1] / A[n - 1][n - 1]
    k = n - 2
    while k >= 0:
        sum = 0
        for i in range(k + 1, n):
            sum += A[k][i] * x[i]
        x[k] = (b[k] - sum) / A[k][k]
        k = k - 1
    return x


def gauss_piv_totala(A, b, tol):
    """
    :param A: Matricea patratica asociata sistemului
    :param b: Vectorul termenilor liberi
    :param tol: Valoarea cu care comparam numerele nenule
    :return: Solutia sistemului
    """
    m, n = np.shape(A)
    if m != n:
        print("Matricea nu este patratica. Introduceti o alta matrice.")
        x = None
        return x

    A_extins = np.concatenate((A, b), axis=1)  # axis=0 l-ar pune pe b o noua linie, 1 il pune drept coloana
    print("Matricea initiala\n", A_extins)
    A_extins = A_extins.astype(float)

    x_indici = np.arange(n) # pentru a retine indicii x-ilor

    for k in range(n - 1):
        max = A_extins[k][k]
        p = k
        m = k
        for i in range(k, n):
            for j in range(k, n):
                if abs(A_extins[i][j]) > abs(max):
                    max = A_extins[i][j]
                    p = i
                    m = j

        if abs(max) <= tol:
            print("Sistemul nu admite solutie unica")
            x = None
            return x

        if (p != k):
            A_extins[[p, k]] = A_extins[[k, p]]  # swap linia p cu linia k
            print('Schimbam linia %d cu linia %d\n' %(p, k), A_extins)

        if (m != k):
            A_extins[:, [m, k]] = A_extins[:, [k, m]] # swap coloana m cu coloana k
            print('Schimbam coloana %d cu coloana %d\n' %(m, k), A_extins)
            x_indici[m], x_indici[k] = x_indici[k], x_indici[m] # swap indice m cu indice k (pentru x)

        for j in range(k + 1, n):
            A_extins[j] = A_extins[j] - (A_extins[j][k] / A_extins[k][k]) * A_extins[k]
            print("Matricea curenta:")
            print(A_extins)

    if abs(A_extins[n - 1][n - 1]) <= tol:
        print("Sistemul nu admite solutie unica")
        x = None
        return x


    x = met_subs_desc(A_extins[:, 0:n], A_extins[:, n], tol).transpose()[0]
    x_new = np.empty(n) # in x_new vom pune solutiile cu indicii corecti
    for i in range(n):
        x_new[x_indici[i]] = x[i]
    return x_new


if __name__ == '__main__':
    d, f, c, n = 9, -3, -3, 15
    sistem = np.zeros((n, n), int)
    sistem[range(n), range(n)] = d
    sistem[range(1,n), range(n-1)] = c
    sistem[range(n-1), range(1,n)] = f

    termeni_liberi = np.ones((n, 1), int)
    termeni_liberi[0, 0] = termeni_liberi[n-1, 0] = 2

    tol = 10 ** -16

    solutie = gauss_piv_totala(sistem, termeni_liberi, tol)
    for i in range(len(solutie)):
        print("x%d =" % (i + 1), fractions.Fraction(solutie[i]).limit_denominator())