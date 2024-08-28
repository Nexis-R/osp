# OSP
長岡技術科学大学木村研究室が開発・提供しているレスキュー対応ロボットのためのプラットフォームロボットOSPのROS2パッケージ
![osp-robot](images/image.png)

ハードウェアのリポジトリはこちらから↓<br>
[opensource-platform](https://github.com/yanagi-kimuralab/opensource-platform?tab=readme-ov-file)

# 環境構築
## 要件
[![humble][humble-badge]][humble]
[![ubuntu22][ubuntu22-badge]][ubuntu22]
- Ubuntu22.04
- ROS2 Humble

## 依存関係
```bash
source /opt/ros/humble/setup.bash

git clone https://github.com/Nexis-R/osp
cd osp
# 自動インストールスクリプト
sudo ./scripts/install-all
# Desktopアプリの追加スクリプト
./scripts/install-bringup-scripts
vcs import --input depends.rosinstall --recursive src
rosdep update
rosdep install -r -y -i --from-paths .
```

## ビルド
```bash
cd ~/osp
colcon build --symlink-install
source install/setup.bash
```

## 使用方法
### オペレーターPC
```bash
ros2 launch 
```
### ロボット側NUC PC
```bash
ros2 launch 
```