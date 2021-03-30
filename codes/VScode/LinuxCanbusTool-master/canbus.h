#ifndef __CANBUS__
#define __CANBUS__

#include <linux/can.h>      //sockaddr_can
#include <sys/socket.h>     //PF_CAN SOCK_RAW
#include <net/if.h>         //struct ifreq
#include <sys/ioctl.h>      //SI

typedef struct canBusElem{
    int canFd;                      //can�豸���
    struct can_frame sendBuffer;    //can�豸����buffer
    struct can_frame recvBuffer;    //can�豸����buffer
    pthread_mutex_t  rdwrLock;      //can�豸���Ͷ�ȡ������
}canBus_t;

typedef struct canbuscmd{
    int show;
    int record;
    int loopback;
    char *interface;
}canbuscmd_t;

int CAN_Send_Random(struct can_frame * frameptr,int can_fd);

int SocketCAN_init(char *interface);

canBus_t * CanBusInit(char *interface);

int CanBusTestMode();

void PthreadCanbusTest();

void CanbusRecvRecord(canbuscmd_t* cmd);

#endif
