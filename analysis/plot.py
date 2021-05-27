import matplotlib.pyplot as plt
import numpy as np
import os
data = np.genfromtxt('analysis/analysis.csv',
                     delimiter=',', names=['N', 'pNoise', 'sNoise', 'fftNoise'])

plt1 = plt.plot(data['N'], data['pNoise'], '-p',
                color='red', label="Perlin Noise")
plt2 = plt.plot(data['N'], data['sNoise'], '-p',
                color='blue', label="Simplex Noise")
plt3 = plt.plot(data['N'], data['fftNoise'], '-p',
                color='green', label="FFT Noise")

plt.legend()

plt.ylabel("Time (seconds)")
plt.xlabel("Resolution (NxN pixels)")

plt.xscale("log", base=2)


# function to show the plot
if(not os.path.exists("analysis/plots")):
    os.system("mkdir analysis/plots")
plt.savefig('analysis/plots/plot.png')
