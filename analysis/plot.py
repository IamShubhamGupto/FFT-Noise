import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt('analysis/analysis.csv',
                     delimiter=',', names=['type', 'dt', 'N'])

plt.plot(data['N'], data['dt'], '-p', color='red')
plt.legend(["Fractal Noise"])
plt.ylabel("Time (seconds)")
plt.xlabel("Image resolution (NxN pixels)")

# function to show the plot
plt.savefig('analysis/plot.png')
