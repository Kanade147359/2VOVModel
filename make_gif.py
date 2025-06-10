import csv
from PIL import Image, ImageDraw

CSV_FILE = 'positions.csv'
OUTPUT_GIF = 'animation.gif'
FRAME_SIZE = (800, 400)
BACKGROUND_COLOR = (255, 255, 255)
PARTICLE_COLOR = (0, 0, 0)
PARTICLE_RADIUS = 3
DURATION = 100

frames = []
with open(CSV_FILE, newline='') as f:
    reader = csv.reader(f)
    header = next(reader)
    N = (len(header) - 1) // 2

    for row in reader:
        image = Image.new("RGB", FRAME_SIZE, BACKGROUND_COLOR)
        draw = ImageDraw.Draw(image)
        for i in range(N):
            x = float(row[1 + 2 * i])
            y = float(row[2 + 2 * i])
            px = int(x * 20 + 50)   # スケーリングとオフセット調整
            py = int(y * 20 + 50)
            draw.ellipse((px - PARTICLE_RADIUS, py - PARTICLE_RADIUS,
                          px + PARTICLE_RADIUS, py + PARTICLE_RADIUS),
                         fill=PARTICLE_COLOR)
        frames.append(image)

frames[0].save(OUTPUT_GIF, save_all=True, append_images=frames[1:], duration=DURATION, loop=0)
print("GIF animation created successfully as 'animation.gif'.")
