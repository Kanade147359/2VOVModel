#!/bin/bash
#PBS -N kanade_simulation_job
#PBS -l nodes=1:ppn=20
#PBS -l walltime=02:00:00
#PBS -l mem=4gb
#PBS -j oe
#PBS -o /path/to/output_directory/simulation_job_output.log

#PBS -l host=yagami02

# 必要なディレクトリを作成
mkdir -p output frames


# 必要なモジュールをロード（必要であれば）
# module load gcc/9.3.0  # 必要なGCCバージョンを指定
# module load python/3.8  # 必要なPythonバージョンを指定

# Makefileを使ってコンパイルとシミュレーションを実行
make
./simulation.out
make gif

# 終了メッセージ
echo "Simulation and GIF creation completed."
