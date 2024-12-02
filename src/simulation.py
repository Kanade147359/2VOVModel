import numpy as np
import csv

def V(r, b, c):
    """
    V関数: 距離に基づく力を計算します。

    Parameters:
        r: 距離
        b: パラメータ
        c: パラメータ

    Returns:
        力の値
    """
    return 0.25 * (np.tanh(2.5 * (r - b)) + c)


def calculate_acceleration(velocity, distances, a, b, c):
    """
    加速度を計算する。

    Parameters:
        position: 対象粒子の位置 [x, y]
        velocity: 対象粒子の速度 [vx, vy]
        neighbors: 近隣粒子の位置を格納した配列 (6, 2)
        distances: 近隣粒子との距離情報を格納した配列 (6, 3) [dx, dy, distance]
        a: 加速度に関するパラメータ
        b, c: 力の計算に使用するパラメータ

    Returns:
        ax, ay: x, y方向の加速度
    """
    F_sum_x = 0.0
    F_sum_y = 0.0

    for i in range(6):  # 6個の近隣粒子を処理
        dx, dy, distance = distances[i]

        # 単位ベクトル emn
        emn_x = dx / distance
        emn_y = dy / distance

        # cos_phi の計算
        cos_phi = dx / distance

        # 力を計算
        force = V(distance, b, c) * (1 + cos_phi)
        F_sum_x += force * emn_x
        F_sum_y += force * emn_y

    # 加速度を計算
    ax = a * ((1.0 + F_sum_x) - velocity[0])
    ay = a * (F_sum_y - velocity[1])

    return ax, ay

def find_neighbors(positions, neighbors, distances, n, num, width, height):
    """
    指定された粒子 `n` の近隣粒子を見つけ、距離に基づいてソートします。

    Parameters:
        positions: 粒子の位置を格納した (num, 2) 配列
        neighbors: 近隣粒子の位置を格納する (num-1, 2) 配列
        distances: 距離情報を格納する (num-1, 3) 配列 [dx, dy, distance]
        n: 処理対象の粒子インデックス
        num: 全粒子数
        width: シミュレーション領域の幅
        height: シミュレーション領域の高さ
    """
    k = 0  # neighbors, distances のインデックス

    for m in range(num):
        if m == n: 
            continue
        dx = positions[m, 0] - positions[n, 0]
        dy = positions[m, 1] - positions[n, 1]

        # 周期境界条件の適用
        if dx < -width / 2: 
            dx += width
        if dx > width / 2: 
            dx -= width
        if dy < -height / 2: 
            dy += height
        if dy > height / 2: 
            dy -= height

        # 距離を計算
        rmn = np.sqrt(dx**2 + dy**2)

        # neighbors と distances を更新
        neighbors[k, 0] = positions[m, 0]
        neighbors[k, 1] = positions[m, 1]
        distances[k, 0] = dx
        distances[k, 1] = dy
        distances[k, 2] = rmn
        k += 1

    # 距離 (distances[:, 2]) をキーに neighbors をソート
    sorted_indices = np.argsort(distances[:k, 2])  # 距離でソートしたインデックス
    neighbors[:k] = neighbors[sorted_indices]
    distances[:k] = distances[sorted_indices]

def update(positions, velocities, dt, a, b, c, num, width, height):
    """
    更新関数: 速度と位置を更新し、境界条件を適用します。
    """
    # 速度の更新
    for n in range(num):
        # ソートする配列
        neighbors = np.zeros((num - 1, 2))  # {X, Y}
        distances = np.zeros((num - 1, 3))  # {dx, dy, distance}
        
        # 近隣粒子を探す（仮置き）
        find_neighbors(positions, neighbors, distances, n, num, width, height)
        # 加速度を計算
        ax, ay = calculate_acceleration(velocities[n], distances, a, b, c)
        
        # 速度の更新
        velocities[n, 0] += ax * dt
        velocities[n, 1] += ay * dt

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