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

<img src="/images/ver1.png" alt="pcd" width="400"/>

For a single
```sh
# commands
roscore
rosrun lidarmaploader lidarmaploader_pub
rosrun lidarmaploader lidarmaploader_subNpub
rosrun tf static_transform_publisher -312913 -4161689 -40 0 0 0 1 map base_link 10
```
### ver2
* publish NxN grid of pointcloud.
* ver2 now takes the form of the second reference link: "pcd_to_pointcloud".

#### TEST 1: see how fast it becomes as the size of N increases
* 월드컵북로의 경우 (memory size)

| Grid Size   | mean        | std         | max         | min           |
| :---:       | :----:      | :----:      |    :----:   |   :----:      |
| 3x3         | 31          | 38          | 283         |  0            |
| 5x5         | 84          | 82          | 539         |  0            |
| 7x7         | 159         | 135         | 786         |  0            |
| 9x9         | 252         | 190         | 1033        |  0            |
| 11x11       | 360         | 240         | 1202        |  0            |
| 13x13       | 480         | 283         | 1351        |  0            |

* Speed test
| Grid Size   | mean        | std         | max         | min           |
| :---:       | :----:      | :----:      |    :----:   |   :----:      |
| 3x3         | 31          | 38          | 283         |  0            |
| 5x5         | 84          | 82          | 539         |  0            |
| 7x7         | 159         | 135         | 786         |  0            |
| 9x9         | 252         | 190         | 1033        |  0            |
| 11x11       | 360         | 240         | 1202        |  0            |
| 13x13       | 480         | 283         | 1351        |  0            |

#### TEST 2
* Load and save cloud and publish || load each time and publish?




### ver3
* dynamically add grids to global map
* assume moving current GPS value
