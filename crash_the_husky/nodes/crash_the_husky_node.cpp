/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ros/ros.h>
#include "crash_the_husky/CrashTheHusky.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "crash_the_husky");
    CrashTheHusky node1; 
    node1.run();
}
