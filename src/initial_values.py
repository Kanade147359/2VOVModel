import numpy as np

def generate_initial_positions(row_size, num, r):
    positions = np.zeros((num, 2))  # num x 2 の配列を作成
    k = 0
    
    for i in range(row_size):
        for j in range(row_size):  # col_size = row_size と仮定
            if i % 2 == 0:
                positions[k, 0] = np.sqrt(3) * r / 2 * i + r / 2
                positions[k, 1] = r * j + r / 2
            else:
                positions[k, 0] = np.sqrt(3) * r / 2 * i + r / 2
                positions[k, 1] = r * j + r / 2 + r / 2
            k += 1
            
    return positions

def generate_initial_velocities(num):
    # num x 2 の配列を生成
    velocities = np.zeros((num, 2))
    
    # 各エージェントの速度を初期化
    velocities[:, 0] = 1.0  # X方向
    velocities[:, 1] = 0.0  # Y方向
    
    return velocities

