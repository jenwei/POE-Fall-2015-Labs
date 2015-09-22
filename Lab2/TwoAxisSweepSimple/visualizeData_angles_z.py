from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np

def analogReadToDist(a):
    return voltageToDist(analogReadToVoltage(a))

def voltageToDist(v):
    if(v == 0):
        return 200
    return (np.log(v) - np.log(4.2223)) / -0.024
    
def analogReadToVoltage(a):
    return a * 1.0 / 1023 * 5 
    
def polarToCoordinate(a, d):
    x = d * np.cos(a*np.pi/180)
    y = d * np.sin(a*np.pi/180)
    return (x,y)

def getArrayFromFile(path):
    return np.loadtxt(path, delimiter=',')

def plotScannerData(x,y,z):
    width, height = np.shape(data)
    X = np.arange(0,height,1)
    Y = np.arange(0,width,1)
    X, Y = np.meshgrid(X,Y)
    Z = data
    hf = plt.figure()
    ha = hf.add_subplot(111, projection='3d')
    ha.plot_surface(x,y,z, cmap=cm.coolwarm, cstride=2)
    ha.set_zlabel('distance from scanner (cm)')
    plt.show()

if __name__ == '__main__':
    data = getArrayFromFile('data_09222015.csv')
    X = np.reshape(data[:,0], (60, -1))
    Y = np.reshape(data[:,1], (60, -1))
    analogReadVals = np.reshape(data[:,2], (60, -1))
    Z = np.vectorize(analogReadToDist)(analogReadVals)     
    plotScannerData(X,Y,Z)
