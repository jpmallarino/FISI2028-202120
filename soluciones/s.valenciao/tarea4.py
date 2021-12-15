# -*- coding: utf-8 -*-
"""tarea4
"""
import numpy as np
import scipy as sp
import sklearn as sl
import time
from mpl_toolkits.mplot3d import axes3d
from matplotlib import pyplot as plt
from matplotlib import cm
import pandas as pd
import seaborn as sns; sns.set()
import matplotlib as mpl
# Metodo del Trapecio
Inicio_de_tiempo = time.time()
N=100

F_X = np.linspace(0.000001,1,1000001) 
x = np.linspace(0.000001,N,1000001)


def F(x):


    return x**(-1/2)

def G(x):


    return np.exp(-x)*np.log(x)

def N(x):

    return np.sin(x)/x

def integracion(x,f):
    c=0
    for i in range(len(x)-1):
        c = c + (f(x[i+1])+(f(x[i])))*abs(x[i+1]-x[i])/2
    return(c)

    
integral_F = integracion(F_X,f) 

integral_G = integracion(x,G)

integral_N = integracion(x,N)

print(f" integral F es {integral_f}")

print(f" integral G es {integral_G}")

print(f"integral N es {integral_N}")

time.sleep(0)



Tiempo_final = time.time()

print("Tiempo que tarda es : ",Tiempo_final-Inicio_de_tiempo, "segundos")