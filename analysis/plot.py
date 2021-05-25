import matplotlib.pyplot as plt
import numpy as np
  
data = np.genfromtxt('analysis/analysis.csv', delimiter=',', names=['type', 'dt', 'N'])

plt.plot(data['N'], data['dt'], color='r', label='the data')


# function to show the plot
plt.savefig('analysis/plot.png')