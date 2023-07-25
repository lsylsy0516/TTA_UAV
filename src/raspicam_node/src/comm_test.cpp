#include "ros/ros.h"
#include "ttauav_node/action.h"

void doMsg(const ttauav_node::action::ConstPtr& a_p){
    ROS_INFO("n=   %f",a_p->n);
    ROS_INFO("e=   %f",a_p->e);
    ROS_INFO("d=   %f",a_p->d);
    ROS_INFO("yaw= %f",a_p->yaw);
    ROS_INFO("FUCKU!");
}

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"action_test");
    ros::NodeHandle nh;
    ROS_INFO("node start!");
    ros::Subscriber sub = nh.subscribe<ttauav_node::action>("action",100,doMsg);
    ros::Rate r(10);
    while(1){
        ros::spinOnce();
        ROS_INFO("node working");
        r.sleep();
    }
    return 0;
}  
