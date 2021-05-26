import matplotlib.pyplot as plt
import numpy as np
import os
from matplotlib.ticker import FormatStrFormatter

data = np.genfromtxt('analysis/analysis.csv',
                     delimiter=',', names=['type', 'dt', 'N'])

plt.plot(data['N'], data['dt'], '-p', color='red')

plt.legend(["FFT Noise"], loc="best")
plt.ylabel("Time (milliseconds)")
plt.xlabel("Resolution (NxN pixels)")
plt.xscale("log", base=2)



# function to show the plot
if(not os.path.exists("analysis/plots")):
    os.system("mkdir analysis/plots")
plt.savefig('analysis/plots/plot.png')
