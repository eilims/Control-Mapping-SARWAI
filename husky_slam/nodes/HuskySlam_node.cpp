/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ros/ros.h>
#include <husky_slam/HuskySlam.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "husky_slam");
    HuskySlam hs;
    hs.run();
}