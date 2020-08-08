import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


val = np.loadtxt("D:\IISC\heat_conduction_unsteady/input.txt")
df5 = np.loadtxt("D:\IISC\heat_conduction_unsteady/T5.dat")
df20 = np.loadtxt("D:\IISC\heat_conduction_unsteady/T20.dat")
df50 = np.loadtxt("D:\IISC\heat_conduction_unsteady/T50.dat")
df7200 = np.loadtxt("D:\IISC\heat_conduction_unsteady/T7200.dat")
m = int (val[0])
n=0
T5 = np.zeros((m+1,m+1))
T20 = np.zeros((m+1,m+1))
T50 = np.zeros((m+1,m+1))
T7200 = np.zeros((m+1,m+1))
for i in range(m+1):
    for j in range(m+1):
        T5[i][j] = df5[n]
        T20[i][j] = df20[n]
        T50[i][j] = df50[n]
        T7200[i][j] = df7200[n]
        n = n+1


x_ax=np.linspace(0,1,m+1)
y_ax=np.linspace(0,1,m+1)
x,y = np.meshgrid(x_ax,y_ax)
t5 = plt.contourf(x,y,T5,levels = np.linspace(20,40,501),cmap= 'jet' )
cbar = plt.colorbar(t5)
plt.clim(20,40)
plt.title("T = 5s")
plt.show()
t20 = plt.contourf(x,y,T20,levels = np.linspace(20,40,501),cmap= 'jet' )
cbar = plt.colorbar(t20)
plt.clim(20,40)
plt.title("T = 20s")
plt.show()
t50 = plt.contourf(x,y,T50,levels = np.linspace(20,40,501),cmap= 'jet' )
cbar = plt.colorbar(t50)
plt.clim(20,40)
plt.title("T = 50s")
plt.show()
t7200 = plt.contourf(x,y,T7200,levels = np.linspace(20,40,501),cmap= 'jet' )
cbar = plt.colorbar(t7200)
plt.clim(20,40)
plt.title("T = 7200s")
plt.show()