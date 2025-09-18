import matplotlib.pyplot as plt
import numpy as np
from scipy.io.wavfile import read, write

# Read the audio file
sampling_rate, data = read('rishabop.wav')

# a. Plot the recorded output
plt.figure(figsize=(10, 4))
plt.plot(data)
plt.title('Original Signal')
plt.xlabel('n (samples)')
plt.ylabel('y[n]')
plt.grid(True)
plt.show()

# b. Check the sampling rate
print(f"Sampling Rate: {sampling_rate} Hz")

# c. Reconstruct the signal with 50% of whatever the sampling rate is and 4-bit quantization.
new_sampling_rate = int(sampling_rate * 0.5)
quantized_levels = 16  # For 4-bit quantization

# Downsample the data
downsampled_data = data[::2]

# Quantize the downsampled data to 4 bits
quantized_data = np.round(downsampled_data * quantized_levels / np.max(np.abs(downsampled_data)))

# Plot reconstructed signal
plt.figure(figsize=(10, 4))
plt.plot(quantized_data)
plt.title('Reconstructed Signal with Lower Sampling Rate and Quantization')
plt.xlabel('n (samples)')
plt.ylabel('y[n]')
plt.grid(True)
plt.show()
