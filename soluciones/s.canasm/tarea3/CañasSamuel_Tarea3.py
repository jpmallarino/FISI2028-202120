#!/usr/bin/env python
# coding: utf-8

# In[21]:


#Tarea 3 Metodos Computacionales 
#Samuel David Cañas Molina - 201922001 


import numpy as np
import matplotlib as mpl
import scipy as sp
import pandas as pd
import sklearn as sl
import seaborn as sns; sns.set()

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm

get_ipython().run_line_magic('matplotlib', 'inline')


#Tarea 3: Encuentre la regresión
#Usted recibe unos datos x y y cómo se muestran a continuación. Usted debe responder cuatro preguntas a partir de estos datos. 
#Suponga que usted tiene un modelo tal que y=f(x) más aún desconoce f.

df = pd.read_pickle("ex1.gz")
sns.scatterplot(x ='x',y ='y',data=df, label = "Datos")
plt.legend(loc="upper right")
plt.show()
df

# Punto (A) Pendiente e intercepto
# Determine la pendiente de los datos en el intervalo [0,1.5] y el valor del intercepto con el eje y. 
#Es decir, f(0)=?. ¿Cuál es el valor de r^2?

lx = df["x"]
ly = df["y"]


xt = []
yt = []
for i in range(len(lx)):
    if(0 <= lx[i] <= 1.5):
        xt.append(lx[i])
        yt.append(ly[i])

x = np.array(xt)
y = np.array(yt)


n = len(x)
sumx = sum(x)
sumy = sum(y)
sumxy = sum(x*y)
sumx2 = sum(x**2)
sumy2 = sum(y**2)
promx = sumx/n
promy = sumy/n

m = (sumx*sumy-(n*sumxy))/(sumx**2-(n*sumx2))
b = promy - m*promx

m, b

sns.scatterplot(x='x',y='y',data=df, label = "Datos")
plt.plot(x, m*x + b, color = "k", label = "Ajuste")
plt.legend(loc="upper right")
plt.title("Regresión polinomial en intervalo de 0 a 1.5")
plt.show()

sigmax = np.sqrt((sumx2/n) - promx**2)
sigmay = np.sqrt(sumy2/n - promy**2)
covar = (sumxy/n) - (promx*promy)
r2 = (covar/(sigmax*sigmay))**2


#Punto (B) Regresión polinomial
# Suponga que quiere realizar la siguiente regresión polinomial:
#y=\beta+\beta_1x+\beta_2x^2+\beta_2x^3+\beta_2x^4+\beta_2x^5.
# Plantee la función de costo que le permita calcular los coeficientes y calcule: 
#$\beta_1, \beta_2, \beta_3, \beta_4, y \beta_5. ¿Cuál es el r^2?

# Calcule f(0) y compare con los resultados anteriores

A = []
for i in range(len(lx)):
    A.append([1, lx[i], lx[i]**2, lx[i]**3, lx[i]**4, lx[i]**5])

Matriz = np.matrix(A)

b = np.array([ly]).reshape(-1,1)

Mb = np.matrix(b)


def L(k,Matriz,Mb):
    
    m,n = Matriz.shape
    X = np.matrix(k).T
    DeltaB=(Matriz*X - Mb) 
    return (DeltaB.T*DeltaB)[0,0]/m 

def dLdx(k,Matriz,Mb):
    
    m,n = Matriz.shape
    X = np.matrix(k).T
    DeltaB=(Matriz*X - Mb) 
    return (2/m)*np.array(Matriz.T*DeltaB).flatten() 

e = 1e-10

res1 = sp.optimize.minimize(fun=L,x0=np.zeros(Matriz.shape[1]), args = (Matriz,Mb), tol=1e-10)
res1['x']

#Calculo de f(0) y de cada coeficiente 
# $f(0)$ =  0.35735768,
# $\beta_1$ = -0.84260174,
# $\beta_2$ = 3.78478429,
# $\beta_3$ = -3.00338516,
# $\beta_4$ =  0.85844412,
# $\beta_5$ = -0.08305811


L(res1['x'],Matriz,Mb)


#Valor de la función de costo
# L = 0.012550626817337412

k =  np.linspace(0,4,100)

def Poli(c5,c4,c3,c2,c1,b,x):
    return  b +  c1*x +c2*(x**2) + c3*(x**3)+ c4*(x**4) +c5*(x**5) 

pre = Poli(res1['x'][5],res1['x'][4],res1['x'][3],res1['x'][2],res1['x'][1],res1['x'][0],k)

r2 = 1-np.sum((pre - ly)**2)/np.sum((ly-ly.mean())**2)
r2, pre[0]


#r^2 = 0.9111078914676154
#f(0)= 0.3573580251551316

sns.scatterplot(x ='x',y ='y',data=df, label = "Datos")
plt.plot(lx,pre,"--", color='k', label = "Ajuste")
plt.title("Regresión polinomial")
plt.legend(loc="upper right")



# Punto (C) Regresión polinomial exacta
# Resulta, que cuando se quiere hacer alguna regresión polinomial esta se puede hacer de forma exacta. 
#¿Cómo? Suponga que ud va a considerar que su problema en lugar de tener $1$ variable ($x$) tiene $n+1$, 
#siendo $n$ el orden del polinomio a ajustar. Es decir, sus nuevas variables van a ser:
#$\{x_0,\,x_1,\,x_2,\,x_3,\dots,\,x_n\}$ definiendo $x_j=x^j$. 
#Así pues, siguiendo el mismo procedimiento para la regresión lineal multidimensional que realizamos para el ejercicio de datos inmobiliarios, puede encontrar los valores de los coeficientes $\beta_1$, $\beta_2$, $\beta_3$, $\beta_4$, y $\beta_5$. Encuentre estos valores y compare con los resultados en la sección (B).
# Calcule f(0) y compare con los resultados anteriores.
# Si ud se pregunta si esto es posible la respuesta es sí. Inclusive, esto se puede extender a cualquier a cualquier conjunto de funciones, tal que $x_j=f_j(x)$, que represente un conjunto "linealmente independiente" (¡Me estoy adelantando a Fourier!). Para quienes quieran explorar algunas curiosidades matemáticas, cuando $n+1$ es igual al número de puntos o valores de $x$ (y todos diferentes) la matriz es siempre invertible y resulta ser la inversa de una matriz de Vandermonde.

lx = df["x"]
ly = df["y"]

X = np.array(lx).reshape(-1, 1)
Y = np.array(ly).reshape(-1, 1)

P = np.array([np.ones([len(lx), 1]), X, X**2, X**3, X**4, X**5]).reshape(6, len(lx)).T
coeffs = np.linalg.inv(P.T @ P) @ P.T @ Y

b, c1, c2, c3, c4, c5 = coeffs

coeffs

Ajuste = b + (c1*X) + (c2*X**2) + (c3*X**3) +  (c4*X**4) + (c5*X**5)

plt.figure()
sns.scatterplot(x='x',y='y',data = df, label = "datos")
plt.plot(X, Ajuste, c ='k', label = "Ajuste")
plt.legend(loc="upper left")
plt.title("Regresión polinomial exacta")
plt.ylabel('y')
plt.xlabel('x')
plt.show()

p = np.array(P@coeffs).flatten()
o = np.array(Y).flatten()
k = o.mean()

r2 = 1 - (np.linalg.norm(p - o)**2)/(np.linalg.norm(o - k)**2)

# r^2 = 0.9199225041318263
#f(0)=0.35644669

# Punto (D) Regresión a un modelo teórico
# Suponga que su modelo teórico es el siguiente:y=\frac{a}{\left[(x-b)^2+c\right]^\gamma}.Halle a, b, c y \gamma.
# Calcule f(0) y compare con los resultados anteriores

def f(parametro,x): 
    return (parametro[0])/((x-parametro[1])**2 + parametro[2])**parametro[3]

def Lfit(parametro,x,y): 
    deltaY=f(parametro,x) - y
    return np.dot(deltaY,deltaY)/len(y)

e = 1e-8

res2 = sp.optimize.minimize(fun=Lfit, x0=np.array([0,1,0,0]), args = (x,y), method='L-BFGS-B', tol=e)

res2["x"]


# a =0.94519587,
#b = 1.43859817
#c = 0.7390972 
#\gamma = 1.12724243

pre2 = f(res2.x,lx)

b = f(res2.x,0)

# f(0)=0.2950897972713322

plt.figure()
plt.scatter(lx,ly, label = "Datos")
plt.plot(lx,pre2, c = 'k', label = "Ajuste")
plt.legend(loc="upper left")
plt.title("Regresión a un modelo teórico")
plt.ylabel('y')
plt.xlabel('x')
plt.show()


# In[ ]:





# In[ ]:





# In[ ]:




