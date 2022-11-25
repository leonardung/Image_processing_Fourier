import numpy as np
import matplotlib.pyplot as plt
import sys


img_values = np.loadtxt("../histogram.txt", delimiter=",", dtype=str)
img_values = img_values[:-1].astype(int)

title = str(sys.argv[1])


plt.hist(range(len(img_values)), weights=img_values, bins = 100)

plt.title(title)
plt.show()
