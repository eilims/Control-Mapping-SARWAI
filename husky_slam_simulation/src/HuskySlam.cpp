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
    ros::Publisher tfPub = nh.advertise<tf::tfMessage>("tf", 1000);
    //Subscribers
    ros::Subscriber tfSub = nh.subscribe("tf", 1000, &HuskySlam::updateTF, this);
    //Set publishing speed to 50Hz
    ros::Rate rate(100);

    while (ros::ok())
    {
        tfPub.publish(this->tf);
        ros::spinOnce();
        rate.sleep();
    }
}

//Called when a message from /odometry/filtered is recieved.
void HuskySlam::updateTF(const tf::tfMessage& msg)
{
    this->tf = msg;
}
