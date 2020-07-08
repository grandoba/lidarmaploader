/*  Using Classes to republish!

#include "myclass.h"
int main(int argc, char **argv)
{
  ros::init(argc, argv, "subNpub");
  myclass Myobject;
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    Myobject.publishDataIfRecieved();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
*/
/*
// sub N pub version3
#include "ros/ros.h"
#include "std_msgs/Int32.h"

std_msgs::Int32 remsg;


void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  remsg.data = 3*(msg->data)+2;
  ROS_INFO("I heard: [%d]", remsg.data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subNpub");

  ros::NodeHandle nh;

//  ros::Publisher int_repub = nh.advertise<std_msgs::Int32>("rechatter", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  { 
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

    std::cout<<remsg.data<<std::endl;
      
//    int_repub.publish(remsg);

    std::cout<<"hello"<<std::endl;

    ros::spinOnce();

    loop_rate.sleep();
  }
  
  return 0;
}
*/
//    Easiest Variation 4

#include "ros/ros.h"
#include "novatel_gps_msgs/NovatelXYZ.h"
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <std_msgs/String.h>
using namespace std;

novatel_gps_msgs::NovatelXYZ remsg;
ros::Publisher repub;
int XX=-1;
int YY=-1;


void chatterCallback(const novatel_gps_msgs::NovatelXYZ::ConstPtr& msg)
{
  sensor_msgs::PointCloud2 cloud;
  cloud.header.stamp = ros::Time::now();


  float x,y,z;

  x = msg->x;  
  y = msg->y;  
  z = msg->z;
  ROS_INFO("I heard: [%f]", x);
  ROS_INFO("I heard: [%f]", y);
  ROS_INFO("I heard: [%f]", z);

  int xx = static_cast<int>(floor(x/10));
  int yy = static_cast<int>(floor(y/10));

  // // STEP 1: Checking if the car is on a different grid
  // if ((XX == x) || (YY == y)) {
  //   ROS_INFO("on the same grid!");
  //   return false;
  // }

  // STEP 2: load pointcloud of the grid currently at.
  // std_msgs::String filename;
  // filename.data = to_string(x)+"-"+to_string(y)+"-.pcd";
  string filename = to_string(xx)+"-"+to_string(yy)+"-.pcd";  
  if(pcl::io::loadPCDFile(filename, cloud) < 0){
    ROS_ERROR_STREAM("Failed to parse pointcloud from file ('" << filename << "')");

// WHAT TO DO HERE?

    // need to return something... but it's void!!!

// 

  }
  
  // // STEP 3: set the size (N x N) of the grid to load 
  // int gridcount = 3; //should be odd 
  // int idx = (gridcount-1)/2;
  // for (int i = -idx; i < idx+1; i++){
  //   for (int j = -idx; j < idx+1; j++){
  //     filename = to_string(x+i)+"-"+to_string(y+j)+"-.pcd";
  //     pcl::io::loadPCDFile(filename, cloud)
  //   }
  // }
  cloud.header.frame_id = "/base_link";
  ROS_INFO_STREAM("Loaded pointcloud with the following stats");
  ROS_INFO_STREAM(" * number of points: " << cloud.width * cloud.height);
  ROS_INFO_STREAM(" * total size [bytes]: " << cloud.data.size());
  ROS_INFO_STREAM(" * channel names: " << pcl::getFieldsList(cloud));
  repub.publish(cloud);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subNpub");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
  repub = nh.advertise<sensor_msgs::PointCloud2>("rechatter", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  { 
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}


/*
//    Easiest Variation 3

#include "ros/ros.h"
#include "std_msgs/Int32.h"

std_msgs::Int32 remsg;

void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  remsg.data = 3*(msg->data)+2;  
  ROS_INFO("I heard: [%d]", remsg.data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subNpub"); //different name try it out. "listenerNNN"
  ros::NodeHandle nh;
  ros::Rate loop_rate(1000);



  while (ros::ok())
  { 

    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
//    std::cout<<remsg.data<<std::endl;

    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
*/

/*
   Easiest Variation 2
#include "ros/ros.h"
#include "std_msgs/Int32.h"


void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  std::cout<<3*(msg->data)+2<<std::endl;
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "subNpub"); //different name try it out. "listenerNNN"

  ros::NodeHandle nh;
  	
  ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

  ros::spin();
  
  return 0;
}




//    Easiest Variation 1

#include "ros/ros.h"
#include "std_msgs/Int32.h"

std_msgs::Int32 remsg;

void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  remsg.data = 3*(msg->data)+2;  
  ROS_INFO("I heard: [%d]", remsg.data);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "subNpub"); //different name try it out. "listenerNNN"

  ros::NodeHandle nh;
  	
  ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

  ros::spin();
  
  return 0;
}



int main(int argc, char **argv)
{

  ros::init(argc, argv, "subNpub"); //different name try it out. "listenerNNN"

  ros::NodeHandle nh;
  	
  ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

  ros::Publisher int_repub = nh.advertise<std_msgs::Int32>("rechatter", 1000);

  std_msgs::Int32 remsg;

  remsg = ((sub.data)-2)/3;
	
  int_repub.publish(remsg);

  ros::spin();
  
  return 0;
}
*/
