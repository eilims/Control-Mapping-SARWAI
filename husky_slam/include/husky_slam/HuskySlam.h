/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuskySlam.h
 * Author: serl
 *
 * Created on September 10, 2017, 3:26 PM
 */

#ifndef HUSKYSLAM_H
#define HUSKYSLAM_H

#include <nav_msgs/Odometry.h>

class HuskySlam {
 public:
  HuskySlam();
  ~HuskySlam();
  void run();
  void updateOdom(const nav_msgs::Odometry& msg);


 private:
  nav_msgs::Odometry odom;
};

#endif /* HUSKYSLAM_H */

