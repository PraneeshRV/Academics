import math
import matplotlib.pyplot as plt
import numpy as np

# Declaring the magnitudes and angles of black and blue vectors
black_magnitude = 10
black_angle = 0  # in radians
blue_magnitude = 20
blue_angle = math.pi/4  # in radians

# Convert polar to rectangular coordinates
black_rectangular = black_magnitude * np.exp(1j * black_angle)
blue_rectangular = blue_magnitude * np.exp(1j * blue_angle)

# Compute the red vector
red_rectangular = black_rectangular + blue_rectangular
red_magnitude = np.abs(red_rectangular)
red_angle = np.angle(red_rectangular)

# Plot the vectors
plt.figure()
ax = plt.subplot(111, projection='polar')
ax.quiver([0, 0, 0], [0, 0, 0], [black_angle, blue_angle, red_angle], [black_magnitude, blue_magnitude, red_magnitude], color=['black', 'blue', 'red'], angles='xy', scale_units='xy', scale=1)
ax.set_rmax(1.2 * red_magnitude)
ax.grid(True)
plt.show()
