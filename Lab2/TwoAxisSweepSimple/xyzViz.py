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

def convertToXYZ(v,h,r):
    x = r*np.cos(v*np.pi/180)*np.cos(h*np.pi/180)
    y = r*np.cos(v*np.pi/180)*np.sin(h*np.pi/180)
    z = r*np.sin(v*np.pi/180)
    return (x,y,z) 

def plotScannerData(x,y,z):
    hf = plt.figure()
    ha = hf.add_subplot(111, projection='3d')
    ha.plot_wireframe(x,y,z, cmap=cm.coolwarm, cstride=5)
    ha.set_xlabel('x (cm)')
    ha.set_ylabel('y (cm)')
    ha.set_zlabel('z (cm)')
    ha.set_xlim3d(0, 50)
    ha.set_ylim3d(0, 50)
    ha.set_zlim3d(0, 100)
    plt.show()

def scrubData(data, cutoff):
    scrubbed = np.zeros(data.shape)
    for i, val in enumerate(data):
        if(val < cutoff):
            scrubbed[i] = data[i]
    return scrubbed

if __name__ == '__main__':
    data = getArrayFromFile('data_09222015.csv')
    V = np.reshape(data[:,0] - min(data[:,0]), (60, -1))
    H = np.reshape(data[:,1] - min(data[:,1]), (60, -1))
    #cleanedData = scrubData(data[:,2])
    analogReadVals = np.reshape(data[:,2], (60, -1))
    R = np.vectorize(analogReadToDist)(analogReadVals)     
    X, Y, Z = convertToXYZ(V,H,R)
    plotScannerData(X,Y,Z)
