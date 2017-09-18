echo "===========Copying and replacing camera module==========="

cp $(pwd)/accessories/kinect_camera.gazebo.xacro ~/Documents/husky_kinetic/src/husky_simulator/husky_gazebo/urdf/accessories/kinect_camera.gazebo.xacro

echo "===========Copying and replacing launch files==========="
cp -fR $(pwd)/launch ~/Documents/husky_kinetic/src/husky_simulator/husky_gazebo/