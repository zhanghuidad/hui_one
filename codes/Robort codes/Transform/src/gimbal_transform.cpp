#include "gimbal_transform.h"
void transform::GimbalAngleCallback(const rm_msgs::GimbalAngle::ConstPtr &gimbal_angle_msg)
{
	ros::Time current_time = ros::Time::now();
  geometry_msgs::Quaternion q = tf::createQuaternionMsgFromRollPitchYaw(0.0,gimbal_angle_msg->pitch_angle,gimbal_angle_msg->yaw_angle);
  gimbal_tf_.header.stamp = current_time;
  gimbal_tf_.transform.rotation = q;
  gimbal_tf_.transform.translation.x = 0;
  gimbal_tf_.transform.translation.y = 0;
  gimbal_tf_.transform.translation.z = 0.15;
	tf_broadcaster_.sendTransform(gimbal_tf_);
}
transform::transform(ros::NodeHandle& nh)
{
	gimbal_sub = nh.subscribe<rm_msgs::GimbalAngle>("/gimbal_angle",10,&transform::GimbalAngleCallback,this);
	ROS_INFO("Tranform node is OK");
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "Transform");
  ros::NodeHandle nh;
  transform tr(nh);
  ros::spin();
  return 0;
}
//TODO:test,change msgs,add base-world frame
