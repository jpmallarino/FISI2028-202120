# -*- coding: utf-8 -*-
"""
Created on Tue Dec  7 15:02:00 2021

@author: danie
"""

from IPython.display import display,Math
import numpy as np
import matplotlib.pyplot as plt

print("Ecuación diferencial:\n")
display(Math(r'-\frac{\partial^2 \tau}{\partial r^2} - \frac{2}{r}\frac{\partial \tau}{\partial r} = \frac{6 \pi \eta a}{k_{b} T}'))



""""""

R = 5*(10**(-6))
nH2O = 10**(-3)
n = (10**3)*nH2O
a = 100*(10**(-9))
V = (4/3)*np.pi*(R**3)
kbT = 4.05*(10**(-21))

D = kbT/(6*np.pi*n*a)

def tau(r):
    return -((r**2)/(6*D)) + ((R**2)/(6*D))

""""""

N = 50

dr = R/N

def r(i):
    return (i*R)/N


"""" Matriz A """
A = np.zeros((N+1,N+1))

""" Primera fila """

A[0][0] = -2
A[0][1] = 2

""" Penultima fila """

A[N-1][N-1] = -2*r(N-1)
A[N-1][N-2] = (r(N-1) - dr)

""" Utlima fila """
A[N][N] = 1

""" Llenando las otras filas """

for i in range(1,N-1):

    A[i][i-1] = r(i) - dr
    A[i][i] = -2*r(i)
    A[i][i+1] = r(i) + dr


""" Vector b """
b = np.zeros((N+1,1))

for i in range(0,N):
    b[i] = -((r(i)*(dr**2))/D)

b[0] = -(dr**2)/D
b[N] = 0

tau_num = np.matmul(np.linalg.inv(A),b)
r_num = [ n*dr for n in range(0,N+1)]

tau_ecuacion = [tau(r_i) for r_i in r_num]
r_plot = [r_i*(10**6) for r_i in r_num]

plt.title(r"${\tau}$ vs r")
plt.xlabel(r"Radio ( $\mu$m )")
plt.ylabel(r" $\tau$ ( s )")
plt.plot(r_plot,tau_ecuacion,color='r',label='Ecuación')
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='x', alpha=0.7)
plt.xlim([0,r_plot[len(r_plot)-1]])
plt.scatter(r_plot,tau_num,label='Numerico')
plt.legend()
plt.show()



""" Integral """

""" Se usa la regla de simpson """
def simpson( h, f1, f2, f3 ):
    return (h/3)*f1 + (4/3)*h*f2 + (h/3)*f3
    

tau_rr = [((tau_num[i][0])*(r(i)**2)) for i in range(0,N+1)]

sol_num = 0

for i in range(0,N-1,2):
    sol_num += simpson(dr, tau_rr[i], tau_rr[i+1], tau_rr[i+2])
    
sol_num = ((4*np.pi)/V)*sol_num

sol_ecuacion = ((R**5)/(45*D))*((4*np.pi)/V)

print(f"\nSolución numerica: {sol_num}\nSolución analitica: {sol_ecuacion}")
print(f"Diferencia: {sol_ecuacion - sol_num}")



""" Cadenas de Markov """

"""El espacio R ya está discretizado en el vector r_num"""

N_markov = 30

delta = R/N_markov

j = [ i*delta for i in range(0,N_markov) ]


""" Ajustamos la escala de tiempo de tal manera que alfa = (1/12) """
alpha = (1/12)
dt = ((delta**2)*alpha)/D


""" Arreglo con numero de viriones para cada posición discretizada """
n_viriones = [0 for i in j]


""" Colocando viriones en una posición """
n_viriones[0] = 1


plt.title("Cantidad y posicion inicial de viriones")
plt.xlabel(r"Radio ( m )")
plt.ylabel(r"Numero de viriones")
plt.scatter(j,n_viriones)
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='x', alpha=0.7)
plt.xlim([0,j[len(j)-1]])
plt.show()


""" Funciones para actualizar """

def numero_viriones_moviendose( viriones_actuales, alpha ):
    
    probabilidad = np.random.uniform( size= int(viriones_actuales) )
    
    moverse_izquierda = 0
    moverse_derecha = 0
    
    for i in range(0,len(probabilidad)):
        
        if probabilidad[i] < alpha:
            moverse_izquierda += 1
        
        if probabilidad[i] < 2*alpha:
            moverse_derecha += 1
    
    moverse_derecha = moverse_derecha - moverse_izquierda

    return moverse_izquierda,moverse_derecha


def mover_viriones( n_viriones, alpha ):

    mover_izquierda = np.zeros((N_markov,1))
    mover_derecha = np.zeros((N_markov,1))

    for i in range(0,N_markov):
        mover_izquierda[i],mover_derecha[i] = numero_viriones_moviendose(n_viriones[i], alpha)
    
    saliendo_izquierda = np.copy(mover_izquierda)
    saliendo_derecha = np.copy(mover_derecha)
    
    mover_izquierda = np.roll(mover_izquierda,-1)
    mover_izquierda[len(mover_izquierda)-1] = 0
    
    mover_derecha = np.roll(mover_derecha,1)
    mover_derecha[0] = 0


    for i in range(0,(N_markov)):
        
        if i == 0:
            n_viriones[i] = n_viriones[i] + mover_izquierda[i] - saliendo_derecha[i]
            
        elif( i>0 or i<N_markov ):
            n_viriones[i] = n_viriones[i] + mover_izquierda[i] + mover_derecha[i] - saliendo_derecha[i] - saliendo_izquierda[i]
        
        else:
            n_viriones[i] = n_viriones[i] + mover_derecha[i] - saliendo_izquierda[i] - saliendo_derecha[i]
        


def experimento( repeticiones, pos_inicial, alpha ):

    n_steps_promedio = 0
    
    for i in range(0,repeticiones):
       
       n_steps_local = 0
       
       n_viriones = [0 for i in j]
       n_viriones[pos_inicial] = 1
       
       while( sum(n_viriones) != 0 ):
           
           mover_viriones(n_viriones, alpha)
           n_steps_local += 1
           
           #plt.title("Cantidad y posicion de viriones")
           #plt.xlabel(r"Radio ( m )")
           #plt.ylabel(r"Numero de viriones")
           #plt.scatter(j,n_viriones)
           #plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='y', alpha=0.7)
           #plt.grid(color='#95a5a6', linestyle='--', linewidth=1, axis='x', alpha=0.7)
           #plt.xlim([0,j[len(j)-1]])
           #plt.show()
            
       n_steps_promedio += n_steps_local


    return n_steps_promedio/repeticiones


n_repeticiones = 10

datos_tiempo = [ dt*experimento(n_repeticiones,0,alpha) for i in range(0,n_repeticiones) ]

media = sum(datos_tiempo)/n_repeticiones

desviacion = 0

for i in datos_tiempo:
    
    desviacion += ((i - media)**2)

desviacion = (desviacion/n_repeticiones)**(1/2)

print(f"Media: {media}\nDesviación estandar: {desviacion}")



for i in j:
    
    n_repeticiones = 10

    datos_tiempo = [ dt*experimento(n_repeticiones,i,alpha) for i in range(0,n_repeticiones) ]

    media = sum(datos_tiempo)/n_repeticiones

    desviacion = 0

    for i in datos_tiempo:
        
        desviacion += ((i - media)**2)

    desviacion = (desviacion/n_repeticiones)**(1/2)

    print(f"Media: {media}\nDesviación estandar: {desviacion}")
        