from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np

def analogReadToDist(a):
    return voltageToDist(analogReadToVoltage(a))

def voltageToDist(v):
    if(v == 0):
        # v cannot be 0 (the equation below won't work - so setting it to a 
        # large value that won't affect the visualization)
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

def plotHeatMap(x,y,z):
    hf = plt.figure()
    z_min, z_max = -np.abs(z).max(), np.abs(z).max()
    plt.pcolor(x, y, z, cmap='bone', vmin=0, vmax=z_max - 120)
    plt.title('3D Letter Heatmap')
    plt.xlabel("Horizontal Distance From Sensor (cm)")
    plt.ylabel("Vertical Distance From Sensor (cm)")
    
    # Set the limits of the plot to the limits of the data
    plt.axis([x.min(), 20, y.min(), 40])
    plt.colorbar()
    plt.show()

if __name__ == '__main__':
    data = getArrayFromFile('data_09222015.csv')
    
    # Take the vertical and horizontal angles (from the data) and map it to the
    #  first quadrant (so that the minimum angle is 0).
    # Add a constant the the V and H to account for discrepancies in plane alignments
    
    V = np.reshape(data[:,0] - min(data[:,0]) - 20, (60, -1))
    H = np.reshape(data[:,1] - min(data[:,1]) + 50, (60, -1))
    analogReadVals = np.reshape(data[:,2], (60, -1))
    
    # Calculate the distance read (the radius) and convert that and the angles
    #  to Cartesian
    R = np.vectorize(analogReadToDist)(analogReadVals)     
    X, Y, Z = convertToXYZ(V,H,R)
    
    # Plot heatmap of front face (2D shape with color to represent depth)
    plotHeatMap(X,Z,Y)
