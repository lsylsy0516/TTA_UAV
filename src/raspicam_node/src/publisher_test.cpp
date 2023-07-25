/*
    需求: 循环发布人的信息

*/

#include "ros/ros.h"
#include "ttauav_node/action.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    //1.初始化 ROS 节点
    ros::init(argc,argv,"action_publisher");

    //2.创建 ROS 句柄
    ros::NodeHandle nh;

    //3.创建发布者对象
    ros::Publisher pub = nh.advertise<ttauav_node::action>("action",1000);

    //4.组织被发布的消息，编写发布逻辑并发布消息
    ttauav_node::action a;
    a.yaw = 20;

    ros::Rate r(10);
    while (ros::ok())
    {
        pub.publish(a);
        ros::spinOnce();
        r.sleep();
    }



    return 0;
}
