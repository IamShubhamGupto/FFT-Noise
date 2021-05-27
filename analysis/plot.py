import matplotlib.pyplot as plt
import numpy as np
import os
data = np.genfromtxt('analysis/analysis.csv',
                     delimiter=',', names=['N', 'perlin_noise', 'simplex_noise', 'fft_noise'])

plt.plot(data['N'], data['perlin_noise'], '-p', color='red')
plt.plot(data['N'], data['simplex_noise'], '-p', color='blue')
plt.plot(data['N'], data['fft_noise'], '-p', color='green')
plt.legend()
plt.ylabel("Time (milliseconds)")
plt.xlabel("Resolution (NxN pixels)")


# function to show the plot
if(not os.path.exists("analysis/plots")):
    os.system("mkdir analysis/plots")
plt.savefig('analysis/plots/plot.png')
