#include "ros/ros.h"
#include "ros/package.h"
#include <iostream>
#include <string>
#include "test_config.pb.h"
#include <io/io.h>
using namespace std;
int main(int argc, char **argv) {
  ros::init(argc, argv, "test_node");
  test::TestConfig test_config;
  string name;
  int print_times;
  std::string full_path = ros::package::getPath("localization") + "/config/test_config.prototxt";  //Getting Proto Path. It's OK to just change the package name.
  if (!roborts_common::ReadProtoFromTextFile(full_path.c_str(),//Files are not opened.
                                           &test_config)) {
    ROS_ERROR("Cannot load test protobuf configuration file.");
    return -1;
  }
  
  name = test_config.name();//Copy values
  print_times = test_config.print_times();
  
  for (int i=0;i<print_times;i++) //Print
  	cout<<name<<endl;
  return 0;
}
