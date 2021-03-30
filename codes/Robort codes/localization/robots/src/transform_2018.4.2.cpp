#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_broadcaster.h>

#define pi 3.1415926

geometry_msgs::TransformStamped odom_trans;
nav_msgs::Odometry odom_first;
bool odom_first_flag = false;
bool odom_trans_flag = false;
	    
void odomCallback(nav_msgs::Odometry msg)
{
	if(!odom_first_flag)
	{
		odom_first = msg;
		odom_first.pose.pose.orientation.w = odom_first.pose.pose.orientation.w;
		odom_first.pose.pose.orientation.x = -odom_first.pose.pose.orientation.x;
		odom_first.pose.pose.orientation.y = -odom_first.pose.pose.orientation.y;
		odom_first.pose.pose.orientation.z = -odom_first.pose.pose.orientation.z;
		odom_first_flag =true;
	}
	odom_trans.header.stamp = msg.header.stamp;
	odom_trans.transform.translation.x = msg.pose.pose.position.x - odom_first.pose.pose.position.x;
	odom_trans.transform.translation.y = msg.pose.pose.position.y - odom_first.pose.pose.position.y;
	odom_trans.transform.translation.z = msg.pose.pose.position.z - odom_first.pose.pose.position.z;

	//odom_trans.transform.rotation = msg.pose.pose.orientation;

	double x,y,z,w;
	double q0,q1,q2,q3,qTOangle_yaw;

/*	w = msg.pose.pose.orientation.w*odom_first.pose.pose.orientation.w - msg.pose.pose.orientation.x*odom_first.pose.pose.orientation.x -\
	msg.pose.pose.orientation.y*odom_first.pose.pose.orientation.y - msg.pose.pose.orientation.z*odom_first.pose.pose.orientation.z;

	x = odom_first.pose.pose.orientation.w*msg.pose.pose.orientation.x + odom_first.pose.pose.orientation.x*msg.pose.pose.orientation.w +\
	odom_first.pose.pose.orientation.y*msg.pose.pose.orientation.z - odom_first.pose.pose.orientation.z*msg.pose.pose.orientation.y;

	y = odom_first.pose.pose.orientation.w*msg.pose.pose.orientation.y + odom_first.pose.pose.orientation.y*msg.pose.pose.orientation.w +\
	odom_first.pose.pose.orientation.z*msg.pose.pose.orientation.x - odom_first.pose.pose.orientation.x*msg.pose.pose.orientation.z;

	z = odom_first.pose.pose.orientation.w*msg.pose.pose.orientation.z + odom_first.pose.pose.orientation.z*msg.pose.pose.orientation.w +\
	odom_first.pose.pose.orientation.x*msg.pose.pose.orientation.y - odom_first.pose.pose.orientation.y*msg.pose.pose.orientation.x;
	
	odom_trans.transform.rotation.x = x;
	odom_trans.transform.rotation.y = y;	
	odom_trans.transform.rotation.z = z;
	odom_trans.transform.rotation.w = w;
*/
	//odom_trans.transform = msg.pose.pose;
	
	q0 = msg.pose.pose.orientation.x;
	q1 = msg.pose.pose.orientation.y;
	q2 = msg.pose.pose.orientation.z;
	q3 = msg.pose.pose.orientation.w;

	qTOangle_yaw = atan2(2*q1*q2+2*q0*q3,-2*q2*q2-2*q3*q3+1)*57.3f;
	///std::cout<<"qTOangle_yaw----"<<qTOangle_yaw<<std::endl;
	odom_trans.transform.rotation.x = q0;
	odom_trans.transform.rotation.y = q1;	
	odom_trans.transform.rotation.z = q2;
	odom_trans.transform.rotation.w = 100;//qTOangle_yaw;//msg.pose.pose.orientation.w;

	odom_trans_flag = true;
}

geometry_msgs::TransformStamped odomMapTrans;
geometry_msgs::PoseWithCovarianceStamped amclMsg;
bool odomMapTransFlag = false;
void amclPoseCallback(geometry_msgs::PoseWithCovarianceStamped msg)
{
	amclMsg = msg;
	geometry_msgs::Transform amclPose;

	amclPose.translation.x = msg.pose.pose.position.x;
	amclPose.translation.y = msg.pose.pose.position.y;
	amclPose.translation.z = msg.pose.pose.position.z;

	amclPose.rotation = msg.pose.pose.orientation;
	
	odomMapTrans.header = msg.header;

	odomMapTrans.header.frame_id = "map";
	odomMapTrans.child_frame_id = "base_link";

	odomMapTrans.transform.translation.x = msg.pose.pose.position.x;
	odomMapTrans.transform.translation.y = msg.pose.pose.position.y;
	odomMapTrans.transform.translation.z = msg.pose.pose.position.z;

	odomMapTrans.transform.rotation = msg.pose.pose.orientation;	

	odomMapTransFlag = true;
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
    
    //ros::Subscriber scan = n.subscribe<sensor_msgs::LaserScan>("scan",1,scanCallback);
    ros::Subscriber odom = n.subscribe<nav_msgs::Odometry>("odom",1,odomCallback);
    ros::Subscriber pose_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",1,amclPoseCallback);

    ros::Publisher initial_pose = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 10);
   
    tf::TransformBroadcaster broadcaster;
    
    // message declarations

    odom_trans.header.frame_id = "odom_base";
    odom_trans.child_frame_id = "base_link";
    
    geometry_msgs::PoseWithCovarianceStamped initialpose_;

	initialpose_.header.stamp = ros::Time::now();
	initialpose_.header.frame_id = "map";

	geometry_msgs::TransformStamped laser_base_broad;

	tf::Transform laser_base_trans;
    laser_base_trans.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
    tf::Quaternion laser_base_q;
    laser_base_q.setRPY(0, 0, 0);
    laser_base_trans.setRotation(laser_base_q);  
	
	memset(&(initialpose_.pose),sizeof(initialpose_.pose),0.0);
	
	n.param<double>("initial_pose_x",initialpose_.pose.pose.position.x,4.5);
	n.param<double>("initial_pose_y",initialpose_.pose.pose.position.y,1.5);
	n.param<double>("initial_pose_a",initialpose_.pose.pose.orientation.z,0.707);  
	n.param<double>("initial_pose_a",initialpose_.pose.pose.orientation.w,0.707); 
	
	n.param<double>("initial_cov_xx",initialpose_.pose.covariance[6*0+0],0.2*0.2);
	n.param<double>("initial_cov_yy",initialpose_.pose.covariance[6*1+1],0.2*0.2);
	n.param<double>("initial_cov_zz",initialpose_.pose.covariance[6*5+5],0.2*0.2);

	//initialpose_.pose.pose.position.x = getParam(n,"initial_pose_x",0.0)  
    ros::Rate loop_rate(30);

	ROS_INFO_STREAM("odom publish ok!");

	bool flag = false;

    while (ros::ok())
    {
  		if(!flag)
		{
			if(odomMapTransFlag){
				flag = true;
			}
			else{
				initialpose_.header.stamp = ros::Time::now();
       		 	initial_pose.publish(initialpose_);  
			}
		}  	
    	if(true || odom_trans_flag)
    	{        
        	broadcaster.sendTransform(odom_trans);
        	odom_trans_flag = false;
        	
        	broadcaster.sendTransform(tf::StampedTransform(laser_base_trans, ros::Time::now(), "base_link","laser")); 	
        }
		if(odomMapTransFlag){
			//broadcaster.sendTransform(odomMapTrans);
			odomMapTransFlag = false;

			memset(&(initialpose_.pose),sizeof(initialpose_.pose),0.0);
			initialpose_.pose.pose.position.x = odomMapTrans.transform.translation.x;
			initialpose_.pose.pose.position.y = odomMapTrans.transform.translation.y;
			initialpose_.pose.pose.orientation.z = odomMapTrans.transform.rotation.z;
			initialpose_.pose.pose.orientation.w = odomMapTrans.transform.rotation.w;
			initialpose_.header.stamp = ros::Time::now();
			//initialpose_.pose.covariance = amclMsg.pose.covariance;
        	initial_pose.publish(initialpose_);       
		}

		ros::spinOnce();
    }


    return 0;
}
