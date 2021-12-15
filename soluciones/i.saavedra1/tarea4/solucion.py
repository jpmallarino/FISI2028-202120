#!/usr/bin/env python
# coding: utf-8

# In[111]:


import numpy as np
import pandas as pd
import scipy as sp
import sklearn as sl

import seaborn as sns; sns.set()
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
from scipy import integrate
import math

get_ipython().run_line_magic('matplotlib', 'inline')
#Punto A: integracion usando trapecios
#integral 1
a=0
b=1
x = np.linspace(a,b,1000)
y =  1/(np.sqrt(x[1:]))

print ("x",np.size(x))
print("y",np.size(y))

x=x[1:]

plt.figure()
plt.plot(x,y)
plt.show()

#trapecio
integral =  y[0]*(x[1]-x[0])/2 + np.sum(y[1:-1]*(x[2:]-x[1:-1]))+ y[-1]*(x[-1]-x[-2])/2
print(integral)
print ("La integral calculada: ",integral)


# In[ ]:


#integral 2
a=0
b=1000
x = np.linspace(a,b,1000000)
x=x[1:]

ealaX= np.exp(-x)
logX=np.log(x)
y=ealaX*logX
print ("x",np.size(x))
print("y",np.size(y))



#trapecio
integral =  y[0]*(x[1]-x[0])/2 + np.sum(y[1:-1]*(x[2:]-x[1:-1]))+ y[-1]*(x[-1]-x[-2])/2
print(integral)
print ("La integral calculada: ",integral)


# In[127]:



#integral 3
a=0
b=1000
x = np.linspace(a,b,1000000)
x=x[1:]
Sen= np.sin(x)

y= Sen/x
print(np.size(Sen))
print(np.size(y))


plt.figure()
plt.plot(x,y)
plt.show()



print ("x",np.size(x))
print("y",np.size(y))



#trapecio
integral =  y[0]*(x[1]-x[0])/2 + np.sum(y[1:-1]*(x[2:]-x[1:-1]))+ y[-1]*(x[-1]-x[-2])/2
print(integral)
print ("La integral calculada: ",integral)




# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




