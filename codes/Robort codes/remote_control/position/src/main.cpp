//说明：本程序用于接收UDP数据包，远程遥控机器人运动
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ros/ros.h>
#include <vector>
#include <rm_msgs/Odometry.h>//ROS消息文件,轮式里程计数据
#include <sensor_msgs/LaserScan.h>//ROS消息文件,激光雷达数据



using namespace std;

float attitude_raw[3] = {0,0,0};//轮式里程计数据(0 位置X；1 位置Y；2 角度)
ros::Time attitude_raw_time;//轮式里程计数据时间戳
float attitude_real[3] = {0,0,0};//真实位姿数据(0 位置X；1 位置Y；2 角度)
sensor_msgs::LaserScan laserscan_rawData;//激光雷达原始数据
bool laser_ready_flag = false;//激光雷达数据更新标志位

float calculateError(sensor_msgs::LaserScan laserscanData, float attitude[3]);//判断定位误差
void scanCallback(sensor_msgs::LaserScan msg)//激光雷达数据输入
{
	laserscan_rawData.header.stamp = msg.header.stamp;//时间戳
	laserscan_rawData.angle_min = msg.angle_min;//最小角度
	laserscan_rawData.angle_max = msg.angle_max;//最大角度
	laserscan_rawData.angle_increment = msg.angle_increment;//每个样点角度增量
	laserscan_rawData.time_increment = msg.time_increment;//每个样点时间增量
	laserscan_rawData.scan_time = msg.scan_time;//总采样时间
	laserscan_rawData.range_min = msg.range_min;//距离最小值
	laserscan_rawData.range_max = msg.range_max;//距离最大值
	laserscan_rawData.ranges.assign(msg.ranges.begin(),msg.ranges.end());//距离数组
	laserscan_rawData.intensities.assign( msg.intensities.begin(), msg.intensities.end());//强度数组
	laser_ready_flag = true;
}

void odomCallback(rm_msgs::Odometry msg)//轮式里程计数据输入
{
	float timePassed = (msg.header.stamp - attitude_raw_time).toSec();//距离上次里程计数据更新时间（秒）
	float x = msg.pose.pose.orientation.x;//角度四元数X
	float y = msg.pose.pose.orientation.y;//角度四元数X
	float z = msg.pose.pose.orientation.z;//角度四元数X
	float w = msg.pose.pose.orientation.w;//角度四元数X
	float angle_raw_new = atan2(2*(w*z+x*y),1-2*(y*y+z*z));//偏航角
	if(timePassed < 1.0)//时间正常，数据更新有效，累加
	{
		if(fabs(msg.pose.pose.position.x - attitude_raw[0]) < 1.0) attitude_real[0] += (msg.pose.pose.position.x - attitude_raw[0]) * cos(attitude_raw[2] - attitude_real[2]);//X方向数据有效（不是乱码），累加到真实数据中
		if(fabs(msg.pose.pose.position.y - attitude_raw[1]) < 1.0) attitude_real[1] += (msg.pose.pose.position.y - attitude_raw[1]) * sin(attitude_raw[2] - attitude_real[2]);//Y方向数据有效（不是乱码），累加到真实数据中
		if(fabs(angle_raw_new - attitude_raw[2]) < 20.0) attitude_real[2] += (angle_raw_new - attitude_raw[2]);//角度数据有效（不是乱码），累加到真实数据中
	}
	attitude_raw_time = msg.header.stamp;//更新时间戳
	attitude_raw[0] = msg.pose.pose.position.x;//更新位置X
	attitude_raw[1] = msg.pose.pose.position.y;//更新位置Y
	attitude_raw[2] = angle_raw_new;//更新偏航角
}





int main(int argc, char** argv)
{
	unsigned int loopCounter = 0;
	//cout << laserscan_rawData.ranges << endl;
	ros::init(argc, argv, "position_XR");
	ros::NodeHandle my_node;
	ros::Subscriber scan = my_node.subscribe<sensor_msgs::LaserScan>("/scan",10,scanCallback);
    ros::Subscriber odom = my_node.subscribe<rm_msgs::Odometry>("/odom",10,odomCallback);
	while(ros::ok())
	{
		ros::spinOnce();//获取数据
		if(loopCounter++ % 1000 == 0) printf("%f\t%f\t%f\t%f\t%f\t%f\r\n",attitude_real[0],attitude_real[1],attitude_real[2],attitude_raw[0],attitude_raw[1],attitude_raw[2]);
		usleep(1000);//sleep for 1ms
		//usleep(1000000);//sleep for 1000ms
	}
	return 0;
}




float calculateError(sensor_msgs::LaserScan laserscanData, float attitude[3])
{
	float errorValue = 0;
	for(int i = 0; i < laserscanData.ranges.size(); i++)
	{
		if(laserscanData.ranges[i] > 0.3 && laserscanData.ranges[i] < 8.0)//激光雷达目标有效
		{
			float X = attitude[0] + laserscanData.ranges[i] * sin(attitude[2] * (float)0.01745329252 + (float)3.14159265 + (laserscanData.angle_min + i * laserscanData.angle_increment));//激光雷达目标点在场地内的真实坐标X
			float Y = attitude[1] + laserscanData.ranges[i] * cos(attitude[2] * (float)0.01745329252 + (float)3.14159265 + (laserscanData.angle_min + i * laserscanData.angle_increment));//激光雷达目标点在场地内的真实坐标Y
			if(X < 0.1)
			{

			}
			else if(X > 7.9)
			{

			}
			else if(Y > 0.1)
			{

			}
			else if(Y < 4.9)
			{

			}


			errorValue += ;
		}
		
	}

}







