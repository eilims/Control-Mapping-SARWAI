/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrashTheHusky.h
 * Author: Daniel Benusovich
 *
 * Created on July 11, 2017, 8:20 PM
 */

#ifndef CRASHTHEHUSKY_H
#define CRASHTHEHUSKY_H

#include <string>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <tf/tfMessage.h>
#include <vehicle/position.h>
#include <vehicle/vehicle_control.h>
#include <sensor_msgs/LaserScan.h>
/*
 Note that vehicle control uses the names space gcs
 */

class CrashTheHusky
{
public: 
    
    // Setup functions
    CrashTheHusky();
    virtual ~CrashTheHusky();
    void run();
    
    //Callback functions
    void updateMap(const nav_msgs::OccupancyGrid& msg);
    void updateTF(const tf::tfMessage& msg);
    void updateOdom(const nav_msgs::Odometry& msg);
    void updateLaser(const sensor_msgs::LaserScan& msg);
    
    // Getter functions
    gcs::Position getRobotPosition();
    nav_msgs::OccupancyGrid getMap();
    tf::tfMessage getTFMessage();
    
private:
    gcs::Position robotPosition;
    nav_msgs::OccupancyGrid map;
    nav_msgs::Odometry odom;
    sensor_msgs::Imu imu;
    tf::tfMessage tfMessage;
    sensor_msgs::LaserScan laserScan;
};


#endif /* CRASHTHEHUSKY_H */

