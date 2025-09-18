import numpy as np
import matplotlib.pyplot as plt

fs = 10  # New sampling frequency
ts = np.arange(-10, 10, 1/fs)  # New sampling times
dy_dt_sampled = -16 * ts * np.sin(ts**2)

# 3-bit quantization
dy_dt_quantized_3bit = np.round(dy_dt_sampled * 7) / 7
plt.figure()
plt.stem(ts, dy_dt_quantized_3bit)
plt.title('3-bit quantization')
plt.show()

# 5-bit quantization
dy_dt_quantized_5bit = np.round(dy_dt_sampled * 31) / 31
plt.figure()
plt.stem(ts, dy_dt_quantized_5bit)
plt.title('5-bit quantization')
plt.show()
