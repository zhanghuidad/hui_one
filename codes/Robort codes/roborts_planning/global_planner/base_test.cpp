#include "ros/ros.h"
#include <iostream>
#include "geometry_msgs/Twist.h"
int main(int argc,char **argv)
{
	ros::init(argc,argv,"base_test");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Rate rate(10);
	int mode = 0;
	int  counter =0;
	geometry_msgs::Twist test;
	while(ros::ok())
	{
		ros::spinOnce();
		if(mode==0)
		{
			counter++;
			if(counter>=50)
			{
					mode=1;
					counter=0;
			}
			else
			{
				test.linear.x=0.2;
				test.linear.y=0.;
			}
		}
		else if(mode==1)
		{
			counter++;
			if(counter>=50)
			{
					mode=2;
					counter=0;
			}
			else
			{
				test.linear.y=0.2;
				test.linear.x=0.;
			}
		}
		else if(mode==2)
		{
			counter++;
			if(counter>=50)
			{
					mode=0;
					counter=0;
			}
			else
			{
				test.linear.y=-0.2;
				test.linear.x=-0.2;
			}
		}
		test.angular.z=0.0;
		chatter_pub.publish(test);
		ros::spinOnce();
		rate.sleep();
	}
}
