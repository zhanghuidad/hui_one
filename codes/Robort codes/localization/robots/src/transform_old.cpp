#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_broadcaster.h>

void scanCallback(sensor_msgs::LaserScan msg)
{
	msg.header.frame_id = "base_link";
}
    
geometry_msgs::TransformStamped odom_trans;   
bool odom_trans_flag = false;
	    
void odomCallback(nav_msgs::Odometry msg)
{
	odom_trans.header = msg.header;
	odom_trans.transform.translation.x = msg.pose.pose.position.x;
	odom_trans.transform.translation.y = msg.pose.pose.position.y;
	odom_trans.transform.translation.z = msg.pose.pose.position.z;
	odom_trans.transform.rotation = msg.pose.pose.orientation;
	//odom_trans.transform = msg.pose.pose;
	odom_trans_flag = true;
}

double getParam(ros::NodeHandle nh,std::string str,double def = 0.0)
{
	double T;
	nh.param<double>(str,T,def);
	return T;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    
    ros::Subscriber scan = n.subscribe<sensor_msgs::LaserScan>("scan",1,scanCallback);
    ros::Subscriber odom = n.subscribe<nav_msgs::Odometry>("odom",1,odomCallback);
    
    ros::Publisher initial_pose = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 10);
    
    tf::TransformBroadcaster broadcaster;
    
    // message declarations

    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";
    
    geometry_msgs::PoseWithCovarianceStamped initialpose_;

	initialpose_.header.stamp = ros::Time::now();
	initialpose_.header.frame_id = "map";
	
	memset(&(initialpose_.pose),sizeof(initialpose_.pose),0.0);
	
	n.param<double>("initial_pose_x",initialpose_.pose.pose.position.x,0.0);
	n.param<double>("initial_pose_y",initialpose_.pose.pose.position.y,0.0);
	n.param<double>("initial_pose_a",initialpose_.pose.pose.orientation.z,0.0);  
	
	n.param<double>("initial_cov_xx",initialpose_.pose.covariance[6*0+0],0.5*0.5);
	n.param<double>("initial_cov_yy",initialpose_.pose.covariance[6*1+1],0.5*0.5);
	n.param<double>("initial_cov_zz",initialpose_.pose.covariance[6*5+5],0.25*0.25);

	//initialpose_.pose.pose.position.x = getParam(n,"initial_pose_x",0.0)  
    ros::Rate loop_rate(30);

    while (ros::ok())
    {
  		  	
    	if(odom_trans_flag)
    	{        
        	broadcaster.sendTransform(odom_trans);
        	odom_trans_flag = false;
        	
        	initial_pose.publish(initialpose_);
        	
        	ROS_INFO_STREAM("odom publish ok!");
        }
		
		ros::spinOnce();
    }


    return 0;
}
