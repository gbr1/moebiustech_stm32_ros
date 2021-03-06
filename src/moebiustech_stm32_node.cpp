/*
 * The MIT License
 *
 * Copyright (c) 2021 Giovanni di Dio Bruno https://gbr1.github.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <ros/ros.h>
#include <controller_manager/controller_manager.h>
#include <ros/callback_queue.h>

#include "moebiustech_stm32_ros/board_joints.h"
#include <moebiustech_stm32_ros/Drive.h>
#include <moebiustech_stm32_ros/Feedback.h>

int main(int argc, char** argv){
    
    ros::init(argc, argv, "moebiustech_stm32_node");
    ros::NodeHandle nh;
    
    ros::CallbackQueue queue;
    nh.setCallbackQueue(&queue);
    
    BoardJoints bj;
    controller_manager::ControllerManager cm(&bj,nh);

    ros::Subscriber getFeedback = nh.subscribe("/moebiustech_stm32/feedback",1,&BoardJoints::callback,&bj);
    ros::Publisher drive = nh.advertise<moebiustech_stm32_ros::Drive>("/moebiustech_stm32/cmd_drive", 1);
    moebiustech_stm32_ros::Drive msg_drive;

    ros::AsyncSpinner spinner(0, &queue);
    spinner.start();

    ros::Time ts = ros::Time::now();

    ros::Rate rate(50);
    while(ros::ok()){
        ros::Duration d = ros::Time::now()-ts;
        ts = ros::Time::now();
        cm.update(ts,d);
        
        msg_drive.header.stamp= ros::Time::now();
        msg_drive.header.frame_id="base_link";
        msg_drive.drivers[0]=bj.getCommand(0);
        msg_drive.drivers[1]=bj.getCommand(1);

        drive.publish(msg_drive);

        rate.sleep();

    }

    spinner.stop();
    

}
