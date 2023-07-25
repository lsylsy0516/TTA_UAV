#ifndef UAV_NODE_H
#define UAV_NODE_H

#include "ros/ros.h"
#include "ttauav_node/flightByOffset.h"
#include "ttauav_node/flightByVel.h"
#include "ttauav_node/gimbalControl.h"
#include "ttauav_node/takeoffOrLanding.h"
#include "ttauav_node/action.h"
#include "ttauav_node/uavdata.h"

/**
 * @brief 无人机动作控制节点
 * 版本：v1.0
 * 具体功能：接受Action消息，根据消息中的mode执行相应动作，并发布动作是否结束的消息
 * 1：起飞
 * 2：降落
 * 3：前进
 * 4：云台控制
 */
class uav_node
{
public:
    uav_node();
private:
    ros::NodeHandle nh;
    ros::Subscriber uavAction_sub;
    ros::Subscriber uavData_sub;
    ros::ServiceClient flightByVel_client;
    ros::ServiceClient gimbalControl_client;
    ros::ServiceClient takeoffAndLanding_client;
    void uavActionCallback(const ttauav_node::action::ConstPtr& msg);
    void uavDataCallback(const ttauav_node::uavdata::ConstPtr& msg);
    
    void takeoffAndLanding(int mode);
    void flightByVel(float velN, float velE, float velD, float velYaw, int time);
    void GimbalControl(float yaw);
    
    int ActionDown; // 0表示动作未结束，1表示动作结束
    int time_thre; // 50*20ms = 1s
    int cnt; // 用于计数
};
#endif  // UAV_NODE_H