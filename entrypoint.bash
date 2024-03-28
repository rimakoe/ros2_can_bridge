#!/bin/bash

sudo chown -R $(whoami):$(whoami) /home/koeppe/ros2_can_bridge/
python -m pip install --update pip
pip install -e ./ros2_ws/src/cantools
rosdep update
rosdep install -r --rosdistro iron --from-paths ros2_ws/src --ignore-src -y
bash
