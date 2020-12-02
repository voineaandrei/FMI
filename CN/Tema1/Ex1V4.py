# -*- coding: utf-8 -*-
import numpy as np
import math
import matplotlib.pyplot as plt

# Exercitiul 1 Varianta 4


# Functie pentru cautarea intervalelor in care f(x) are solutii.
# f(a) * f(b) < 0 => exista x intre a si b, astfel incat f(x) = 0.
def cauta_intervale(f, a, b, n):
    """
    :param f: functia ecuatiei
    :param a: capatul din stanga a intervalului
    :param b: capatul din dreapta a intervalului
    :param n: numarul de subintervale in care impartim intervalul initial
    :return: matrice cu 2 linii si N coloane, unde
             pe primia linie vor fi capetele din stanga a subintervalelor unde gasim solutii
             pe a doua linie vor fi capetele din dreapta a subintervalelor unde gasim solutii
             N coloane = N solutii
    """
    # Returneaza n + 1 numere, situate la distanțe egale, din cadrul intervalului [a, b]
    subintervale = np.linspace(a, b, n + 1)

    for i in range(len(subintervale)):
        if (f(subintervale[i]) == 0):  # Trebuie să avem soluțiile în intervale, nu la capete
            print("Schimba numarul de subintervale!")
            exit(0)

    matrice = np.zeros((2, 1000))  # matrice(2, 1000) plina de 0
    nr_solutii = 0
    for i in range(n):
        if f(subintervale[i]) * f(subintervale[i + 1]) < 0:  # exista solutie
            matrice[0][nr_solutii] = subintervale[i]
            matrice[1][nr_solutii] = subintervale[i + 1]
            nr_solutii += 1

    matrice_solutii = matrice[:, 0:nr_solutii]  # luam toate liniile si coloanele de la 0 la nr_solutii
    return matrice_solutii


def MetSecantei(f, x0, x1, eps):
    k = 1
    x = [x0, x1]

    while abs(x[k] - x[k - 1]) / abs(x[k - 1]) >= eps:
        k += 1
        x.append((x[k - 2] * f(x[k - 1]) - x[k - 1] * f(x[k - 2])) / (f(x[k - 1]) - f(x[k - 2])))
        if x[k] < x0 or x[k] > x1:
            print("Introduceti alte valori pentru x0 si x1!")
            exit(0)

    return x[k], k - 1


def MetPozFalse(f, a0, b0, eps):
    k = 0
    a = [a0]
    b = [b0]
    x = [(a[0] * f(b[0]) - b[0] * f(a[0])) / (f(b[0]) - f(a[0]))]

    while True:
        k += 1
        if f(x[k - 1]) == 0:
            return x[k - 1], k
        elif f(a[k - 1]) * f(x[k - 1]) < 0:
            a.append(a[k - 1])
            b.append(x[k - 1])
            x.append((a[k] * f(b[k]) - b[k] * f(a[k])) / (f(b[k]) - f(a[k])))
        elif f(a[k - 1]) * f(x[k - 1]) > 0:
            a.append(x[k - 1])
            b.append(b[k - 1])
            x.append((a[k] * f(b[k]) - b[k] * f(a[k])) / (f(b[k]) - f(a[k])))
        if abs(x[k] - x[k - 1]) / abs(x[k - 1]) < eps:
            break

    return x[k], k


if __name__ == '__main__':

    # Varianta 4 f(x) si [a,b]
    def f(x):
        y = 2 * x * math.cos(2 * x) - x + 2
        return y

    a, b = -4, 3

    # Gasim subintervalele in care se afla solutiile
    intervale = cauta_intervale(f, a, b, 10)
    nr_solutii = len(intervale[0])

    # Solutii pentru metoda secantei, folosind eps = 10^(-5)
    print("Solutii pentru metoda secantei, folosind epsilon = 0.00001")
    solutii_met_sec = []
    for i in range(nr_solutii):
        solutii_met_sec.append(MetSecantei(f, intervale[0][i], intervale[1][i], 10**-5))
    print(solutii_met_sec)

    # Solutii pentru metoda pozitiei false, folosind eps = 10^(-5)
    print("Solutii pentru pozitiei false, folosind epsilon = 0.00001")
    solutii_met_poz_false = []
    for i in range(nr_solutii):
        solutii_met_poz_false.append(MetPozFalse(f, intervale[0][i], intervale[1][i], 10**-5))
    print(solutii_met_poz_false)

    def f(x_list):
        y_list = []
        for x in x_list:
            y = 2 * x * math.cos(2 * x) - x + 2
            y_list.append(y)
        return y_list

    # Graficul; rosu - metoda secantei; verde - metoda pozitiei false
    x_grafic_sec = np.linspace(a, b, 100)
    y_grafic_sec = f(x_grafic_sec)
    plt.plot(x_grafic_sec, y_grafic_sec, marker = ',', color = 'blue', linewidth = 3)
    plt.axvline(0, color = 'black')
    plt.axhline(0, color = 'black')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Exercitiul 1 Varianta 4')
    plt.grid(True)
    for i in range(nr_solutii):
        plt.plot(solutii_met_sec[i][0], 0, marker = 'o', color = 'red', linewidth = 6)
        plt.plot(solutii_met_poz_false[i][0], 0, marker = 'o', color = 'green', linewidth = 6)
    plt.show()