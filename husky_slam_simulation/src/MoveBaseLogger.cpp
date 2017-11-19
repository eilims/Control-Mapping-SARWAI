/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "move_base_logger/MoveBaseLogger.hpp"
#include "ros/node_handle.h"

MoveBaseLogger::MoveBaseLogger() {

}

MoveBaseLogger::~MoveBaseLogger() {}

void MoveBaseLogger::run(){
    ros::NodeHandle nh;

    ros::Subscriber twistSub = nh.subscribe("cmd_vel", 1000, &MoveBaseLogger::updateTwist, this);
    ros::Subscriber goalStatusSub = nh.subscribe("move_base/status", 1000, &MoveBaseLogger::updateGoalStatus, this);
    ros::Subscriber feedbackSub = nh.subscribe("move_base/feedback", 1000, &MoveBaseLogger::updateFeedback, this);
    ros::Subscriber resultSub = nh.subscribe("move_base/result", 1000, &MoveBaseLogger::updateResult, this);

    ros::Rate rate(100);
    
    int index = 0;
    std::string twistFileName = "/home/serl/Documents/CONTROL_LOGS/Move_Base_Log_Twist";
    std::string goalStatusFileName = "/home/serl/Documents/CONTROL_LOGS/Move_Base_Log_Goal_Status";
    std::string feedbackFileName = "/home/serl/Documents/CONTROL_LOGS/Move_Base_Log_Feedback";
    std::string resultFileName = "/home/serl/Documents/CONTROL_LOGS/Move_Base_Log_Result";
    
    createFile(&twistFileName);
    createFile(&goalStatusFileName);
    createFile(&feedbackFileName);
    createFile(&resultFileName);
    
    ROS_INFO_STREAM(twistFileName);
    ROS_INFO_STREAM(goalStatusFileName);
    ROS_INFO_STREAM(feedbackFileName);
    ROS_INFO_STREAM(resultFileName);
    
    std::ofstream twistLog(twistFileName);
    std::ofstream goalStatusLog(goalStatusFileName);
    std::ofstream feedbackLog(feedbackFileName);
    std::ofstream resultLog(resultFileName);
    
    while(ros::ok()){
        twistLog << "Index: " << index << " value: " << this->twistMsg << std::endl;
        goalStatusLog << "Index: " << index << " value: " << this->goalStatusMsg << std::endl;
        feedbackLog << "Index: " << index << " value: " << this->feedbackMsg << std::endl;
        resultLog << "Index: " << index << " value: " << this->resultMsg << std::endl;
        index++;
        ros::spinOnce();
    }
}

void MoveBaseLogger::updateTwist(const geometry_msgs::Twist& msg){
    this->twistMsg = msg;
}

void MoveBaseLogger::updateGoalStatus(const actionlib_msgs::GoalStatus& msg){
    this->goalStatusMsg = msg;
}

void MoveBaseLogger::updateFeedback(const move_base_msgs::MoveBaseActionFeedback& msg){
    this->feedbackMsg = msg;
}

void MoveBaseLogger::updateResult(const move_base_msgs::MoveBaseActionResult& msg){
    this->resultMsg = msg;
}

void MoveBaseLogger::createFile(std::string* fileName){
    char index = '1';
    while (fileExists(*fileName + ".txt")){
        *fileName += index;
        index++;
    }
    *fileName += ".txt";
}

bool MoveBaseLogger::fileExists(std::string filename){
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}
