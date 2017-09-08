/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ros/ros.h>
#include <husky_slam/HuskySlam.h>

HuskySlam::HuskySlam()
{


}

HuskySlam::~HuskySlam()
{
}

void HuskySlam::run()
{
    ros::NodeHandle nh;
    ros::Publisher odomPub = nh.advertise<nav_msgs::Odometry>("odom", 1000);
    ros::Subscriber odomSub = nh.subscribe("odometry/filtered", 1000, &HuskySlam::updateOdom, this);
    ros::Rate rate(50);

    while (ros::ok())
    {
        ROS_INFO_STREAM("Transmitting");
        odomPub.publish(this->odom);
        ros::spinOnce();
        rate.sleep();
    }
}

void HuskySlam::updateOdom(const nav_msgs::Odometry& msg)
{
    ROS_INFO_STREAM("testing");
    this->odom = msg;
}