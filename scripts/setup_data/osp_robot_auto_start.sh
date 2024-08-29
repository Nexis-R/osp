#!/bin/bash

# SSH接続して、リモートでコマンドを実行
ssh osp-nuc@osp-nuc.local -X << EOF
    # 使用するROSミドルウェア実装をCycloneDDSに設定
    export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

    # ROS 環境のセットアップ
    source /opt/ros/humble/setup.bash

    # ユーザーのROSワークスペース環境のセットアップ
    source ~/osp/install/setup.bash

    # ターミナルの設定ファイルをソース
    source ~/.bashrc

    # Ctrl-C (SIGINT) シグナルとスクリプト終了時にクリーンアップを行うトラップを設定
    trap cleanup SIGINT EXIT

    # SIGINTまたはスクリプト終了時に呼び出されるクリーンアップ関数を定義
    function cleanup {
        echo "Cleaning up..."
        if [ -n "\$PID" ]; then
            kill \$PID 2>/dev/null
            wait \$PID
        fi
        echo "Cleanup complete."
        exit
    }

    # ROS2のteleop bringup ファイルをバックグラウンドで起動
    ros2 launch osp_bringup osp_bringup.launch.xml $@ &
    PID=\$!

    # バックグラウンドプロセスが終了するのを待つ
    wait \$PID

    # 無限ループでSSHセッションを維持
    while true; do
        sleep 1
    done
EOF
