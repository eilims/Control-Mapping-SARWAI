/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveBaseLogger.hpp
 * Author: serl
 *
 * Created on November 18, 2017, 2:03 PM
 */

#ifndef MOVEBASELOGGER_HPP
#define MOVEBASELOGGER_HPP

#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalStatus.h>
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

class MoveBaseLogger {
public:
    MoveBaseLogger();
    ~MoveBaseLogger();
    
    void run();
    
    void updateTwist(const geometry_msgs::Twist& msg);
    
    void updateGoalStatus(const actionlib_msgs::GoalStatus& msg);
    
    void updateFeedback(const move_base_msgs::MoveBaseActionFeedback& msg);
    
    void updateResult(const move_base_msgs::MoveBaseActionResult& msg);
    
private:
    
    void createFile(std::string* fileName);
    bool fileExists(std::string filename);
    geometry_msgs::Twist twistMsg;
    actionlib_msgs::GoalStatus goalStatusMsg;
    move_base_msgs::MoveBaseActionFeedback feedbackMsg;
    move_base_msgs::MoveBaseActionResult resultMsg; 
};

#endif /* MOVEBASELOGGER_HPP */

