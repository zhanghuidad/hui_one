//说明：本程序用于发送UDP数据包，实现多台机器间的通讯
//tar_pos_x、tar_pos_y、tar_pos_yaw长度为3
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <ros/ros.h>
#include "decision/strategyEx.h"
#include "infocenter/strategy_info.h"
//#include "/home/hitcsc/RM2019/devel/include/decision/strategyEx.h"
//#include "/home/hitcsc/RM2019/devel/include/infocenter/strategy_info.h"
//编译：catkin_make -DCATKIN_WHITELIST_PACKAGES=communication


class UPD_Transmitter
{
public:
	int OK;//初始化成功标志
	int sock_fd;//UDP套接字
	struct sockaddr_in addr_serv;//目标IP地址
	UPD_Transmitter(const char* targetIP, int targetPort, int selfPort = 0)
	{
		OK = 0;
		while(1)
		{
			sock_fd = socket(AF_INET, SOCK_DGRAM, 0);//创建UDP套接字
			if(sock_fd < 0)
			{
				printf("socket ERROR\n");
				continue;
			}
			if(selfPort != 0)//绑定端口，设置发送端口号
			{
				printf("self port = %d\r\n", selfPort);
				struct sockaddr_in addr_self;
				memset(&addr_self, 0, sizeof(struct sockaddr_in));//每个字节都用0填充
				addr_self.sin_family = AF_INET;//使用IPV4地址
				addr_self.sin_port = htons(selfPort);//发送数据使用的端口
				addr_self.sin_addr.s_addr = htonl(INADDR_ANY);//自动获取IP地址
				if(bind(sock_fd, (struct sockaddr *)&addr_self, sizeof(addr_self)) < 0)//绑定socket
				{
					perror("bind error:");
					continue;
				}
			}
			//设置目标信息
			memset(&addr_serv, 0, sizeof(struct sockaddr_in));//每个字节都用0填充
			addr_serv.sin_family = AF_INET;//使用IPV4地址
			addr_serv.sin_port = htons(targetPort);//监听的端口
			addr_serv.sin_addr.s_addr = inet_addr(targetIP);//ip地址转换
			OK = 1;
			break;
		}
	}
	int send(char* send_buf, int bufLength)//向目标端口发送UDP数据
	{
		int len = sizeof(addr_serv);
		return sendto(sock_fd, send_buf, bufLength, 0, (struct sockaddr *)&addr_serv, len);
	}
	int receive(char* recv_buf, int bufLength)//接收数据
	{
		int len = sizeof(sockaddr);
		struct sockaddr_in addr_client;
		int recvNum = recvfrom(sock_fd, recv_buf, bufLength, 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
//		printf("port = %d\r\n",ntohs(addr_client.sin_port));
		return recvNum;
	}
protected:
private:
};

UPD_Transmitter sender("10.0.0.4", 10005, 20000);

char UdpPackToSend[80] = {0};//要发送的UDP数据包，格式如下：
/*
0~3:		消息ID			unsigned int
4~7:		消息时间(s)		int
8~11:		消息时间(ns)	int
12~120:strategyEx消息
12~15:		ammo			int
16~19:		hurt			int
20~23:		taskName		int
24~27:		HP				int
28~79:strategy_info消息
28~31:		target_num		int
32~35:		tar_pos_x[0]	float
36~39:		tar_pos_x[1]	float
40~43:		tar_pos_x[2]	float
44~47:		tar_pos_y[0]	float
48~51:		tar_pos_y[1]	float
52~55:		tar_pos_y[2]	float
56~59:		tar_pos_yaw[0]	float
60~63:		tar_pos_yaw[1]	float
64~67:		tar_pos_yaw[2]	float
68~71:		global_pos_x	float
72~75:		global_pos_y	float
76~79:		global_pos_yaw	float
*/
void sendMessage(void)
{
	static unsigned int messageID = 0;
	UdpPackToSend[0] = (messageID >> 24) & 0xff;
	UdpPackToSend[1] = (messageID >> 16) & 0xff;
	UdpPackToSend[2] = (messageID >> 8) & 0xff;
	UdpPackToSend[3] = messageID & 0xff;
	sender.send(UdpPackToSend, 80);
	messageID++;
}
void msg1Callback(decision::strategyEx msg1_raw)//要发送的消息1
{
	int cnt = 4;
/*
struct timeval tv1;
gettimeofday(&tv1, NULL);
UdpPackToSend[cnt++] = (tv1.tv_sec >> 24) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_sec >> 16) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_sec >> 8) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_sec >> 0) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_usec >> 24) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_usec >> 16) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_usec >> 8) & 0xff;
UdpPackToSend[cnt++] = (tv1.tv_usec >> 0) & 0xff;
*/
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.sec >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.sec >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.sec >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.sec >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.nsec >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.nsec >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.nsec >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.header.stamp.nsec >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.ammo >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.ammo >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.ammo >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.ammo >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.hurt >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.hurt >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.hurt >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.hurt >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.taskName >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.taskName >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.taskName >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.taskName >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.HP >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.HP >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.HP >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg1_raw.HP >> 0) & 0xff;
	sendMessage();
}

void msg2Callback(infocenter::strategy_info msg2_raw)//要发送的消息2
{
	int cnt = 4;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.sec >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.sec >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.sec >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.sec >> 0) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.nsec >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.nsec >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.nsec >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.header.stamp.nsec >> 0) & 0xff;
	cnt = 28;
	UdpPackToSend[cnt++] = (msg2_raw.target_num >> 24) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.target_num >> 16) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.target_num >> 8) & 0xff;
	UdpPackToSend[cnt++] = (msg2_raw.target_num >> 0) & 0xff;
	for(int i = 0; i < 3; i++)
	{
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_x[i])))) >> 24) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_x[i])))) >> 16) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_x[i])))) >> 8) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_x[i])))) >> 0) & 0xff;
	}
	for(int i = 0; i < 3; i++)
	{
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_y[i])))) >> 24) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_y[i])))) >> 16) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_y[i])))) >> 8) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_y[i])))) >> 0) & 0xff;
	}
	for(int i = 0; i < 3; i++)
	{
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_yaw[i])))) >> 24) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_yaw[i])))) >> 16) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_yaw[i])))) >> 8) & 0xff;
		UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.tar_pos_yaw[i])))) >> 0) & 0xff;
	}
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_x)))) >> 24) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_x)))) >> 16) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_x)))) >> 8) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_x)))) >> 0) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_y)))) >> 24) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_y)))) >> 16) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_y)))) >> 8) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_y)))) >> 0) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_yaw)))) >> 24) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_yaw)))) >> 16) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_yaw)))) >> 8) & 0xff;
	UdpPackToSend[cnt++] = ((*((unsigned int*)(&(msg2_raw.global_pos_yaw)))) >> 0) & 0xff;
	sendMessage();
}


int main(int argc, char** argv)
{
//	UPD_Transmitter sender("192.168.199.102", 10005);
	if(sender.OK == 0)
	{
		printf("error 0\r\n");
		return 0;
	}
	printf("communication_transmitter start!\r\n");
	ros::init(argc, argv, "communication_sender");
	ros::NodeHandle my_node;
	ros::Subscriber msg1_sub = my_node.subscribe<decision::strategyEx>("/strategy_ex",1,msg1Callback);
	ros::Subscriber msg2_sub = my_node.subscribe<infocenter::strategy_info>("/strategy_info",1,msg2Callback);
	memset(UdpPackToSend, 0, sizeof(UdpPackToSend));
	ros::spin();//接收数据
	/*
	while(ros::ok())
	{
		ros::Time timeNow = ros::Time::now();
		char stingToSend[1000] = {0};
		struct timeval tv1;
		gettimeofday(&tv1, NULL);
		sprintf(stingToSend,"%.9lf\n%d.%06d", timeNow.toSec(), tv1.tv_sec, tv1.tv_usec);
		sender.send(stingToSend, sizeof(stingToSend));
		usleep(100000);//0.1秒
	}
	*/
}



