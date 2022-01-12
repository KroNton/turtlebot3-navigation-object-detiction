#!/usr/bin/env python
from re import I
import rospy
from sensor_msgs.msg import Image
from darknet_ros_msgs.msg import BoundingBox
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import Header
from std_msgs.msg import String


def callback(data):
     num =len( bounding_boxes)

    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.bounding_boxes[0].xmin)
    
def listener():


    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/darknet_ros/bounding_boxes", BoundingBoxes, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
