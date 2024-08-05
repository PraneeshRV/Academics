import numpy as np

fs = 10
ts = np.arange(-10, 10, 1/fs)
dy_dt_sampled = -16 * ts * np.sin(ts**2)

# 3-bit quantization
dy_dt_quantized_3bit = np.round(dy_dt_sampled * 7) / 7

# 5-bit quantization
dy_dt_quantized_5bit = np.round(dy_dt_sampled * 31) / 31

rmse_3bit = np.sqrt(np.mean((dy_dt_sampled - dy_dt_quantized_3bit)**2))
rmse_5bit = np.sqrt(np.mean((dy_dt_sampled - dy_dt_quantized_5bit)**2))

print(f'RMSE for 3-bit quantization: {rmse_3bit}')
print(f'RMSE for 5-bit quantization: {rmse_5bit}')
