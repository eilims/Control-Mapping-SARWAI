/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ros/init.h"


#include <ros/ros.h>
#include <move_base_logger/MoveBaseLogger.hpp>

int main(int argc, char** argv){
    ros::init(argc, argv, "move_base_logger");
    MoveBaseLogger mbl;
    mbl.run();
}

