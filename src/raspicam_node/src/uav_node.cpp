#include "uav_node.h"
#include "ttauav_node/flightByOffset.h"
#include "ttauav_node/flightByVel.h"
#include "ttauav_node/gimbalControl.h"
#include "ttauav_node/takeoffOrLanding.h"
/**
 * @brief 控制无人机起飞降落
 * @param mode 1表示起飞，2表示降落
 */
void uav_node::takeoffAndLanding(int mode){
    takeoffAndLanding_client = nh.serviceClient<ttauav_node::takeoffOrLanding>("takeoffOrLanding");
    ttauav_node::takeoffOrLanding xiaoxi;
    xiaoxi.request.takeoffOrLanding = mode;
    if (takeoffAndLanding_client.call(xiaoxi))
    {
        if (mode == 1)
        {
            ROS_INFO("takeoff success!!!!!");
        }
        else
        {
            ROS_INFO("landing success!!!!!");
        }
    }
    else
    {
        ROS_INFO("failed!!!!!!");
    }
}

/**
 * @brief 控制无人机按照速度前进以及转向
 * @param velN 速度北向分量
 * @param velE 速度东向分量
 * @param velD 速度地向分量
 * @param velYaw 速度偏航分量
 * @param time 飞行时间
*/
void uav_node::flightByVel(float velN, float velE, float velD, float velYaw, int time){
    // 速度控制
    flightByVel_client = nh.serviceClient<ttauav_node::flightByVel>("flightByVel");
    ttauav_node::flightByVel xiaoxi;
    xiaoxi.request.vel_n = velN;
    xiaoxi.request.vel_e = velE;
    xiaoxi.request.vel_d = velD;
    if (velN>0.2) xiaoxi.request.vel_n=0.2;
    if (velN<-0.2) xiaoxi.request.vel_n=-0.2;
    if (velE>0.2) xiaoxi.request.vel_e=0.2;
    if (velE<-0.2) xiaoxi.request.vel_e=-0.2;
    if (velD>0.2) xiaoxi.request.vel_d=0.2;
    if (velD<-0.2) xiaoxi.request.vel_d=-0.2;
    xiaoxi.request.targetYaw = velYaw;
    xiaoxi.request.fly_time = time;
    ROS_INFO("%f,%f",velN,velE);
    if (flightByVel_client.call(xiaoxi))
    {
        ROS_INFO("FlyByVal_callSuccess!!!!!");
    }
    else
    {
        ROS_INFO("failed!!!!!!");
    }
}

/**
 * @brief 控制云台转动
 * @param pitch 云台俯仰角
*/
void uav_node::GimbalControl(float pitch)
{
    // 云台控制
    gimbalControl_client = nh.serviceClient<ttauav_node::gimbalControl>("gimbalControl");
    ttauav_node::gimbalControl xiaoxi;
    xiaoxi.request.pitch = pitch;
    if (gimbalControl_client.call(xiaoxi))
    {
        ROS_INFO("success!!!!!");
    }
    else
    {
        ROS_INFO("failed!!!!!!");
    }
}

/**
 * @brief 无人机数据回调函数
 * 用于判断无人机是否稳定,判断动作是否结束
 * @param msg 无人机数据
 */
void uav_node::uavDataCallback(const ttauav_node::uavdata::ConstPtr& msg){
    if(!ActionDown){
        if (msg->accN < 0.2 && msg->accE < 0.2 && msg->accD < 0.2)
        {
            cnt++;
            ROS_INFO("Acting! %d",cnt);
        }
        else{
            ROS_INFO("Acting! %d",cnt);
        }
    }
    if (cnt == time_thre) // 无人机稳定，判断为动作结束
    {
        cnt = 0;
        nh.setParam("IfActionDown", true); // 用于通知所有人动作结束
        ROS_INFO("ActionDown!");
    }
}

/**
 * @brief 无人机动作回调函数
 * 根据a_p的mode执行动作
 * @param msg 动作消息
 */
void uav_node::uavActionCallback(const ttauav_node::action::ConstPtr& msg){
    float velN = msg -> n;
    float velE = msg -> e;
    float velD = msg -> d;
    float velYaw = msg -> yaw;
    float pitch = msg -> PTZ_pitch;
    float fly_time = msg->fly_time;
    // 根据a_p的mode执行动作
    switch (msg -> mode){
        case 1:
            takeoffAndLanding(1);
            nh.setParam("IfActionDown", false);
            ActionDown = nh.param("IfActionDown",true);
            while(!ActionDown){
                ActionDown = nh.param("IfActionDown", true);
                // ROS_INFO("getParam=%d",ActionDown);
                ros::spinOnce();
            } 
            break;
        case 2:
            takeoffAndLanding(2);
            nh.setParam("IfActionDown", false);
            ActionDown = nh.param("IfActionDown", true);
            while(!ActionDown){
                ActionDown = nh.param("IfActionDown", true);
                ROS_INFO("getParam=%d",ActionDown);
                ros::spinOnce();
            } 
            break;
        case 3:
            flightByVel(velN, velE, velD, velYaw, fly_time);
            nh.setParam("IfActionDown", false);
            ActionDown = nh.param("IfActionDown", true);
            while(!ActionDown){
                ActionDown = nh.param("IfActionDown", true);
                ROS_INFO("getParam=%d",ActionDown);
                ros::spinOnce();
            } 
            break;
        case 4:
            GimbalControl(pitch);
            nh.setParam("IfActionDown", false);
            ActionDown = nh.param("IfActionDown", true);
            while(!ActionDown){
                ActionDown = nh.param("IfActionDown", true);
                ROS_INFO("getParam=%d",ActionDown);
                ros::spinOnce();
            } 
            break;
        default:
            break;
    }
}

uav_node::uav_node(){
    cnt = 0;
    time_thre = 10;
    uavAction_sub = nh.subscribe("uavAction", 1000, &uav_node::uavActionCallback, this); 
    ROS_INFO("action subscribed!");
    uavData_sub = nh.subscribe("uavdata", 1000, &uav_node::uavDataCallback, this);
    ROS_INFO("uavdata subscribed!");
    ActionDown = true;
    nh.setParam("IfActionDown", true);
    ROS_INFO("node_init!");
}

int main(int argc, char **argv) {
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"uav");
    ROS_INFO("node start!");
    uav_node uav_node_object;
    while (ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}
