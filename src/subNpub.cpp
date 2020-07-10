#include "ros/ros.h"
#include "novatel_gps_msgs/NovatelXYZ.h"
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <std_msgs/String.h>
using namespace std;



class pcd_to_grid_to_PointCloud {

  ros::NodeHandle nh;
  // the topic to publish at, will be overwritten to give the remapped name
  std::string cloud_topic;
  // source file name, will be overwritten to produce actually configured file
  std::string file_name;
  // tf2 frame_id
  std::string frame_id;
  // latched topic enabled/disabled
  bool latch;
  // pointcloud message and publisher
  sensor_msgs::PointCloud2 cloud;
  ros::Publisher pub;
  // timer to handle republishing
  ros::Timer timer;
  // center grid location according to GPS
  std::string currGrid = "a";
  std::string prevGrid = "b";

  void chatterCallback(const novatel_gps_msgs::NovatelXYZ::ConstPtr& msg) {
    float x,y,z;
    x = msg->x;
    y = msg->y;
    z = msg->z;
    ROS_INFO("I heard: [%f]", x);
    ROS_INFO("I heard: [%f]", y);
    ROS_INFO("I heard: [%f]", z);
    int xx = static_cast<int>(floor(x/10));
    int yy = static_cast<int>(floor(y/10));
    currGrid = to_string(xx)+"-"+to_string(yy)+"-.pcd";

    int num_subscribers = pub.getNumSubscribers();
    if (num_subscribers > 0) {
        ROS_DEBUG("Publishing data to %d subscribers.", num_subscribers);
    }

    // Check if current location (GPS) is at another 10mx10m grid.
    if ( currGrid != prevGrid ){

      sensor_msgs::PointCloud2 tmp_cloud;

      if(pcl::io::loadPCDFile(currGrid, cloud) < 0){
        ROS_ERROR_STREAM("Failed to parse pointcloud from file ('" << currGrid << "')");
      }
      int c2s = 1; // center to side -> c2s
      // msg.x = 312913.23; msg.y = 4161689.3; msg.z = 40;
      // 31291-416168-.pcd
      for (int i = -c2s; i < c2s+1; i++){
        for (int j = -c2s; j < c2s+1; j++){
          std::string filename = to_string(static_cast<int>(floor(x/10)+i))+"-"+to_string(static_cast<int>(floor(y/10)+j))+"-.pcd";
          if (pcl::io::loadPCDFile(filename, tmp_cloud) >= 0){
            pcl::concatenatePointCloud(cloud, tmp_cloud, cloud);
          }
        }
      }
      prevGrid = currGrid;
    }

    // update timestamp and publish
    cloud.header.stamp = ros::Time::now();
    ROS_DEBUG_STREAM_ONCE("Publishing pointcloud");
    ROS_DEBUG_STREAM_ONCE(" * number of points: " << cloud.width * cloud.height);
    ROS_DEBUG_STREAM_ONCE(" * frame_id: " << cloud.header.frame_id);
    ROS_DEBUG_STREAM_ONCE(" * topic_name: " << cloud_topic);
    pub.publish(cloud);
  }

public:

    void init_run() {
        // init publisher
        pub = nh.advertise<sensor_msgs::PointCloud2>(cloud_topic, 1, latch);
        // treat publishing once as a special case to interval publishing
        ros::Subscriber sub = nh.subscribe("chatter", 1000, &pcd_to_grid_to_PointCloud::chatterCallback, this);
        // set frame_id
        cloud.header.frame_id = frame_id;
    }

    void print_config_info() {
        ROS_INFO_STREAM("Recognized the following parameters");
        ROS_INFO_STREAM(" * frame_id: " << frame_id);
        ROS_INFO_STREAM(" * topic_name: " << cloud_topic);
        ROS_INFO_STREAM(" * latch: " << std::boolalpha << latch);
    }

};


int main (int argc, char** argv) {
    // init ROS
    ros::init(argc, argv, "pcd_to_grid_to_PointCloud");
    // set up node
    pcd_to_grid_to_PointCloud node;
    // print info about effective configuration settings
    node.print_config_info();
    // initialize run
    node.init_run();

    // blocking call to process callbacks etc
    // ros::spin();
    ros::Rate loop_rate(10); //same as "loop_rate = 10" in Hz
    while ( ros::ok() )
    {
      ros::Time start_t = ros::Time::now();
      ros::spinOnce();
      ros::Time fin_t = ros::Time::now();
      double dt = (fin_t - start_t).toSec();
      ROS_INFO("time for 1 callback is [%f]",dt);
      loop_rate.sleep();
    }
    return 0;
}
