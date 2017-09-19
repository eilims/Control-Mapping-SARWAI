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

//We must republish odometry to the correct topic /odom, which google cartographer uses
void HuskySlam::run()
{
    ros::NodeHandle nh;
    //Publishers
    ros::Publisher odomPub = nh.advertise<nav_msgs::Odometry>("odom", 1000);
    //Subscribers
    ros::Subscriber odomSub = nh.subscribe("odometry/filtered", 1000, &HuskySlam::updateOdom, this);
    //Set publishing speed to 50Hz
    ros::Rate rate(50);

    while (ros::ok())
    {
        odomPub.publish(this->odom);
        ros::spinOnce();
        rate.sleep();
    }
}

//Called when a message from /odometry/filtered is recieved.
void HuskySlam::updateOdom(const nav_msgs::Odometry& msg)
{
    this->odom = msg;
}