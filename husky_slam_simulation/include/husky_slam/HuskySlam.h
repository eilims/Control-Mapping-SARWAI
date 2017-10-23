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

#include <tf/tfMessage.h>

/* Implementation below :
 *  HuskySlam thingy;
 *  thingy.run();
 * 
 * This class is self containted and can be run on anywhere on ros as it 
 * generates a unique node. 
 * 
 * This node serves to redirect the information required by google cartographer
 * and Gazebo husky simulation. 
 */


class HuskySlam {
 public:

  //Constructors and Deconsructors
  HuskySlam();
  ~HuskySlam();

  //Main methods
  void run();

  //Callback methods
  void updateTF(const tf::tfMessage& msg);

  void parseTF();


 private:
  tf::tfMessage tf;
  int sec;
  int nsec;
};

#endif /* HUSKYSLAM_H */

