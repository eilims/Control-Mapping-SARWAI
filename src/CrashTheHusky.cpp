
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <crash_the_husky/CrashTheHusky.h>
#include <ros/ros.h>




CrashTheHusky::CrashTheHusky() 
{
    
    //Set to anything greater than 0 for google
    this->laserScan.angle_increment = 0;
    this->laserScan.angle_max = 1;
    this->laserScan.angle_increment = 1;
    this->laserScan.time_increment = 1;
    this->laserScan.scan_time = 1;
    this->laserScan.range_min = .001;
    this->laserScan.range_max = 50;
}
    
    

CrashTheHusky::~CrashTheHusky()
{

}

void CrashTheHusky::run()
{
    ros::NodeHandle nh;
    
    ros::Rate rate(50);
    
    // Publishers used to route data to the proper topics. 
    // Thanks google. You bitch
    ros::Publisher sendOdom = nh.advertise<nav_msgs::Odometry>("/odom", 1000);
    
    
    //Covariance required by google cartographer to do anything
    //Set once and never change
    ros::Publisher sendIMU = nh.advertise<sensor_msgs::Imu>("imu", 1000);
    
    //Resend laser so that google is happy with the send rate
    ros::Publisher sendLaser= nh.advertise<sensor_msgs::LaserScan>("scan", 1000);
    
    // Gmapping subs
    //Creating all the subscribers needed for getting map and data
    
    //Subscriber for actual map. Recieve list of all cells in ROW MAJOR ORDER
    // Also contains: meter/cell, width of map, length of map, and origin in map meta data
    ros::Subscriber map = nh.subscribe("map", 1000, &CrashTheHusky::updateMap, this);
    
    //Subscriber for tf information. 
    // IE where we are facing (orientation) and where are we on the map (Translation)
    ros::Subscriber pose = nh.subscribe("tf", 1000, &CrashTheHusky::updateTF, this);
    
    //Get odom data from original source. This will be rerouted to Google Cart. 
    ros::Subscriber odometry = nh.subscribe("/odometry/filtered", 1000, &CrashTheHusky::updateOdom, this);
    
    
    
    while(ros::ok())
    {
        sendOdom.publish(this->odom);
        sendIMU.publish(this->imu);
        //sendLaser.publish(this->laserScan);
        ros::spinOnce();
        rate.sleep();
    }
}

void CrashTheHusky::updateMap(const nav_msgs::OccupancyGrid& msg)
{
    this->map = msg;
}


void CrashTheHusky::updateTF(const tf::tfMessage& msg)
{
    this->tfMessage = msg;
}

void CrashTheHusky::updateOdom(const nav_msgs::Odometry& msg)
{
    //Do not publish here, this is an interrupt do not waste time
    this->odom = msg;
    //Converting nav_msgs::Odometry IMU portion to sensor_msgs::imu
    //Required for cartographer. At least for now, the odometry only appraoch does not function
    this->imu.angular_velocity = this->odom.twist.twist.angular;
    this->imu.linear_acceleration = this->odom.twist.twist.linear;
    this->imu.orientation = this->odom.pose.pose.orientation;
    this->imu.linear_acceleration_covariance =  {   this->odom.twist.covariance[0], this->odom.twist.covariance[2], this->odom.twist.covariance[3],
                                                    this->odom.twist.covariance[6], this-> odom.twist.covariance[7], this->odom.twist.covariance[8],
                                                    this->odom.twist.covariance[12], this->odom.twist.covariance[13], this->odom.twist.covariance[14]};
    
    this->imu.angular_velocity_covariance =     {   this->odom.twist.covariance[21], this->odom.twist.covariance[22], this->odom.twist.covariance[23],
                                                    this->odom.twist.covariance[27], this-> odom.twist.covariance[28], this->odom.twist.covariance[29],
                                                    this->odom.twist.covariance[33], this->odom.twist.covariance[34], this->odom.twist.covariance[35]};
    
    this->imu.orientation_covariance =          {   this->odom.pose.covariance[21], this->odom.pose.covariance[22], this->odom.pose.covariance[23],
                                                    this->odom.pose.covariance[27], this-> odom.pose.covariance[28], this->odom.pose.covariance[29],
                                                    this->odom.pose.covariance[33], this->odom.pose.covariance[34], this->odom.pose.covariance[35]};
}

void CrashTheHusky::updateLaser(const sensor_msgs::LaserScan& msg)
{
    this->laserScan = msg;
}

nav_msgs::OccupancyGrid CrashTheHusky::getMap()
{
    return this->map;
}

tf::tfMessage CrashTheHusky::getTFMessage()
{
    return this->tfMessage;   
}

gcs::Position CrashTheHusky::getRobotPosition()
{
    return this->robotPosition;
    
}

