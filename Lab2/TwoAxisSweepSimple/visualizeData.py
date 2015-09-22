from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np

def analogReadToDist(a):
    return voltageToDist(analogReadToVoltage(a))

def voltageToDist(v):
    return (np.log(v) - np.log(4.2223)) / -0.024
    
def analogReadToVoltage(a):
    return a * 1.0 / 1023 * 5 
    
def polarToCoordinate(a, d):
    x = d * np.cos(a*np.pi/180)
    y = d * np.sin(a*np.pi/180)
    return (x,y)

def getArrayFromFile(path):
    return np.loadtxt(path, delimiter=',')
    
def convertToXYZ(v,h,r):
    x = r*np.cos(v*np.pi/180)*np.cos(h*np.pi/180)
    y = r*np.cos(v*np.pi/180)*np.sin(h*np.pi/180)
    z = r*np.sin(v)
    return (x,y,z) 
           
def plotScannerData(xs,ys,zs):
    print ("Plotting now")
    X, Y = np.meshgrid(xs,ys)
    Z = zs
    hf = plt.figure()
    ha = hf.add_subplot(111, projection='3d')
    ha.plot_surface(X,Y,Z, cmap=cm.coolwarm, cstride=2)
    ha.set_zlabel('distance from scanner (cm)')
    plt.show()

if __name__ == '__main__':
    print ("Starting here")
    analogReadVals = getArrayFromFile('data_09222015.csv')
    vertAngles = analogReadVals[:,0]
    horzAngles = analogReadVals[:,1]
    radiis = np.vectorize(analogReadToDist)(analogReadVals[:,2])
    xs,ys,zs = convertToXYZ(vertAngles, horzAngles, radiis)
    print ("About to plot")
    plotScannerData(xs,ys,zs)
