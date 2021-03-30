#include "ros/ros.h"
#include "ros/package.h"
#include <iostream>
#include <string>
#include <io/io.h>
#include "rm_msgs/GimbalAngle.h"
#include <tf/transform_broadcaster.h>
#include <boost/bind.hpp>
#include <geometry_msgs/TransformStamped.h>
class transform
{
	public:
		geometry_msgs::TransformStamped gimbal_tf_;
		transform(ros::NodeHandle& nh);//Can not add Const! Or "error:can not find function...."
	private:
		ros::Subscriber gimbal_sub;
		tf::TransformBroadcaster tf_broadcaster_;
		//void GimbalAngleCallback(const rm_msgs::GimbalAngleConstPtr &gimbal_angle_msg);
		void GimbalAngleCallback(const rm_msgs::GimbalAngle::ConstPtr &gimbal_angle_msg);
};
