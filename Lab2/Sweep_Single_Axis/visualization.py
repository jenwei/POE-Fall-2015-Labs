import numpy as np
import matplotlib.pyplot as plt
import os

#f = "C:/Users/jwei/Documents/Fall-2015/POE/POE-Fall2015/Lab2/Sweep_Single_Axis/simpleSweepData.txt"
#f= "jwei"
#f = open("singleSweepData.txt")
#print f
print np.genfromtxt("singleSweepData.txt")
# TODO: parse the text file manually :(

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
    
testData = np.array([[267,0],
                     [415,4],
                     [672,64],
                     [303,90]])
                     
sensorVals = testData[:,0]
distances = np.vectorize(analogReadToDist)(sensorVals)
angles = np.vectorize(lambda x : x + 45)(testData[:,1])
cartesian = polarToCoordinate(angles, distances)
print cartesian

plt.plot(cartesian[0], cartesian[1])
plt.xlim([0, 100])
plt.ylim([0, 100])
plt.show()




