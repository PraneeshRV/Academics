import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(-10, 10, 1000)
y = 8 * np.cos(t**2)
dy_dt = -16 * t * np.sin(t**2)

plt.figure()
plt.plot(t, y, label='y(t)')
plt.plot(t, dy_dt, label='dy/dt')
plt.legend()
plt.show()
