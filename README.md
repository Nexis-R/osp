# OSP
長岡技術科学大学木村研究室が開発・提供しているレスキュー対応ロボットのためのプラットフォームロボットOSPのROS2パッケージ
![osp-robot](images/image.png)

ハードウェアのリポジトリはこちらから↓<br>
[opensource-platform](https://github.com/yanagi-kimuralab/opensource-platform?tab=readme-ov-file)

# 環境構築
## 要件
- Ubuntu22.04
- ROS2 Humble

## 依存関係
```bash
source /opt/ros/humble/setup.bash
rosdep update

git clone https://github.com/Nexis-R/osp
cd osp
./install-scripts/install-all 
vcs import --input depends.rosinstall --recursive src
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