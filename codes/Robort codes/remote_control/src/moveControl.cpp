//说明：本程序用于接收UDP数据包，远程遥控机器人运动
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>//ROS消息文件
#include <rm_msgs/GimbalCtrl.h>//ROS消息文件
//#include <remote_control/GimbalCtrl.h>//ROS消息文件



using namespace std;

ros::Publisher command_move_pub;//用于发送底盘控制命令
ros::Publisher command_gimble_pub;//用于发送云台控制命令
geometry_msgs::Twist moveCommand;//底盘控制命令
rm_msgs::GimbalCtrl gimbalCommand;//云台控制命令

class UPD_Receiver
{
public:
	UPD_Receiver(int monitorPort)
	{
		OK = 0;
		sock_fd = socket(AF_INET, SOCK_DGRAM, 0);//创建UDP套接字
		if(sock_fd < 0)
		{
			printf("socket ERROR\n");
			return;
		}
		struct sockaddr_in addr_serv;
		memset(&addr_serv, 0, sizeof(struct sockaddr_in));//每个字节都用0填充
		addr_serv.sin_family = AF_INET;//使用IPV4地址
		addr_serv.sin_port = htons(monitorPort);//监听的端口
		addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);//自动获取IP地址，INADDR_ANY表示接收所有网卡的数据
		if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)//绑定socket
		{
			perror("bind error:");
			return;
		}
		OK = 1;//初始化成功
	}
	int receive(char* recv_buf, int bufLength)
	{
		int len;
		struct sockaddr_in addr_client;
		return recvfrom(sock_fd, recv_buf, bufLength, 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
	}
	int OK;//初始化成功标志
	int sock_fd;//UDP套接字
protected:
private:
};

int main(int argc, char** argv)
{
	unsigned int messageID = 0;
	if(argc != 2)
	{
		printf("impue error!\r\n");
		return 0;
	}
	UPD_Receiver receiver(atoi(argv[1]));
	if(receiver.OK != 1)
	{
		printf("socket init error\r\n");
		return 0;
	}
	int recv_num;
	unsigned char recv_buf[2000];
	ros::init(argc, argv, "remote_control");
	ros::NodeHandle my_node;
	command_move_pub = my_node.advertise<geometry_msgs::Twist>("/cmd_vel", 10);//ROS标准消息，车体控制命令
	command_gimble_pub = my_node.advertise<rm_msgs::GimbalCtrl>("/gimbal_cmd", 10);//自定义消息，云台控制命令
	while(ros::ok())
	{
		//printf("server wait:\n");
		recv_num = receiver.receive((char*)recv_buf, 2000);
		if(recv_num < 0)
		{
			perror("recvfrom error:");
			exit(1);
		}
		if(recv_num != 20) continue;//命令长度错误
		//recv_buf[recv_num] = '\0';
		//printf("receive %d bytes: %s\n", recv_num, recv_buf);
		int messageID_temp = (unsigned int)recv_buf[14] | (unsigned int)(recv_buf[15] << 8) | (unsigned int)(recv_buf[16] << 16) | (unsigned int)(recv_buf[17] << 24);
		if(messageID_temp > messageID || (messageID > 10000000 && messageID_temp < 100000))//消息ID正确，是最新消息
		{
			messageID = messageID_temp;
			moveCommand.linear.x = (recv_buf[0] - 128) / 127.0 * 1.0;//x方向线速度指令//最大速度1米每秒
			moveCommand.linear.y = (recv_buf[1] - 128) / 127.0 * 1.0 * 1.414;//y方向线速度指令//最大速度1米每秒
			moveCommand.linear.z = 0;//z方向线速度指令
			moveCommand.angular.x = 0;//x方向角速度指令
			moveCommand.angular.y = 0;//y方向角速度指令
			moveCommand.angular.z = (128 - recv_buf[2]) / 127.0 * 3.14;//z方向角速度指令//最大速度1弧度每秒
			gimbalCommand.ctrl_mode = 7;//控制模式：7 云台相对车体运动
			gimbalCommand.yaw_ref = (128 - recv_buf[3]) / 77.0 * 100.0;//水平方向，正负90度
			gimbalCommand.pit_ref = (recv_buf[4] - 128) / 77.0 * 30.0;//垂直方向，正负30度
			gimbalCommand.visual_valid = 0;
			command_move_pub.publish(moveCommand);
			command_gimble_pub.publish(gimbalCommand);
		}
	}
	return 0;
}











