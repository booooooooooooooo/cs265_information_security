import numpy as np
import matplotlib.pyplot as plt
import math

x = np.arange(0.0, 10000.0, 1)
y = 1.9223 * np.power(x, 1.0/3) * np.power(np.log2(x), 2.0/3)
plt.plot(x, y)
plt.ylabel('number field sieve')
plt.show()
