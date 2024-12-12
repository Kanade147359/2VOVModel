import math
import numpy as np

import initial_values
import simulation

def main():
  row_size = 2
  num = 2
  r = 1.3
  a = 0.5
  b = 1.0
  c = -1.0
  dt = 0.01
  steps = 1000

  width = math.sqrt(3) / 2 * r * row_size
  height = r * row_size

  filepath = 'output/positions.csv'
  positions = initial_values.generate_initial_positions(row_size, num, r)
  velocities = initial_values.generate_initial_velocities(num)

  simulation.run_simulation(positions, velocities, steps, num, dt, a, b, c, width, height, filepath)

if __name__ == '__main__':
  main()