#include <thread>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include "rm_msgs/LocalPlannerAction.h"
#include "state/error_code.h"
#include <nav_msgs/Path.h>

using rrts::common::ErrorCode;

class LocalPlannerTest{
 public:
  LocalPlannerTest():
    local_planner_actionlib_client_("local_planner_node_action", true){
    ros::NodeHandle rviz_nh("move_base_simple");
    goal_sub_ = rviz_nh.subscribe<nav_msgs::Path>("/global_planner_node/path", 1,
                                                              &LocalPlannerTest::GoalCallback,this);

    local_planner_actionlib_client_.waitForServer();
  }
  ~LocalPlannerTest() = default;

  void GoalCallback(const nav_msgs::Path::ConstPtr & goal){
    ROS_INFO("Get new goal.");
    route_.route = *goal;
    local_planner_actionlib_client_.sendGoal(route_,
                                              boost::bind(&LocalPlannerTest::DoneCallback, this, _1, _2),
                                              boost::bind(&LocalPlannerTest::ActiveCallback, this),
                                              boost::bind(&LocalPlannerTest::FeedbackCallback, this, _1)
    );
  }

  void DoneCallback(const actionlib::SimpleClientGoalState& state,  const rm_msgs::LocalPlannerResultConstPtr& result){
    ROS_INFO("The goal is done with %s!",state.toString().c_str());
  }
  void ActiveCallback() {
    ROS_INFO("Action server has recived the goal, the goal is active!");
  }
  void FeedbackCallback(const rm_msgs::LocalPlannerFeedbackConstPtr& feedback){
    if (feedback->error_code != ErrorCode::OK) {
      ROS_INFO("%s", feedback->error_msg.c_str());
    }
  }
 private:
  ros::Subscriber goal_sub_;
  rm_msgs::LocalPlannerGoal route_;
  actionlib::SimpleActionClient<rm_msgs::LocalPlannerAction> local_planner_actionlib_client_;
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "local_planner_test");
  LocalPlannerTest local_planner_test;
  ros::spin();
  return 0;
}

