import numpy as np


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


def gauss_piv_partiala(A, b, tol):
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

    for k in range(n - 1):
        max = A_extins[k][k]
        p = k
        for j in range(k + 1, n):
            if abs(A_extins[j][k]) > abs(max):
                max = A_extins[j][k]
                p = j

        if abs(max) <= tol:
            print("Sistemul nu admite solutie unica")
            x = None
            return x

        if (p != k):
            A_extins[[p, k]] = A_extins[[k, p]]  # swap linia p cu linia k
            print('Schimbam linia %d cu linia %d\n' %(p, k), A_extins)

        for j in range(k + 1, n):
            A_extins[j] = A_extins[j] - (A_extins[j][k] / A_extins[k][k]) * A_extins[k]
            print("Matricea curenta:")
            print(A_extins)

    if abs(A_extins[n - 1][n - 1]) <= tol:
        print("Sistemul nu admite solutie unica")
        x = None
        return x

    x = met_subs_desc(A_extins[:, 0:n], A_extins[:, n], tol)
    return x


if __name__ == '__main__':
    sistem = [[1, 1, 5], [2, 17, 20], [2, 7, 13]]
    termeni_liberi = [[4], [33], [16]]
    tol = 10 ** -16

    solutie = gauss_piv_partiala(sistem, termeni_liberi, tol)
    print("Solutia sistemului este: x1 = %.2f, x2 = %.2f, x3 = %.2f" % (solutie[0], solutie[1], solutie[2]))