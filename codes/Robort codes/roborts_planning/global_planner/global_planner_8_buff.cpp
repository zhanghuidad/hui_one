#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <rm_msgs/GlobalPlannerAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <vector>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Quaternion.h>
#define LYH_PI 3.1415926
typedef actionlib::SimpleActionClient<rm_msgs::GlobalPlannerAction> Client;
int main(int argc, char **argv) {
  ros::init(argc, argv, "global_planner_8");
  ros::NodeHandle n;
  ros::Rate rate(10);
  std::vector<geometry_msgs::PoseStamped> goal_list;
  geometry_msgs::Quaternion q;

    geometry_msgs::PoseStamped goal_1;
    goal_1.pose.position.x = 7.3;
    goal_1.pose.position.y = 4.3;
    q=tf::createQuaternionMsgFromYaw(-90.0/180*LYH_PI);
    goal_1.pose.orientation= q;

    geometry_msgs::PoseStamped goal_2;
    goal_2.pose.position.x = 7.3;
    goal_2.pose.position.y = 0.7;
    q=tf::createQuaternionMsgFromYaw(LYH_PI);
    goal_2.pose.orientation= q;

    geometry_msgs::PoseStamped goal_3;
    goal_3.pose.position.x = 0.7;
    goal_3.pose.position.y = 4.3;
    q=tf::createQuaternionMsgFromYaw(-90.0/180*LYH_PI);
    goal_3.pose.orientation= q;

    geometry_msgs::PoseStamped goal_4;
    goal_4.pose.position.x = 0.7;
    goal_4.pose.position.y = 0.7;
    q=tf::createQuaternionMsgFromYaw(0.0);
    goal_4.pose.orientation= q;


    geometry_msgs::PoseStamped goal_5;
    goal_5.pose.position.x = 1.75;
    goal_5.pose.position.y = 3.3;
    q=tf::createQuaternionMsgFromYaw(0.0/180*LYH_PI);
    goal_5.pose.orientation= q;

    geometry_msgs::PoseStamped goal_6;
    goal_6.pose.position.x = 4.0;
    goal_6.pose.position.y = 0.5;
    q=tf::createQuaternionMsgFromYaw(90.0/180*LYH_PI);
    goal_6.pose.orientation= q;

    geometry_msgs::PoseStamped goal_7;
    goal_7.pose.position.x = 6.3;
    goal_7.pose.position.y = 1.8;
    q=tf::createQuaternionMsgFromYaw(-180.0/180*LYH_PI);
    goal_7.pose.orientation= q;

    geometry_msgs::PoseStamped goal_8;
    goal_8.pose.position.x = 4.0;
    goal_8.pose.position.y = 4.5;
    q=tf::createQuaternionMsgFromYaw(-90.0/180*LYH_PI);
    goal_8.pose.orientation= q;


    goal_list.push_back(goal_1);
    goal_list.push_back(goal_2);
    goal_list.push_back(goal_3);
    goal_list.push_back(goal_4);
    goal_list.push_back(goal_5);
    goal_list.push_back(goal_6);
    goal_list.push_back(goal_7);
    goal_list.push_back(goal_8);


  int num = 1;
  bool first_time=1;
  Client client("global_planner_node_action", true);
    std::cout<<"server is ok"<<std::endl;

  client.waitForServer();
 // clien.sendGoal(goal_list[num]);
  std::cout<<"ros::ok"<<std::endl;
  int counter = 0;
  while(ros::ok())
  {
    
    if(client.getState()==actionlib::SimpleClientGoalState::SUCCEEDED&&counter>20)
    {
      num++;
      counter = 0;
    }
    else if(client.getState()==actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      counter ++;
    }
    if(num>7)
      num=0;
    rm_msgs::GlobalPlannerGoal lyh;
    lyh.goal=goal_list[num];
    //lyh.goal=goal_4;
    std::cout<<"goal is ok"<<std::endl;
    client.sendGoal(lyh);
    ros::spinOnce();
    rate.sleep();
  }
}