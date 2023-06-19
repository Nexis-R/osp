echo "alias rt-imu-conf='ros2 lifecycle set /rt_usb_9axisimu_driver configure'" >> ~/.bash_aliases
echo "alias rt-imu-act='ros2 lifecycle set /rt_usb_9axisimu_driver activate'" >> ~/.bash_aliases
echo "alias teleop-osp='rt-imu-conf; rt-imu-act; ros2 launch osp_teleop osp_teleop.launch.xml'" >> ~/.bash_aliases