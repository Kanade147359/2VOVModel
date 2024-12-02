def run_simulation(positions, velocities, steps, num, dt, a, b, c, width, height, filepath):
    """
    Simulates the system for a given number of steps and writes the positions to a CSV file every 20 steps.
    """
    # ファイルをオープン
    try:
        with open(filepath, mode='w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            
            for i in range(steps):
                # 更新関数を呼び出し
                update(positions, velocities, dt, a, b, c, num, width, height)
                
                # 20ステップごとにデータを書き込む
                if i % 20 == 0:
                    for j in range(num):
                        writer.writerow(positions[j])  # positions[j]は[x, y]を表す行
    except IOError as e:
        print(f"Error opening file: {filepath}, {e}")