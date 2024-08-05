import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(-15, 15, 1000)
t[t == 0] = 1e-20  # Avoid division by zero
y = np.sin(3*t) / (3*t)

plt.figure()
plt.plot(t, y)
plt.show()
