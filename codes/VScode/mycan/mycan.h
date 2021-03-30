#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
typedef  struct can_frame {
	canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
	__u8    can_dlc; /* data length code: 0 .. 8 */
#ifdef WIN32
	__u8    can_na[3];//字节对齐问题
#endif // WIN32
	__u8    data[8] __attribute__((aligned(8)));
}S_CanFrame;


struct   ifreq   
{ 
	# define IFNAMSIZ 6
	char  ifr_name[IFNAMSIZ];     /*   interface   name,   e.g.,   "le0 "   */ 
	union   { 
		struct     sockaddr   ifru_addr; 
		struct     sockaddr   ifru_dstaddr; 
		struct     sockaddr   ifru_broadaddr; 
		short       ifru_flags; 
		int           ifru_metric; 
		//caddr_t   ifru_data; 
	}   ifr_ifru; 
	short       ifr_ifindex; 
}; 