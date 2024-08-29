#!/bin/bash

# 使用するROSミドルウェア実装をCycloneDDSに設定
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

# ROS 環境のセットアップ
source /opt/ros/humble/setup.bash

# ユーザーのROSワークスペース環境のセットアップ
source ~/osp/install/setup.bash

# ターミナルの設定ファイルをソース
source ~/.bashrc

# Ctrl-C (SIGINT) シグナルを処理して、クリーンアップを行うトラップを設定
trap cleanup SIGINT

# SIGINTを受信したときに呼び出されるクリーンアップ関数を定義
function cleanup {
    echo "Ctrl-C was pressed. Cleaning up..."
    wait $PID
    echo "Cleanup complete."
    exit
}

# ROS2のteleop launch　ファイルをバックグラウンドで起動
ros2 launch osp_teleop osp_teleop.launch.xml $@ &
PID=$!

# バックグラウンドプロセスが終了するのを待つ
wait $PID