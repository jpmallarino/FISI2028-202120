import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm

D = pd.read_pickle('ex1.gz')

sns.scatterplot(x='x',y='y',data=df)

plt.show()

D
T = D[(df.x >= 0) & (D.x <= 1.5)]
T
X_A= d['x'].values.reshape(-1,1)
Y_A= d['y'].values.reshape(-1,1)
modelo = LinearRegression()
modelo.fit(X_A, Y_A)
print("Inter eje y:", modelo.intercept_)
print("M:", modelo.coef_)
print("R^2:", modelo.score(X_A,Y_A))
def P (x,A,b):
    M, G= A.shape
    X = np.matrix(x).T
    DeltaDE_B = (A * X - b)
    return (DeltaDE_B.T * DeltaDE_B)[0, 0] / M
Optimizar = sp.optimize.minimize(fun=L,x0=np.zeros(Xn.shape[1]), args = (Xn,Yn), tol=1e-10)
print("coeficientes son:",Optimizar['x'])
print("f(0)es:",Optimizar['x'][0])
yb = df["y"]
b = np.linspace(0,4,100)
def variables(a,b,c,d,e,f,x):
    return a*x**5 + b*x**4 + c*x**3 + d*x**2 + e*x + f
prediccion = fb(Optimizar['x'][5],Optimizar['x'][4],Optimizar['x'][3],Optimizar['x'][2],Optimizar['x'][1],Optimizar['x'][0],b)
r2 = 1-np.sum((prediccion-yb)**2)/np.sum((yb-yb.mean())**2)
r2
Y = df.loc[:, ['y']]

Y
X = df.loc[:, ['x']].rename(columns={'x': 'x1'})
X.insert(0, 'x0', 1)
X['x2'] = X['x1']*X['x1']
X['x3'] = X['x2']*X['x1']
X['x4'] = X['x3']*X['x1']
X['x5'] = X['x4']*X['x1']
Xn = X.to_numpy()
Yn = Y.to_numpy()
Rpe= np.linalg.inv(Xn.T @ Xn) @ Xn.T @ Yn
