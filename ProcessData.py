import numpy as np
import matplotlib.pyplot as plt

#############################################################################
######################## EXTRACT ARRAY FROM DATA.TXT ########################
#############################################################################

# Note: Data must be pasted into a file named DATA.TXT with header removed.
#       DATA.TXT must be in the same folder with this program.

data = np.genfromtxt("DATA (4).TXT", delimiter=',')
Tsec = data[:,0]
Roll = data[:,1]
Ptch = data[:,2]
Head = data[:,3]
Zagl = data[:,4]
Vair = data[:,5]
AccX = data[:,6]
AccY = data[:,7]
AccZ = data[:,8]
Svo1 = data[:,9]
Svo2 = data[:,10]
Svo3 = data[:,11]
Svo4 = data[:,12]
Svo5 = data[:,13]
Svo6 = data[:,14]
Vbat = data[:,15]

pulse = ((1000/255)*Svo5)+1000

#############################################################################
############################### PLOT ALL DATA ###############################
#############################################################################

figure, axes = plt.subplots(1, 1)

#Atitude Plot
axes.set_title("Pulse Duration vs. Time")
axes.set_ylabel("Pulse Duration [mili-sec]")
axes.set_xlabel("Time [sec]")
axes.plot(Tsec, Svo5, color="blue")
axes.grid()


fig, ax1 = plt.subplots(1,1)
ax1.set_title("Yaw Angle vs. Time")
ax1.set_ylabel("Yaw Angle [deg]")
ax1.set_xlabel("Time [sec]")
ax1.plot(Tsec, Head, color="red")
plt.grid()
plt.show()