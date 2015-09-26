import numpy as np
import matplotlib.pyplot as plt

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

def plotSingleSweep():
    data = np.loadtxt("sweepdata.csv", delimiter=',')
    #data = np.genfromtxt("sweepdata.csv", delimiter = ",")
    sensorVals = data[:,1]
    distances = np.vectorize(analogReadToDist)(sensorVals)
    angles = data[:,0] -80
    x,y = polarToCoordinate(angles, distances)
    plt.plot(x,y)
    plt.xlabel('X (cm)')
    plt.ylabel('Y (cm)')
    plt.title('3D Scanner Single Axis Visualization')
    plt.show()
                     
if(__name__ == "__main__"):
    plotSingleSweep()
