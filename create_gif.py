import pandas as pd
import matplotlib.pyplot as plt
from PIL import Image
import os
import math

csv_filepath = 'output/positions.csv'  # 必要に応じて変更
output_gif = 'simulation.gif'

N = 10
num = 100  
frames = []

r = 0.5
width = (math.sqrt(3) / 2) * r * N 
height = r * N

df = pd.read_csv(csv_filepath, header=None, names=['x', 'y'])
print(df.head())
if not os.path.exists('frames'):
    os.makedirs('frames')


for step in range(0, len(df), num):
    subset = df.iloc[step:step + num]

    plt.figure(figsize=(6, 6))
    plt.xlim(0, width) 
    plt.ylim(0, height)  
    plt.scatter(subset['x'], subset['y'])
    plt.title(f'Step {step // num}')
    
    frame_filename = f'frames/frame_{step // 100}.png'
    plt.savefig(frame_filename)
    plt.close()

    frames.append(Image.open(frame_filename))

frames[0].save(output_gif, format='GIF', append_images=frames[1:], save_all=True, duration=100, loop=0)

for frame in frames:
    os.remove(frame.filename)

print(f"GIF saved as {output_gif}")
