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
  sensor_msgs::PointCloud2 tmp_cloud;

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

  // STEP 3: set the size (N x N) of the grid to load

  int c2s = 1; // center to side -> c2s
  // msg.x = 312913.23; msg.y = 4161689.3; msg.z = 40;
  // 31291-416168-.pcd
  // int idx = (gridcount-1)/2;
  for (int i = -c2s; i < c2s+1; i++){
    for (int j = -c2s; j < c2s+1; j++){
      filename = to_string(static_cast<int>(floor(x/10)+i))+"-"+to_string(static_cast<int>(floor(y/10)+j))+"-.pcd";
      if (pcl::io::loadPCDFile(filename, tmp_cloud) >= 0){
        pcl::concatenatePointCloud(cloud, tmp_cloud, cloud);
      }
    }
  }

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
