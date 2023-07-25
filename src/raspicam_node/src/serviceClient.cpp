#include "ros/ros.h"
#include "ttauav_node/takeoffOrLanding.h"
#include "ttauav_node/flightByOffset.h"
#include "ttauav_node/gimbalControl.h"
#include "ttauav_node/flightByVel.h"
 
int main(int argc, char  *argv[])
{

    //if (argc < 2)
    {
        ROS_ERROR("please set :1-takeoff 2-landing 3-flightByOffset 4-flightByVel 5-gimbalControl");
      //  return 1;
    }

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"client");
    ros::NodeHandle n;

    if(atoi(argv[1]) == 3) // 
    {
        ros::ServiceClient client = n.serviceClient<ttauav_node::flightByOffset>("flightByOffset");

        ttauav_node::flightByOffset xiaoxi ;
        xiaoxi.request.targetYaw = 90.2f* atof(argv[2]);

        std::vector<float> arrp;

        arrp.push_back(0);
        arrp.push_back(0);
        arrp.push_back(0);

        xiaoxi.request.offset = arrp;
        xiaoxi.request.yawThreshold = 1.0;
        xiaoxi.request.posThreshold = 0.5;

        bool tiaojian = client.call(xiaoxi);
        if(tiaojian)
        {
            ROS_INFO("success!!!!!");
            ROS_INFO("result：%d",xiaoxi.response.ack);
        }
        else
        {
            ROS_INFO("failed!!!!!!");
        }
    }
    else if(atoi(argv[1]) == 4)
    {
        ros::ServiceClient client = n.serviceClient<ttauav_node::flightByVel>("flightByVel");

        ttauav_node::flightByVel xiaoxi ;

        xiaoxi.request.vel_n = atof(argv[2]);
        xiaoxi.request.vel_e = atof(argv[3]);
        xiaoxi.request.vel_d = atof(argv[4]);

        xiaoxi.request.targetYaw = atof(argv[5]);
        xiaoxi.request.fly_time = atof(argv[6]); // 运动n毫秒

        bool tiaojian = client.call(xiaoxi);
        if(tiaojian)
        {
            ROS_INFO("success!!!!!");
            ROS_INFO("result：%d",xiaoxi.response.ack);
        }
        else
        {
            ROS_INFO("failed!!!!!!");
        }
    }
    else if(atoi(argv[1]) == 5)
    {
        ros::ServiceClient client = n.serviceClient<ttauav_node::gimbalControl>("gimbalControl");

        ttauav_node::gimbalControl xiaoxi ;
 
        xiaoxi.request.pitch = atof(argv[2]);
        xiaoxi.request.yaw = 0.0;

        bool tiaojian = client.call(xiaoxi);
        if(tiaojian)
        {
            ROS_INFO("success!!!!!");
            ROS_INFO("result：%d",xiaoxi.response.ack);
        }
        else
        {
            ROS_INFO("failed!!!!!!");
        }
    }
    else
    {
        ros::ServiceClient client = n.serviceClient<ttauav_node::takeoffOrLanding>("takeoffOrLanding");

        ttauav_node::takeoffOrLanding xiaoxi ;
        xiaoxi.request.takeoffOrLanding = atoi(argv[1]);

        bool tiaojian = client.call(xiaoxi);
        if(tiaojian)
        {
            ROS_INFO("success!!!!!");
            ROS_INFO("result：%d",xiaoxi.response.ack);
        }
        else
        {
            ROS_INFO("failed!!!!!!");
        }
    }

    
    return 0;
}
