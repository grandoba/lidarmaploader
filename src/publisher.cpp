/*
#include "ros/ros.h"
#include "std_msgs/Int32.h"
// Added
void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d]", 3*(msg->data)+2);
}

int main(int argc, char **argv)
{
  ROS_INFO("Start operating publisher...");
  ros::init(argc, argv, "publisher");
  ros::NodeHandle nh;

  ros::Publisher int_pub = nh.advertise<std_msgs::Int32>("chatter", 1000);

  ros::Rate loop_rate(10);

  int count = 0;

  while (ros::ok())
  {
    std_msgs::Int32 msg;
    msg.data = count;
    std::cout<<msg.data<<std::endl;
    int_pub.publish(msg);
    count ++;
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
*/

// # Parsed Best Position in the WGS-84 ECEF frame from Novatel receiver
// Header header

// NovatelMessageHeader novatel_msg_header

// # Position Data (m)
// string solution_status
// string position_type

// float64 x
// float64 y
// float64 z

// # Position Standard Deviation (m)
// float32 x_sigma
// float32 y_sigma
// float32 z_sigma

// # Velocity Data
// string velocity_solution_status
// string velocity_type

// float64 x_vel
// float64 y_vel
// float64 z_vel

// # Velocity Standard Deviation (m/s)
// float32 x_vel_sigma
// float32 y_vel_sigma
// float32 z_vel_sigma

// string base_station_id
// float32 velocity_latency

// # Data Ages (sec)
// float32 diff_age
// float32 solution_age

// # Satellite Usage
// uint8 num_satellites_tracked
// uint8 num_satellites_used_in_solution
// uint8 num_gps_and_glonass_l1_used_in_solution
// uint8 num_gps_and_glonass_l1_and_l2_used_in_solution

// # Extended Solution Status
// NovatelExtendedSolutionStatus extended_solution_status

// # Signal Masks
// NovatelSignalMask signal_mask

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
















































