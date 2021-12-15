import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy as sp
import sklearn as sl

import seaborn as sns; sns.set()
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy as sp
import sklearn as sl

import seaborn as sns; sns.set()
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
import matplotlib.pyplot as plt

## primer punto codigo en latex por bloque neon adjunto foto del resultado de la ecuacion graficada

## \bigtriangledown ^2\tau =\frac{1}{r^2}*\frac{\partial }{\partial r}(r^2\frac{\partial \tau }{\partial r})
## \frac{1}{r^2}\frac{\partial }{\partial r}(r^2\frac{\partial \tau }{\partial r})=-\frac{6\eta \pi a}{\kappa_bt}
## \frac{1}{r^2}[(2r\frac{\partial \tau }{\partial r}+r^2\frac{\partial ^2\tau }{\partial r^2})]=\frac{6\pi \eta a}{\kappa _bt}
## \frac{\partial ^2\tau }{\partial r^2}+\frac{2\partial \tau }{r\partial r}=-\frac{6\pi \eta a}{\kappa _bt}
## \frac{\partial ^2\tau }{\partial r^2}+\frac{2\partial \tau }{r\partial r}+\frac{6\pi \eta a}{\kappa _bt}=0

## punto dos
m=300
R=5*10**(-6)
DR=R/m
r=np.arange(0,R,DR)
coeficiente=((4.05*10**(-21)))/(6*np.pi*10**(2)*(100*10**(-9)))
T_O=0
T_N=0
N=np.matrix([np.array([(r[i]-DR if j == i-1 and i>0 else 0)for j in range(m)])for i in range(m)])
N= N+ np.matrix([np.array([(-2*r[i]if j == i else 0)for j in range(m)])for i in range(m)])
N= N + np.matrix([np.array([(r[i]+DR if j == i+1 and i <m-1 else 0)for j in range(m)])for i in range(m)])
N[0,:]=np.zeros(m)
N[0,0]=1
N[0,1]= -1
N[-1,:]=np.zeros(m)
N[-1,-1]=1
x=(-r*(DR**2)/coeficiente)
x[0]=T_O
x[-1]=T_N
x= np.matrix(x).T

THAO=np.array((np.linalg.inv(N)*x).T).flatten()
r_t = np.arange(0,5,5/m)

plt.plot(r_t,THAO)
plt.plot(r_t,(R**2/(6*coeficiente))-(1/6*coeficiente)*r**2)
plt.legend()
plt.xlabel("r")
plt.ylabel("t")
plt.show
## PUNTO 3
R = 5*10**(-6)
R_i=0.000001
R_f=R
N=1000001
vol=(4/3)*np.pi*(100*10**(-9))**3
def tiempo(r):
  return ((4*np.pi)/vol)*((R**2/(6*coeficiente))-(1/(6*coeficiente)*r**2))*(r*2)
def integral_por_el_metodo_simpson(empieza,termina,N,tiempo):
  x_1, D_x = np.linspace(empieza, termina, num=N-1, retstep=True)
  return (D_x/3)*(tiempo(x_1[0])+2*np.sum(tiempo(x_1[2:len(x_1)-1:2]))+4*np.sum(tiempo(x_1[1::2]))+tiempo(x_1[-1]))
tiempo_promedio= integral_por_el_metodo_simpson(R_i,R_f,N,tiempo)
print(f"tiempo promedio es {tiempo_promedio}")



