/******************************************************************
dbc_timer.c
�����ߣ��ƺ���
ʱ�䣺2018/4/23
���ܣ�ʵ��10ms 20ms 50ms 100ms��������
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "dbc_timer.h"
#include "canbus.h"

extern int can_fd;
extern struct can_frame frame_send;    //frame to be send

/*
    ���ڼ���10ms 20ms 50ms 100ms���������ʱ���߳�
*/
void timerRoutine(void)
{
    while(1)
    {
        //pthread_mutex_lock(&(timerThread->timerThreadLock));
        //10
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //20
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_20msThreadReady));
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //30
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //40
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //50
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        pthread_cond_broadcast(&(timerThread->_50msThreadReady));
        //60
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //70
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //80
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //90
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //100
        usleep(10*1000);
        pthread_cond_broadcast(&(timerThread->_100msThreadReady));
        pthread_cond_broadcast(&(timerThread->_10msThreadReady));
        //printf("one loop done!\n");
    }
}

/*
10ms 20ms 50ms 100ms��������
*/
void _10MsTask(TaskAdd_t * Task)
{
    while(1)
    {
        pthread_cond_wait(&(timerThread->_10msThreadReady), &(timerThread->timerThreadLock));
        (*Task->task)(&Task->arg);
        //usleep(10*1000);
    }
}

void _20MsTask(TaskAdd_t * Task)
{
    while(1)
    {
        pthread_cond_wait(&(timerThread->_20msThreadReady), &(timerThread->timerThreadLock));
        (*Task->task)(&Task->arg);
        //usleep(20*1000);
    }
}

void _50MsTask(TaskAdd_t * Task)
{
    while(1)
    {
        pthread_cond_wait(&(timerThread->_50msThreadReady), &(timerThread->timerThreadLock));
        (*Task->task)(&Task->arg);
        //usleep(50*1000);
    }
}

void _100MsTask(TaskAdd_t * Task)
{
    while(1)
    {
        pthread_cond_wait(&(timerThread->_100msThreadReady), &(timerThread->timerThreadLock));
        (*Task->task)(&Task->arg);
        //usleep(100*1000);
    }
}


/*
��ʼ��ʱ������
����ֵ��ʱ���߳̽ṹ��
*/
TimerThread_t* TimerRoutineInit(void)
{

    TimerThread_t *timerThread = (TimerThread_t *)malloc(sizeof(TimerThread_t));
    timerThread->timerRoutineThread = (pthread_t *)malloc(sizeof(pthread_t));
    //create timer thread!

    //pthread_create(timerThread->timerRoutineThread, NULL, (void*)timerRoutine, NULL);

    timerThread->threadStop = 0;

    pthread_cond_init(&(timerThread->_10msThreadReady),NULL);
    pthread_cond_init(&(timerThread->_20msThreadReady),NULL);
    pthread_cond_init(&(timerThread->_50msThreadReady),NULL);
    pthread_cond_init(&(timerThread->_100msThreadReady),NULL);
    //mutex init
    pthread_mutex_init(&(timerThread->timerThreadLock),NULL);

    //pthread_cond_init();

    return timerThread;
}

/*
�������������
TaskAdd_t * Task�������߳�
int Type������
pthread_t�����ص��߳�ID
*/
pthread_t AddTimerTask(TaskAdd_t * Task, int Type)
{
    pthread_t taskFd;
    switch (Type){
        case 1:

            pthread_create(&taskFd,NULL,(void *)_10MsTask, Task);
            return taskFd;
            break;

        case 2:

            pthread_create(&taskFd,NULL,(void *)_20MsTask, Task);
            return taskFd;
            break;

        case 3:

            pthread_create(&taskFd,NULL,(void *)_50MsTask, Task);
            return taskFd;
            break;

        case 4:

            pthread_create(&taskFd,NULL,(void *)_100MsTask, Task);
            return taskFd;
            break;

        default:
            return -1;
    }
}

/*
������������ĺ���
*/
void TimerCtl(int on_off)
{
    switch (on_off)
    {
        case 1:
            timerThread->threadStop = 1;
            break;
        case 0:
            timerThread->threadStop = 0;
            break;

        default:
            pthread_create(timerThread->timerRoutineThread, NULL, (void*)timerRoutine, NULL);
            break;
    }
}



//int main()
//{
//
//    //pthread_create();
//
//    //pthread_join(*timerThread->timerRoutineThread,NULL);
//
//    TimerThread_t* timerThread = TimerRoutineInit();
//    printf("Hello world!\n");
//
//
//
//    pthread_join(*timerThread->timerRoutineThread,NULL);
//
//    free(timerThread->timerRoutineThread);
//    free(timerThread);
//    return 0;
//}
