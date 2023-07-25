#include "flight_mode.h"
#include "ros/ros.h"

bool flightByOffset(float targetYaw, float offsetZ, float yawThreshold, float posThreshold)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ttauav_node::flightByOffset>("flightByOffset");

    ttauav_node::flightByOffset xiaoxi;
    xiaoxi.request.targetYaw = targetYaw;
    xiaoxi.request.offset.push_back(0);
    xiaoxi.request.offset.push_back(0);
    xiaoxi.request.offset.push_back(offsetZ);
    xiaoxi.request.yawThreshold = yawThreshold;
    xiaoxi.request.posThreshold = posThreshold;

    if (client.call(xiaoxi))
    {
        ROS_INFO("success!!!!!");
        ROS_INFO("result: %d", xiaoxi.response.ack);
        return true;
    }
    else
    {
        ROS_INFO("failed!!!!!!");
        return false;
    }
}

bool flightByVel(float velN, float velE, float velD, float targetYaw, int flyTime)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ttauav_node::flightByVel>("flightByVel");

    ttauav_node::flightByVel xiaoxi;
    xiaoxi.request.targetYaw = targetYaw;
    xiaoxi.request.vel_n = velN;
    xiaoxi.request.vel_e = velE;
    xiaoxi.request.vel_d = velD;
    xiaoxi.request.fly_time = flyTime;

    if (client.call(xiaoxi))
    {
        ROS_INFO("success!!!!!");
        ROS_INFO("result: %d", xiaoxi.response.ack);
        return true;
    }
    else
    {
        ROS_INFO("failed!!!!!!");
        return false;
    }
}

bool gimbalControl(float pitch)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ttauav_node::gimbalControl>("gimbalControl");

    ttauav_node::gimbalControl xiaoxi;
    xiaoxi.request.pitch = pitch;

    if (client.call(xiaoxi))
    {
        ROS_INFO("success!!!!!");
        ROS_INFO("result: %d", xiaoxi.response.ack);
        return true;
    }
    else
    {
        ROS_INFO("failed!!!!!!");
        return false;
    }
}

bool takeoffAndLanding(int takeoffOrLanding)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ttauav_node::takeoffOrLanding>("takeoffOrLanding");

    ttauav_node::takeoffOrLanding xiaoxi;
    xiaoxi.request.takeoffOrLanding = takeoffOrLanding;

    if (client.call(xiaoxi))
    {
        ROS_INFO("success b!!!!!");
        ROS_INFO("result: %d", xiaoxi.response.ack);
    }
    else
    {
        ROS_INFO("failed!!!!!!");
        return false;
    }

}
