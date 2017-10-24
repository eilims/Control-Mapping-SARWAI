/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ros/ros.h>
#include <husky_slam/HuskySlam.h>

HuskySlam::HuskySlam()
{
    this->sec = 0;
    this->nsec = 0;
    this->tf.transforms.resize(1);
    //Header assignments
    this->tf.transforms[0].header.seq = 0;
    this->tf.transforms[0].header.stamp.sec = this->sec;
    this->tf.transforms[0].header.stamp.nsec = this->nsec;
    this->tf.transforms[0].header.frame_id = "odom";
    this->tf.transforms[0].child_frame_id = "base_link";
    this->tf.transforms[0].transform.translation.x = 0;
    this->tf.transforms[0].transform.translation.y = 0;
    this->tf.transforms[0].transform.translation.z = 0;
    this->tf.transforms[0].transform.rotation.x = 0;
    this->tf.transforms[0].transform.rotation.y = 0;
    this->tf.transforms[0].transform.rotation.z = 0;
    this->tf.transforms[0].transform.rotation.w = 1;
}

HuskySlam::~HuskySlam()
{
}

//We must republish odometry to the correct topic /tf, which google cartographer uses
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
        parseTF();
        tfPub.publish(this->tf);
        ros::spinOnce();
        rate.sleep();
    }
}

//Called when a message from /tf is recieved.
//We have to parse throughthe times to ensure the transform is valid
void HuskySlam::updateTF(const tf::tfMessage& msg)
{
    if ((msg.transforms[0].header.stamp.sec >= this->sec) && (msg.transforms[0].header.stamp.nsec >= this->nsec))
    {
        this->sec = msg.transforms[0].header.stamp.sec;
        this->nsec = msg.transforms[0].header.stamp.nsec;
        this->tf = msg;
        
    }
}

void HuskySlam::parseTF()
{
    //We have to go through each transform and change base_link to test_link
    for(int i = 0; i < sizeof(this->tf)/sizeof(this->tf.transforms[0]); i++)
    {
        if (this->tf.transforms[i].child_frame_id == "base_link")
        {
            this->tf.transforms[i].child_frame_id = "test_link";
        }
    }
}
