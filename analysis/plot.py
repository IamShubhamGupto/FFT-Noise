import matplotlib.pyplot as plt
import numpy as np
import os
data = np.genfromtxt('analysis/analysis.csv',
                     delimiter=',', names=['type', 'dt', 'N'])

plt.plot(data['N'], data['dt'], '-p', color='red')
plt.legend(["Fractal Noise"])
plt.ylabel("Time (milliseconds)")
plt.xlabel("Image resolution (NxN pixels)")

# function to show the plot
if(not os.path.exists("analysis/plots")):
    os.system("mkdir analysis/plots")
plt.savefig('analysis/plots/plot.png')
