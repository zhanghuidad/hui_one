/*(1). 初始化
SocketCAN 中大部分的数据结构和函数在头文件 linux/can.h 中进行了定义。 
CAN 总线套接字的创建采用标准的网络套接字操作来完成。
网络套接字在头文件 sys/socket.h 中定义。 套接字的初始化方法如下： */
/* 1. 报文发送程序 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
	 
int main()
	{
        
    int s, nbytes;
    struct ifreq ifr;
    struct can_frame frame[2] = {{0}};
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);//创建套接字
    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr); //指定 can0 设备
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *)&addr, sizeof(addr));//将套接字与 can0 绑定
    //禁用过滤规则，本进程不接收报文，只负责发送
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
    //生成两个报文
    frame[0]. can_dlc = 1;
    frame[0].data[0] = 'Y';
    frame[0].can_id = 0x22;
    frame[0]. can_dlc = 1;
    frame[0].data[0] = 'N';
 //循环发送两个报文
    while(1)
    {
       nbytes = write(s, &frame[0], sizeof(frame[0])); //发送 frame[0]
        if(nbytes != sizeof(frame[0]))
       {
            printf("Send Error frame[0]\n!");
            break; //发送错误，退出
        }
        sleep(1);
        nbytes = write(s, &frame[1], sizeof(frame[1])); //发送 frame[1]
        if(nbytes != sizeof(frame[0]))
        {
            printf("Send Error frame[1]\n!");
            break;
        }
        sleep(1);
    }
    close(s);
    return 0;
}