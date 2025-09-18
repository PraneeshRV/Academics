import numpy as np
import matplotlib.pyplot as plt

fs = 5  # Sampling frequency
ts = np.arange(-10, 10, 1/fs)  # Sampling times
y_sampled = 8 * np.cos(ts**2)
dy_dt_sampled = -16 * ts * np.sin(ts**2)

plt.figure(figsize=(10, 6))
plt.stem(ts, y_sampled, label='y(t)')
plt.stem(ts, dy_dt_sampled, '-.r', label='dy/dt')
plt.legend()
plt.show()