#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import scipy as sp
import sklearn as sl

import seaborn as sns; sns.set()
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
get_ipython().run_line_magic('matplotlib', 'inline')
from matplotlib import animation, rc
from IPython.display import HTML


# # Tarea 5 y 6: Ecuación de difusión en 3 dimensiones
# 
# Uds se preguntarán, ¿por qué vamos a resolver la ecuación de difusión? La respuesta no es muy obvia, pero es interesante: Los procesos de difusión comparten algo muy bonito con los procesos estocásticos. Para ello, vamos a analizar un problema de COVID: el tiempo medio estimado de infección de los viriones.
# 
# La transmisión de COVID se da preponderamente debido a la aspersión de aerosoles en el aire. Estas partículas *semi*-esféricas -cuyo orden de magnitud es de $\sim1-10\,\mu m$ de radio- están compuestas principalmente por agua, lípidos orgánicos y viriones (se pueden considerar *quasi*-puntuales ya que son del orden de los $\sim100\,nm$). Cuando una particula del aerosol entra y se adhiere al tracto respiratorio, el virus toma un tiempo en entrar en contacto con las células para infectar el huésped debido al movimiento Browniano. Los viriones, a diferencia de las bacterias, no cuentan con cilios, flagelos u otros mecanismos para desplazarse en los medios, por lo cual, su única esperanza es que por fluctuaciones térmicas puedan llegar a la superficie de la gota de aerosol para replicar su ADN al entrar en contacto con los tejidos susceptibles. Este proceso es en esencia estocástico y se puede modelar mediante la ecuación de Difusión. Esta ecuación tiene dos partes. La idea es que uds resuelvan el problema de la manera más sencilla. La ecuación es la siguiente,
# $$
# \frac{\partial\Psi}{\partial t}=D\nabla^2\Psi,
# $$
# donde $D$ es la constante de difusión del medio y $\Psi$ es la concentración de partículas. La taza de difusión depende de la temperatura y la viscosidad del medio y se puede modelar usando la relación de Einstein-Stokes,
# $$
# D=\frac{k_BT}{6\pi\eta a},
# $$
# siendo $k_B$ la constante de Boltzmann, $T$ la temperatura en grados Kelvin, $\eta$ la viscosidad del medio y $a$ el radio de los viriones. En esencia, lo que la ecuación de difusión me está diciendo es que la concentración media de viriones depende de la posición y el tiempo. No obstante, para poder calcular el tiempo que tardaría un virión en alcanzar la superficie se puede modelar en la media usando la siguiente ecuación de difusión,
# $$
# -\nabla^2\tau=\frac{1}{D},
# $$
# donde $\tau$ es el tiempo medio que dependería de la posición en la que se encuentra inicialmente.

# ## 1. Escriba la ecuación de difusión para el tiempo $\tau$ en coordenadas esféricas y asuma que $\tau(r,\theta,\phi)\simeq\tau(r)$ ya que por simetría esférica sólo dependerá de la posición radial respecto al centro de la gotica (Usar **LaTex**)

# Como theta y phi son cero se tiene que:
# 
# ![image-4.png](attachment:image-4.png)
# 
# Ejemplo de una ecuación:
# $$
# f(x)=\frac{1}{x^2}
# $$

# ## 2. Resuelva la ecuación diferencial para el tiempo de forma numérica y grafique
# 
# Asuma las siguientes condiciones iniciales:
# 1. $\tau(R)=0$ ya que si el virión está en la superficie el tiempo debe ser naturalmente nulo.
# 1. $\tau^\prime(r)=0$ ya que por simetría la derivada radial debe ser nula en el origen
# 
# Suponga las siguientes condiciones:
# - $R=5\mu m$ para el radio de la esfera de *quasi* agua (calcula el volumen $V$)
# - $\eta_{\text{H}_2\text{O}}\simeq1\times10^{-3}\,Pa\cdot s$ (Pascales por segundo)
# - $\frac{\eta}{\eta_{\text{H}_2\text{O}}}\approx10^3\to10^5$
# - $a\simeq100\,nm$
# - $V=\frac{4}{3}\pi a^3$
# - $k_BT\simeq4.05\times10^{-21}J$

# In[2]:


eta = 1*10**(-3)*(1*(10**5))
a = 1*10**(-9)
D = (4.05*10**(-21))/(6*np.pi*eta*a)

R = 5*10**(-6)
N = 500
dr = R/N

c0 = 0
cN = 0
r = np.arange(0, R, dr)


# In[3]:


A = np.matrix([np.array([(r[i]-dr if j == i-1 and i > 0 else 0)for j in range(N+1)])for i in range(N+1) ]) 
A = A + np.matrix([np.array([(-2*r[i] if j == i else 0)for j in range(N+1)])for i in range(N+1) ]) 
A = A + np.matrix([np.array([(r[i]+dr if j == i+1 and i < N-1 else 0)for j in range(N+1)])for i in range(N+1) ]) 

A[0,:] = np.zeros(N+1)
A[0,0] = 1
A[0,1] = -1
A[-1, -1] = 1

c = (-r*(dr**2)/D)
c[0] = c0
c[-1] = cN
c = np.matrix(c).T


# In[4]:


Tau = np.array((np.linalg.inv(A)*c).T).flatten()
r1 = np.arange(0,R,R/N)


# In[5]:


plt.plot(r1, Tau, label = "Solución numérica")
plt.xlabel("r (μm)")
plt.ylabel("Tau (s)")
plt.legend()


# ## 3. Si los viriones están distribuidos uniformemente, encuentre el tiempo que tardaría un virión en salir de la gota de aerosol.
# 
# Tenga presente que debe promediar suponiendo que el virión tiene una distribución uniforme, i.e. $\rho\left(\vec{r}\right)=1/V$, usando la siguiente relación,
# $$
# \bar{\tau} = \int_{\mathcal{V}}\tau\left(\vec{r}\right)\rho\left(\vec{r}\right)\,\text{d}\vec{r} = \frac{4\pi}{V}\int_{0}^{R}\tau(r)\,r^2\text{d}r.
# $$
# Realice la integral numéricamente.

# In[6]:


V = (4/3)*np.pi*(R**3)

T = sp.integrate.simpson(4*np.pi*Tau*(r**2)/V, r)

T


# Por lo anterior, se puede ver que el tiempo quet ardaría un virión en salir de la gota de aerosol es de: $775.7 sec$.

# ## 4. Las cadenas de Markov.
# 
# Vamos a resolver el problema anterior usando un proceso de Markov. Suponga que ud **divide** la esfera en cubitos de ancho $\delta x=\delta y=\delta z=\Delta=R/N$ con $N$ un número determinado de particiones. Para nuestro experimento, vamos a suponer que ponemos un virión en una posición inicial $\vec{r}_0=(\Delta\,j, 0, 0)$, determinada por un índice $j\in\{0,1,2,\dots,N\}$. Ud va a actualizar la posición del virión en la malla discreta siguiendo las reglas a continuación:
# - Determine el número de divisiones $N$ y calcule $\Delta$.
# - Ajuste la escala de tiempo $\delta t$ y de tal manera que la probabilidad $\alpha=D\frac{\delta t}{\Delta^2}<\frac{1}{6}$. (Recomiendo $\leq1/12$)
# - Haga una corrida de Markov-Monte Carlo actualizando la posición con la probabilidad de transición $\alpha$ hacia los primeros vecinos cercanos y calcule el número de pasos de tiempo para llegar a la superficie, i.e. $|\vec{r}(t_m)|>R-\Delta$
# - Repita este experimento para la misma posición un gran número de veces para obtener una estadística (media y desviación estándar).
# - Repita todos los pasos para todos los índices $j\in\{0,1,2,\dots,N\}$ y grafique. ¡Compare con los resultados anteriores!

# In[7]:


N = 100
delta = R/N

x = np.arange(0,R,delta)
dt = 1e-4
t = np.arange(0,T,dt)

alpha = D*dt/delta**2

assert alpha < 1/12
print('Resumen:'
     f'\n  alpha = {alpha}'
     f'\n  delta = {delta}'
     f'\n  dt = {dt}')


# In[8]:


def actualiza_objetos(n):
    global alpha
    # esta funcion me dice de n objetos cuantos van a la izquierda y cuantos a la derecha
    v = np.random.uniform(size=n)
    izq = sum(v<alpha)
    der = sum(v<2*alpha) - izq
    return (izq,der)

def actualiza_phi(phi):
    # calcular cuantos se van a la derecha y cuantos a la izquierda
    dphi = np.array([actualiza_objetos(_phi) for _phi in phi]).T
    # verificar cuantos hay.... reajustar cuantos se van: condiciones de frontera
    dphi[0,0] = 0
    dphi[1,-1] = 0
    # sumar los q tenia phi0 + los q llegan - los q se van
    dphi_izq = np.roll(dphi[0],-1)
    dphi_der = np.roll(dphi[1], 1)
    dphi = np.sum(dphi, axis=0)
    return phi-dphi+dphi_izq+dphi_der


# In[17]:


phi = np.zeros(N, dtype=np.uint32)
# condiciones iniciales
phi[0] = N*delta
phi[N//2] = 15

plt.scatter(x, phi)


# In[10]:


phi = np.zeros(N, dtype=np.uint32)
# condiciones iniciales
phi[0] = N*delta
phi[N//-400] = 15

plt.scatter(x, phi)


# In[11]:


phi = np.zeros(N, dtype=np.uint32)
# condiciones iniciales
phi[0] = N*delta
phi[N//400] = 15

plt.scatter(x, phi)


# In[12]:


# First set up the figure, the axis, and the plot element we want to animate
fig, ax = plt.subplots()

ax.set_xlim(( 0, R))
ax.set_ylim((0, max(phi)))
ax.set_ylim(auto=True, ymin=0, ymax=max(phi))

line, = ax.plot([], [], 'o', lw=2)

# initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    return (line,)

# animation function. This is called sequentially
def animate(i):
    global phi
    phi = actualiza_phi(phi)
    line.set_data(x, phi)
    return (line,)

### call the animator. blit=True means only re-draw the parts that have changed.

anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=200, interval=40, blit=True)

# equivalent to rcParams['animation.html'] = 'html5'
rc('animation', html='jshtml')
rc
tohtml = anim.to_jshtml()
plt.clf()

HTML(tohtml)


# ## 5. Diseñe un experimento para calcular el numeral (3) usando Markov-Monte Carlo

# In[ ]:




