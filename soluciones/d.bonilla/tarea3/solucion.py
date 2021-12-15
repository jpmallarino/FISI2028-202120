# -*- coding: utf-8 -*-
"""
Created on Mon Nov  1 20:27:56 2021

@author: danie
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as mpl
import scipy.optimize as sp

df = pd.read_pickle('ex1.gz')


#%% Regresión Lineal

dmc = df[(df['x'] <= 1.5)]

sxy = (dmc['x']*dmc['y']).sum()
sx = dmc['x'].sum()
sy = dmc['y'].sum()
sxx = (dmc['x']*dmc['x']).sum()

n = len(dmc['x'])
mean = (1/n)*(dmc['y'].sum())

m = (n*sxy - sx*sy)/(n*sxx - sx*sx)
b = (sy*sxx - sx*sxy)/(n*sxx - sx*sx)
ssres = ((dmc['y'] - (m*dmc['x'] + b))*(dmc['y'] - (m*dmc['x'] + b))).sum()
sstot = ((dmc['y'] - mean)*(dmc['y'] - mean)).sum()

r2_mc = 1 - (ssres/sstot)


print("\nRegresión Lineal:")
print(f"pendiente = {m}")
print(f"intercepto = {b}") 
print(f"valor de r^2 = {r2_mc}")


mpl.scatter(dmc['x'],dmc['y'],color='r')
mpl.plot(dmc['x'],(m*dmc['x']+b))
mpl.xlabel("x")
mpl.ylabel("y")
mpl.title("Regresión Lineal")
mpl.show()

#%% Regresión Polinomial 

#usando función de costo

def vector_ajuste_rp( datos_x,datos_y ):
    
    v = []
    
    for i in range(0,6):
        
        v = v + [((datos_y)*(datos_x**i)).sum()]
    
    return np.array(v)


def matriz_ajuste_rp( datos_x ):
    
    matriz = np.empty((0,6))    

    for i in range(0,6):
        
        matriz = np.vstack((matriz,np.array([(datos_x**(0+i)).sum(),(datos_x**(1+i)).sum(),(datos_x**(2+i)).sum(),(datos_x**(3+i)).sum(),(datos_x**(4+i)).sum(),(datos_x**(5+i)).sum()])))

    return matriz

A = matriz_ajuste_rp(df['x'])
x = vector_ajuste_rp(df['x'], df['y'])

b_rp = np.matmul(np.linalg.inv(A),x)

y_vals_rp = np.zeros(len(df['x']))

for i in range(0,len(df['x'])):
            
    y_vals_rp[i] = b_rp[0]*1 + b_rp[1]*(df['x'][i]) + b_rp[2]*((df['x'][i])**2) + b_rp[3]*((df['x'][i])**3) + b_rp[4]*((df['x'][i])**4) + b_rp[5]*((df['x'][i])**5)
    

y_data_rp = pd.DataFrame(data=y_vals_rp,columns=['y'])

mean_rp = (1/len(y_data_rp))*((df['y']).sum())

ssres = ((df['y'] - (y_data_rp['y']))**2).sum()
sstot = ((df['y']-mean_rp)**2).sum()

r2_rp = 1 -(ssres/sstot)

print("\nRegresión Polinomial:")
print(f"coeffs 5to grado = \n b1: {b_rp[0]} \n b2: {b_rp[1]} \n b3: {b_rp[2]} \n b4: {b_rp[3]} \n b5: {b_rp[4]} ") 
print(f"r^2 = {r2_rp}")
print(f"f(0) = {y_vals_rp[0]}") 

mpl.scatter(df['x'],df['y'],color='r')
mpl.plot(df['x'],y_data_rp['y'])
mpl.xlabel("x")
mpl.ylabel("y")
mpl.title("Regresión Polinomial")
mpl.show()


#%% Regresión Polinomial exacta

#usando procedimiento datos inmobiliarios

def matriz_ajuste( datos ):

    matriz = np.empty((0,6))    

    for index in datos.index:
        
        matriz = np.vstack((matriz,np.array([1,datos[index],datos[index]**2,datos[index]**3,datos[index]**4,datos[index]**5])))

    return matriz

y = np.matrix(df['y'].to_numpy(dtype=np.float64))

A = np.matrix(matriz_ajuste(  df['x'] ))
b = np.matmul(np.linalg.inv((np.matmul(np.transpose(A),A))),np.matmul(np.transpose(A),np.transpose(y)))


y_vals = np.zeros(len(df['x']))

for i in range(0,len(df['x'])):
            
    y_vals[i] = b[0]*1 + b[1]*(df['x'][i]) + b[2]*((df['x'][i])**2) + b[3]*((df['x'][i])**3) + b[4]*((df['x'][i])**4) + b[5]*((df['x'][i])**5)
    

y_data = pd.DataFrame(data=y_vals,columns=['y'])

mean = (1/len(y_data))*((df['y']).sum())

ssres = ((df['y'] - (y_data['y']))**2).sum()
sstot = ((df['y']-mean)**2).sum()

r2 = 1 -(ssres/sstot)

print("\nRegresión Polinomial exacta:")
print(f"f(0) = {y_vals[0]}")  
print(f"r^2 = {r2}")
print(f"coeffs 5to grado = \n b1: {b[0][0]} \n b2: {b[1][0]} \n b3: {b[2][0]} \n b4: {b[3][0]} \n b5: {b[4][0]} ")     


mpl.scatter(df['x'],df['y'],color='r')
mpl.plot(df['x'],y_data['y'])
mpl.xlabel("x")
mpl.ylabel("y")
mpl.title("Regresión Polinomial Exacta")
mpl.show()


#%% Ajuste ecuación no lineal

def f(parametros,x):
    return parametros[0]/(((x - parametros[1])**2) + parametros[2])**(parametros[3])

def Lfit(parametros,x,y):
    
    deltaY = f(parametros,x) - y
    return np.dot(deltaY,deltaY)/len(y)

res1 = sp.minimize( fun=Lfit, x0 = np.array([1,0,0,1]),args=(df['x'],df['y']), method='L-BFGS-B',tol=1e-8 )

y1_pred = f(res1.x,df['x'])

print("\nEcuación no lineal:")
print(f"f(0) = {y1_pred[0]}")  
print(f"los coeficientes son: \n a: {res1.x[0]} \n b: {res1.x[1]} \n c: {res1.x[2]} \n gamma: {res1.x[3]}")

mpl.scatter(df['x'],df['y'],color='r')
mpl.plot(df['x'],y1_pred)
mpl.xlabel("x")
mpl.ylabel("y")
mpl.title("Ajuste ecuación no lineal")
mpl.show()


print("\nEntre la regresión polinomica y la exacta la diferencia es de apenas algunos decimales, ambos resultados son muy similares, tanto para el intercepto como para el valor de r2, estas tienen mejor ajuste que la regresión lineal. El intercepto de el ajuste con la ecuación no lineal tiene un valor muy cercano al de la regresión con polinomios.")

