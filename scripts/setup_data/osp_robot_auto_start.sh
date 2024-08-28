#!/bin/bash
# ROS 環境のセットアップ
source /opt/ros/humble/setup.bash
# ユーザーのROSワークスペース環境のセットアップ
source ~/osp/install/setup.bash

# Unbind the USB device
echo "Unbind the USB device"
echo "1-1" | sudo tee /sys/bus/usb/drivers/usb/unbind

# Wait for 4 seconds
sleep 4

# Bind the USB device
echo "Bind the USB device"
echo "1-1" | sudo tee /sys/bus/usb/drivers/usb/bind

# ターミナルの設定ファイルをソース
source ~/.bashrc

# セッション名
SESSION_NAME="osp_robot_auto_session"

# 同名のセッションが存在するか確認し、存在する場合は終了する
if byobu list-sessions | grep -q "^$SESSION_NAME:"; then
    byobu kill-session -t $SESSION_NAME
fi

# 新しいセッションを開始
byobu new-session -d -s $SESSION_NAME

# 左側のペインでtopを実行
byobu send-keys -t ${SESSION_NAME}:0 "top; exec bash" Enter

# 新しいペインを作成し右側でgiant_bringup_auto.launchを実行
byobu split-window -h -t ${SESSION_NAME}:0
byobu send-keys -t ${SESSION_NAME}:0.1 "source /opt/ros/humble/setup.bash; ros2 launch osp_bringup osp_bringup.launch.xml; exec bash" Enter

# Byobuセッションをアタッチ
byobu attach-session -t $SESSION_NAME
