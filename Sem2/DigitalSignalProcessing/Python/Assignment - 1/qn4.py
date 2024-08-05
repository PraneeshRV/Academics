import numpy as np
import matplotlib.pyplot as plt

# Time vector
t = np.linspace(0, 2*np.pi, 1000)

# Signals
s1 = 3 * np.sin(2*t)
s2 = 3 * np.sin(4*t)
s3 = 3 * np.sin(8*t)
s4 = 3 * np.sin(16*t)
s5 = s1 + s2 + s3 + s4

# Plotting
plt.figure(figsize=(10,6))
plt.plot(t, s1, label='3sin(2t)')
plt.plot(t, s2, label='3sin(4t)')
plt.plot(t, s3, label='3sin(8t)')
plt.plot(t, s4, label='3sin(16t)')
plt.plot(t, s5, label='Sum of signals')
plt.legend()
plt.grid(True)
plt.show()