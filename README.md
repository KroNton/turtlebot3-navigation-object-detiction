# turtlebot3-navigation-object-detiction

Downloading turtlebot3 pkgs 

inside catkin_ws/src/


git clone https://github.com/ROBOTIS-GIT/turtlebot3.git

git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git

git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git

git clone https://github.com/KroNton/turtlebot3-navigation-object-detiction.git

---------------------------------------------------------------------------------------------------------------------


Navigation and object detection 

inside catkin_ws/

To run the simulation in gazebo 

open new terminal and run the following commands:

source devel/setup.bash 

export TURTLEBOT3_MODEL=waffle_pi

 roslaunch turtlebot3_assignment turtlebot3_office.launch 


To run the navigation stack

open new terminal and run the following commands:

 source devel/setup.bash 

export TURTLEBOT3_MODEL=waffle_pi

roslaunch turtlebot3_assignment turtlebot3_navigation.launch 






To run the object detection part

open new terminal and run the following commands:

source devel/setup.bash 
roslaunch my_object_recognition_pkg yolo_v2_tiny.launch 


