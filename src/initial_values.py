import numpy as np

def generate_initial_positions(row_size, num, r):
    """
    初期位置を生成します。

    Parameters:
        row_size: 行のサイズ（未使用）
        num: 粒子数（未使用）
        r: 半径（未使用）

    Returns:
        positions: 初期位置を格納した (2, 2) 配列
    """
    positions = np.zeros((2, 2))  # 2 x 2 の配列を生成
    positions[0, 0] = 1.0
    positions[0, 1] = 2.5
    positions[1, 0] = 4.0
    positions[1, 1] = 2.5
    return positions

def generate_initial_velocities(num):
    """
    初期速度を生成します。

    Parameters:
        num: 粒子数（未使用）

    Returns:
        velocities: 初期速度を格納した (2, 2) 配列
    """
    velocities = np.zeros((2, 2))  # 2 x 2 の配列を生成
    velocities[0, 0] = 1.0
    velocities[0, 1] = 0.0
    velocities[1, 0] = 0.0
    velocities[1, 1] = 0.0
    return velocities

