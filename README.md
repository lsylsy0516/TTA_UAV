# TTA_UAV
Based on the official TTA_UAV sample code for secondary development, suitable for the DJI Intelligent Warehousing Competition

## 主程序 `uav_node.cpp` 

`uav_node.cpp` 用于控制无人机的起飞、降落、飞行和云台控制等动作

### 函数 `takeoffAndLanding(int mode)`

控制无人机的起飞和降落动作。通过ROS服务调用来与无人机控制器进行通信，发送起飞或降落指令，并根据返回的结果打印相应的提示信息。

### 函数 `flightByVel(float velN, float velE, float velD, float velYaw, int time)`

控制无人机按照给定的速度前进以及转向。通过ROS服务调用来与无人机控制器进行通信，发送速度控制指令，并根据返回的结果打印相应的提示信息。

### 函数 `GimbalControl(float pitch)`

控制无人机的云台转动。通过ROS服务调用来与无人机控制器进行通信，发送云台控制指令，并根据返回的结果打印相应的提示信息。

### 回调函数 `uavDataCallback(const ttauav_node::uavdata::ConstPtr& msg)`

接收无人机数据，并根据数据判断无人机是否稳定和动作是否结束。当无人机稳定时，计数器增加，若计数器达到预设阈值，则判断为动作结束，并通知其他节点动作已完成。

### 回调函数 `uavActionCallback(const ttauav_node::action::ConstPtr& msg)`

接收来自其他节点的无人机动作指令消息，并根据指令中的 mode 执行相应的动作。根据不同的 mode 调用上述的控制函数来实现起飞、降落、飞行或云台控制等功能。

### 构造函数 `uav_node()`

`uav_node`类的构造函数。在构造函数中，初始化ROS节点，订阅无人机数据和动作消息的主题，并初始化一些参数和状态变量。

### 成员变量

- `takeoffAndLanding_client`: ROS服务客户端，用于发送起飞和降落指令。
- `flightByVel_client`: ROS服务客户端，用于发送速度控制指令。
- `gimbalControl_client`: ROS服务客户端，用于发送云台控制指令。
- `uavAction_sub`: ROS消息订阅器，订阅无人机动作消息。
- `uavData_sub`: ROS消息订阅器，订阅无人机数据。
- `cnt`: 用于计数无人机稳定的时间步长。
- `time_thre`: 无人机稳定的时间阈值。
- `ActionDown`: 表示无人机动作是否完成的状态标志。

该文件的功能是实现无人机控制节点，根据接收到的动作指令控制无人机的起飞、降落、飞行和云台控制等动作，并根据无人机数据判断动作是否完成。同时，它通过ROS的服务和消息机制与其他节点进行通信，实现无人机的控制与状态更新。