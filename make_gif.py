import csv
from PIL import Image ImageDraw

# --- 設定 ---
CSV_FILE = 'positions.csv'
OUTPUT_GIF = 'animation.gif'
FRAME_SIZE = (800, 400)    # 描画領域のサイズ (幅, 高さ)
BACKGROUND_COLOR = (255, 255, 255)
PARTICLE_COLOR = (0, 0, 0)
PARTICLE_RADIUS = 3
DURATION = 100    

steps = []
with open(CSV_FILE, newline='') as f:
	reader = csv.reader(f)
	header = next(reader)
	N = (len(header) - 1) // 2
	for row in reader:
		coords = list(map(float))
	

print("GIF animation created successfully as 'animation.gif'.")