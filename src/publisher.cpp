
#include "ros/ros.h"
#include "novatel_gps_msgs/NovatelXYZ.h"

int main(int argc, char **argv)
{
  ROS_INFO("Start operating publisher...");
  ros::init(argc, argv, "publisher");
  ros::NodeHandle nh;

  ros::Publisher int_pub = nh.advertise<novatel_gps_msgs::NovatelXYZ>("chatter", 1000);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    novatel_gps_msgs::NovatelXYZ msg;

    msg.x = 312913.23; msg.y = 4161689.3; msg.z = 40;

    std::cout<<msg.x<<std::endl;
    std::cout<<msg.y<<std::endl;
    std::cout<<msg.z<<std::endl;
    std::cout<<"---"<<std::endl;

    double secs = ros::Time::now().toSec();
    ROS_INFO("secs is %f",secs);

    int_pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
