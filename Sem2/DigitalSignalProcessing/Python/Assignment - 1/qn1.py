import cmath
import math

# Given complex number Z
Z = cmath.exp(complex(5, 10)) * (cmath.cos(0.25*math.pi) + complex(0,1)*cmath.sin(math.pi/3))

# Compute magnitude and angle
magnitude = abs(Z)
angle = cmath.phase(Z)

print("Magnitude: ", magnitude)
print("Angle in radians: ", angle)
