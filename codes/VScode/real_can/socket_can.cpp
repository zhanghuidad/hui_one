#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char** argv)
{
    int s;					//！是socket返回的套接字描述符//
    int nbytes_write,nbytes_read;
    struct sockaddr_can addr;  //！这个结构体是用来存套接字的地址，例如32,33//
    struct can_frame frame;
    struct ifreq ifr;    //！ifreq是一个配置接口（例如can0），IP地址的等等//

    const char *ifname = "can0";

    if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {   //!socket函数定义，返回-1,就是发生错误//
        perror("Error while opening socket");
        return -1;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);        //！一般ioctl是用来管理i/o口的，例如波特率，//

    addr.can_family  = AF_CAN;			//！地址族//
    addr.can_ifindex = ifr.ifr_ifindex;		//！协议地址//

    printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {   //!就是bind函数，把本地和套接字连接//
        perror("Error in socket bind");
        return -2;
    }

    for(int i = 1; i < 2000; i++) {
        /*		frame.can_id  = 0x104A005A;
        		frame.can_dlc = 2;
        		frame.data[0] = 0x01;
        		frame.data[1] = 0x00;

        		nbytes = write(s, &frame, sizeof(struct can_frame));

        		printf("Wrote %d bytes\n", nbytes);
        		usleep(1000);
        		frame.can_id  = 0x104A005C;
        		frame.can_dlc = 4;
        		frame.data[0] = 0x00;
        		frame.data[1] = 0x00;
        		frame.data[2] = 0x80;
        		frame.data[3] = 0x3F;

        		nbytes = write(s, &frame, sizeof(struct can_frame));

        		printf("Wrote %d bytes\n", nbytes);
        */
        frame.can_id  = 0x104A0058;
        if(!(frame.can_id & CAN_ERR_FLAG))    //！CAN_ERR_FLAG是错误帧，检查错误
            frame.can_id |= CAN_EFF_FLAG;	  //！a | = b 就是 a = a|b，就相当于加：//！CAN_EFF_FLAG，扩展帧的标识，//！这是一种协议你得确定你是用标准帧还是扩展帧。//

        frame.can_dlc = 2;			//！ frame payload length in byte，也就是单位是byte是8位//

        if(i%2) {
            frame.data[0] = 0x01;
            frame.data[1] = 0x02;
        } else {
            frame.data[0] = 0x02;
            frame.data[1] = 0x02;
        }

        nbytes_write = write(s, &frame, sizeof(struct can_frame));  //！write函数就行当send的函数，调用后会返回真正发送的数据长度//

        if(nbytes_write != sizeof(frame)) {
            printf("Send failed, Wrote %d bytes\n", nbytes_write);
        } else {
            printf("Send successfully ! \n");
        }

        usleep(200*1000);     //！频率设为5hz//
    }

    return 0;
}
