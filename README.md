# lidar map loader

## Algorithms
Basically,
1. Publish a fixed GPS position from **publisher.cpp**
2. subscribe the GPS position and publish the map to rviz

For debugging and visualization
```sh
rostopic echo /rechatter/header
rviz
rqt_graph
```
### ver1
* publish the single map from the

references
[link1](http://wiki.ros.org/pcl_ros)
[link2](https://github.com/ros-perception/perception_pcl/blob/melodic-devel/pcl_ros/tools/pcd_to_pointcloud.cpp)

pcd file: 31291-416168-.pcd
image of pcd file ![](/images/ver1.png)

For a single
```sh
# commands
roscore
rosrun lidarmaploader lidarmaploader_pub
rosrun lidarmaploader lidarmaploader_subNpub
rosrun tf static_transform_publisher -312913 -4161689 -40 0 0 0 1 map base_link 10
```
### ver2
