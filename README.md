```
# Install the ROS 2 Humble packages for computer vision
sudo apt update
sudo apt install ros-humble-cv-bridge ros-humble-opencv
```

```
# Re-source your ROS 2 environment (if not already done)
source /opt/ros/humble/setup.bash
# Rebuild the package
colcon build --packages-select computer_vision
```
