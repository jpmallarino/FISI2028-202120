import numpy as np
import pandas as pd
import scipy as sp
import sklearn as sl

import seaborn as sns
from sklearn.metrics import r2_score

sns.set()
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm


def regresion(coeficiente, x, y):
    mx = []
    my = []

    for i in range(coeficiente):
        my.append([])
        suma = [0] * len(x)
        # for co in range(i):
        for k in range(len(x)):
            suma[k] = pow(x[k], i)
        for k in range(len(x)):
            suma[k] *= y[k]
        my[i].append(sum(suma))
    for i in range(coeficiente):
        for j in range(coeficiente):
            if j == 0:
                mx.append([])
            if i == 0 and j == 0:
                mx[i].append(len(y))
            else:
                suma = [0] * len(x)
                for k in range(len(x)):
                    suma[k] = pow(x[k], i + j)
                mx[i].append(sum(suma))

    mx = np.array(mx)
    my = np.array(my)

    casicero = 1e-15

    mx = np.array(mx, dtype=float)

    mxy = np.concatenate((mx, my), axis=1)
    mxy0 = np.copy(mxy)

    tamano = np.shape(mxy)
    n = tamano[0]
    m = tamano[1]

    for i in range(0, n - 1, 1):
        columna = abs(mxy[i:, i])
        dondemax = np.argmax(columna)
        if dondemax != 0:
            temporal = np.copy(mxy[i, :])
            mxy[i, :] = mxy[dondemax + i, :]
            mxy[dondemax + i, :] = temporal

    mxy1 = np.copy(mxy)

    for i in range(0, n - 1, 1):
        pivote = mxy[i, i]
        adelante = i + 1
        for k in range(adelante, n, 1):
            factor = mxy[k, i] / pivote
            mxy[k, :] = mxy[k, :] - mxy[i, :] * factor
    mxy2 = np.copy(mxy)

    ultfila = n - 1
    ultcolumna = m - 1
    for i in range(ultfila, 0 - 1, -1):
        pivote = mxy[i, i]
        atras = i - 1
        for k in range(atras, 0 - 1, -1):
            factor = mxy[k, i] / pivote
            mxy[k, :] = mxy[k, :] - mxy[i, :] * factor
        # diagonal a unos
        mxy[i, :] = mxy[i, :] / mxy[i, i]
    X = np.copy(mxy[:, ultcolumna])
    X = np.transpose([X])

    coeficientes = []
    for i in X:
        coeficientes.append(i[0])

    return coeficientes


df = pd.read_pickle('ex1.gz')
sns.scatterplot(x='x',y='y',data=df)
plt.show()

datos_seleccionados = df[(0 <= df["x"]) & (df["x"] <= 1.5)]

x = list(datos_seleccionados.drop_duplicates(subset="x")["x"])
y = list(datos_seleccionados.drop_duplicates(subset="y")["y"])

r = r2_score(x, y)

regresion_lineal = regresion(2, x, y)

print(f"pendiente: {regresion_lineal[1]}")
print(f"intercepto: {regresion_lineal[0]}")
print(f"r: {r}")

polinomio = np.polynomial.polynomial.Polynomial(coef=regresion_lineal)
xx = np.arange(start=0, stop=2, step=0.5)
# plt.scatter(x, y, color="red")
plt.plot(xx, polinomio(xx), color="red")


x = list(df.drop_duplicates(subset="x")["x"])
y = list(df.drop_duplicates(subset="y")["y"])
regresion_polinomica = regresion(6, x, y)

print(f"f(0): {regresion_polinomica[0]}")
for i in range(1, 6):
    print(f"b{i}: {regresion_polinomica[i]}")

polinomio = np.polynomial.polynomial.Polynomial(coef=regresion_polinomica)
xx = np.arange(start=0, stop=4.1, step=0.1)
# plt.scatter(x, y, color="red")
plt.plot(xx, polinomio(xx), color="green")






