#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

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
	odom_trans.header.stamp = msg.header.stamp;// + ros::Duration(0.1);
	odom_trans.transform.translation.x = msg.pose.pose.position.x - odom_first.pose.pose.position.x;
	odom_trans.transform.translation.y = msg.pose.pose.position.y - odom_first.pose.pose.position.y;
	odom_trans.transform.translation.z = msg.pose.pose.position.z - odom_first.pose.pose.position.z;

	//odom_trans.transform.rotation = msg.pose.pose.orientation;

	double x,y,z,w;

	w = msg.pose.pose.orientation.w*odom_first.pose.pose.orientation.w - msg.pose.pose.orientation.x*odom_first.pose.pose.orientation.x -\
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

	

	odom_trans_flag = true;
}

geometry_msgs::TransformStamped odomMapTrans;
geometry_msgs::PoseWithCovarianceStamped amclMsg;
bool odomMapTransFlag = false;
bool odomMapTransFlag2 = false;
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
	odomMapTransFlag2 = true;
}

double getParam(ros::NodeHandle nh,std::string str,double def = 0.0)
{
	double T;
	nh.param<double>(str,T,def);
	return T;
}

/*struct TransformListenerWrapper : public tf::TransformListener
{
   inline tf2_ros::Buffer &getBuffer() {return tf2_buffer_;}
};
*/    
int main(int argc, char** argv)
{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    
    //ros::Subscriber scan = n.subscribe<sensor_msgs::LaserScan>("scan",1,scanCallback);
    ros::Subscriber odom = n.subscribe<nav_msgs::Odometry>("odom",1,odomCallback);
    ros::Subscriber pose_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",1,amclPoseCallback);

    ros::Publisher initial_pose = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 10);
    ros::Publisher odom_pose = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("odom_pose",10);
   
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
	
	double initial_z = 0.707;
	double initial_w = 0.707;

	n.param<double>("init_pose_x",initialpose_.pose.pose.position.x,0.8);
	n.param<double>("init_pose_y",initialpose_.pose.pose.position.y,0.8);
	n.param<double>("init_pose_z",initialpose_.pose.pose.orientation.z,initial_z);  
	n.param<double>("init_pose_a",initialpose_.pose.pose.orientation.w,initial_w); 
	
	n.param<double>("init_cov_xx",initialpose_.pose.covariance[6*0+0],0.5*0.5);
	n.param<double>("init_cov_yy",initialpose_.pose.covariance[6*1+1],0.5*0.5);
	n.param<double>("init_cov_zz",initialpose_.pose.covariance[6*5+5],0.2*0.2);

	//initialpose_.pose.pose.position.x = getParam(n,"initial_pose_x",0.0)  
    ros::Rate loop_rate(30);

	ROS_INFO_STREAM("odom publish ok!");

	bool flag = false;

	geometry_msgs::PoseWithCovarianceStamped odompose_;

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
    	if(odom_trans_flag)
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

			double theta1,theta2;

			theta1 = 2*atan2(initial_z,initial_w);
			theta2 = 2*atan2(odom_trans.transform.rotation.z,odom_trans.transform.rotation.w);
			
			double theta = theta1+theta2;

			initialpose_.pose.pose.orientation.z = sin(theta/2.);
			initialpose_.pose.pose.orientation.w = cos(theta/2.);

			initialpose_.header.stamp = ros::Time::now();
			//initialpose_.pose.covariance = amclMsg.pose.covariance;
		//if(amclMsg.pose.covariance[0] > 0.001)
        		initial_pose.publish(initialpose_);       
		}
		if(flag)
		{
			
			if(odomMapTransFlag2){
				odompose_ = amclMsg;
				odomMapTransFlag2 = false;
			}
std::cout << "1" << std::endl;	 		
	 		tf::StampedTransform tx_odom;
	 			 
			tf::TransformListener tf_;

			ros::Time now = ros::Time::now();

			try
			{
    			tf_.waitForTransform("base_link", odompose_.header.stamp, "base_link", now, "odom_base", ros::Duration(0.1));

				tf_.lookupTransform("base_link", odompose_.header.stamp, "base_link", now, "odom_base", tx_odom);

            }
			catch(tf::TransformException& e)
			{
				tx_odom.setIdentity();
			}
  			tf::Pose pose_old, pose_new;
  			tf::poseMsgToTF(odompose_.pose.pose, pose_old);
  			
  			pose_new = pose_old * tx_odom;
std::cout << "3" << std::endl;	
			tf::poseTFToMsg(pose_new,odompose_.pose.pose);
	
			odompose_.header.stamp = now;
std::cout << "4" << std::endl;			
			odom_pose.publish(odompose_);
std::cout << "5" << std::endl;		
}
		ros::spinOnce();
    }

        
    return 0;
}
