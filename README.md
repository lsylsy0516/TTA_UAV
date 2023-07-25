# TTA_UAV

## 简介

TTA_UAV（TTA Unmanned Aerial Vehicle）是基于ROS（Robot Operating System）的无人机控制框架，专门为大疆智能仓储竞赛开发的样例代码，支持二次开发。该框架允许用户通过发送各种指令来控制无人机的行为，包括起飞、降落、跟随目标和扫描等动作。

![image](./gif/0.gif)

## 依赖关系

- ROS（Robot Operating System）：用于无人机控制的通信和消息发布。

## 执行流程

### 调试模式

在调试模式下，我们通常希望能够方便地查看节点输出的ROS消息，

1. 打开终端窗口并运行`roscore`启动ROS主节点。
2. 在每个终端窗口中执行`source devel/setup.bash`命令，以便加载工作空间中的ROS包。
3. 在不同的终端窗口中运行各个节点：
   
   ```bash
   rosrun ttauav_node uavData
   rosrun ttauav_node service
   rosrun ttauav_node uav_node
   ```
4. 在每个节点的输出中，你可以查看到节点发布的`ROS_INFO`等消息，从而进行调试和观察节点的运行情况。

### 任务模式

在任务模式下，我们希望将多个节点封装在一个启动文件中，一次性运行它们以完成特定任务。这样可以方便部署和运行，不需要频繁切换终端窗口。在ROS中，可以使用`roslaunch`工具实现这一目的。以下是具体的步骤：

1. 打开终端窗口并运行`roscore`启动ROS主节点。
2. 在工作空间目录下运行`catkin_make`编译ROS包。
3. 运行任务启动文件，例如：
   
   ```bash
   roslaunch ttauav_node uav_node.launch
   ```
4. `roslaunch`命令将会自动运行启动文件中定义的所有节点，并将它们组织在一个ROS网络中。

在任务模式下，你可以一次性运行多个节点并完成特定的任务，无需手动运行多个终端窗口。这样可以提高运行效率，并方便部署和使用。

## 主程序 `uav_node.cpp`

`uav_node.cpp` 用于控制无人机的起飞、降落、飞行和云台控制等动作

### 主要功能

- 无人机控制节点 `uav_node`：
  - 接收来自全局控制节点的指令。
  - 根据接收到的指令，发送不同的无人机控制指令，如起飞、降落、飞行速度和云台控制等。
  - 通过更新参数服务器中的参数，实现动作的触发和连续执行。

## 解释

### 类 `uav_node`

- #### 函数  `takeoffAndLanding(int mode)`

控制无人机的起飞和降落动作。通过ROS服务调用来与无人机控制器进行通信，发送起飞或降落指令，并根据返回的结果打印相应的提示信息。

- #### 函数  `flightByVel(float velN, float velE, float velD, float velYaw, int time)`
  
  - 控制无人机按照给定的速度前进以及转向。通过ROS服务调用来与无人机控制器进行通信，发送速度控制指令，并根据返回的结果打印相应的提示信息。

- #### 函数  `GimbalControl(float pitch)`
  
  - 控制无人机的云台转动。通过ROS服务调用来与无人机控制器进行通信，发送云台控制指令，并根据返回的结果打印相应的提示信息。

- #### 回调函数 `uavDataCallback(const ttauav_node::uavdata::ConstPtr& msg)`
  
  - 接收无人机数据，并根据数据判断无人机是否稳定和动作是否结束。当无人机稳定时，计数器增加，若计数器达到预设阈值，则判断为动作结束，并通知其他节点动作已完成。

- #### 回调函数 `uavActionCallback(const ttauav_node::action::ConstPtr& msg)`
  
  - 接收来自其他节点的无人机动作指令消息，并根据指令中的 mode 执行相应的动作。根据不同的 mode 调用上述的控制函数来实现起飞、降落、飞行或云台控制等功能。

- #### 构造函数 `uav_node()`
  
  - `uav_node`类的构造函数。在构造函数中，初始化ROS节点，订阅无人机数据和动作消息的主题，并初始化一些参数和状态变量。

- #### 成员变量
  
  - `takeoffAndLanding_client`: ROS服务客户端，用于发送起飞和降落指令。
  - `flightByVel_client`: ROS服务客户端，用于发送速度控制指令。
  - `gimbalControl_client`: ROS服务客户端，用于发送云台控制指令。
  - `uavAction_sub`: ROS消息订阅器，订阅无人机动作消息。
  - `uavData_sub`: ROS消息订阅器，订阅无人机数据。
  - `cnt`: 用于计数无人机稳定的时间步长。
  - `time_thre`: 无人机稳定的时间阈值。
  - `ActionDown`: 表示无人机动作是否完成的状态标志。
