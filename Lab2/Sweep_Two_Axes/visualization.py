import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

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

def dataToCoordinates(d,v,h):
    x = d * np.cos(v*np.pi/180) * np.cos(h*np.pi/180)
    y = d * np.cos(v*np.pi/180) * np.sin(h*np.pi/180)
    z = d * np.sin(v*np.pi/180)
    return (x,y,z)
    
def plotTwoAxesSweep():
    data = np.genfromtxt("oneAxis6.csv", delimiter = ",")
    data = filterSensorVals(data)
    sensorVals = data[:,0]
    distances = np.vectorize(analogReadToDist)(sensorVals)
    #filterPoints(distances)
    vertAngles = data[:,1]
    horiAngles = data[:,2]
    x,y,z = dataToCoordinates(distances, vertAngles, horiAngles)
    plot3d(x,y,z)
    
def filterSensorVals(data):
    vals = data[:,0]
    newData = []
    for i in range(len(vals)):
        if vals[i] < 150*4:
            newData.append(data[i])
    return np.array(newData)
            
def filterPoints(points):
    for i in range(len(points)):
        if points[i] < 50 or points[i] > 100:
            points[i] = 0
    
def plot3d(xs,ys,zs):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(xs, ys, zs)   
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.show()
                        
if(__name__ == "__main__"):
    plotTwoAxesSweep()
