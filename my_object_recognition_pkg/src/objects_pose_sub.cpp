#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


#include <boost/thread/thread.hpp>
#include <darknet_ros_msgs/BoundingBox.h>
#include <darknet_ros_msgs/BoundingBoxes.h>

#include <fstream>
#include <iostream>
using namespace message_filters;


#define class_num  20
#define DEBUG 1

void depth_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& detect_msg, const sensor_msgs::Image::ConstPtr& msg)
{
    int u[class_num] = {};
    int v[class_num] = {};
    int centerIdx[class_num] = {};

    int sizes = msg->data.size();

   
    
    int num = detect_msg->bounding_boxes.size();
 
    for (int i = 0; i < num; i++)
    {
        u[i] = ((detect_msg->bounding_boxes[i].xmax - detect_msg->bounding_boxes[i].xmin)/2) + detect_msg->bounding_boxes[i].xmin; 
        v[i] = ((detect_msg->bounding_boxes[i].ymax - detect_msg->bounding_boxes[i].ymin)/2) + detect_msg->bounding_boxes[i].ymin;
        centerIdx[i] = u[i] + msg->width * v[i];
        if (centerIdx[i] < 0) 
        {
            centerIdx[i] = 0;
        }
        else if (centerIdx[i] > sizes /4)
        {
            centerIdx[i] = sizes /4;
        }
    }
    std::cout<<"Bouding Boxes (header):" << detect_msg->header <<std::endl;
    std::cout<<"Bouding Boxes (image_header):" << detect_msg->image_header <<std::endl;
    std::cout<<"Bouding Boxes (Class):" << "\t";

    std::ofstream write;
    write.open("result-test.csv", std::ios::app);
    for (int i = 0; i < num; i++)
    {
        std::cout << detect_msg->bounding_boxes[i].Class << "\t";
        std::cout<<"Center distance :  " << depths[centerIdx[i]] << "  m" << std::endl;
        write << detect_msg->bounding_boxes[i].Class << ","<< depths[centerIdx[i]] <<  std::endl;   
    }
    write.close();
    std::cout << "\033[2J\033[1;1H";     // clear terminal
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "fuse_data");
    ros::NodeHandle n;
    
    message_filters::Subscriber<darknet_ros_msgs::BoundingBoxes> object_sub(n, "/darknet_ros/bounding_boxes", 1);
    
    

    typedef sync_policies::ApproximateTime<darknet_ros_msgs::BoundingBoxes, sensor_msgs::Image> syncPolicy;
    Synchronizer<syncPolicy> sync(syncPolicy(10), object_sub, depth_sub); 
    
    sync.registerCallback(boost::bind(&depth_callback, _1, _2));
    ros::spin();
    return 0;
}
    
