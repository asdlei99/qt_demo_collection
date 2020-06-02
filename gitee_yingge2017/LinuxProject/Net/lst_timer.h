#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <stdio.h>

#define BUFFER_SIZE 64
class util_timer;
/*用户数据结构*/
struct client_data
{
    struct sockaddr_in address;
    int sockfd;
    char buf[ BUFFER_SIZE ];
    util_timer* timer;
};
/*定时器类*/
class util_timer
{
public:
    util_timer() : prev( NULL ), next( NULL ){}

public:
   time_t expire; /*任务的超时时间，绝对时间*/
   /*任务回调函数
    毁掉函数处理的客户数据，由定时器的执行者传递给回调函数*/
   void (*cb_func)( client_data* );
   client_data* user_data;
   util_timer* prev; //指向前一个定时器
   util_timer* next;//指向下一个定时器
};
/*定时器链表，它是一个升序、双向链表，且带有头结点和为节点*/
class sort_timer_lst
{
public:
    sort_timer_lst() : head( NULL ), tail( NULL ) {}
    /*链表销毁时，删除其中的所有定时器*/
    ~sort_timer_lst()
    {
        util_timer* tmp = head;
        while( tmp )
        {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }
    /*将目标定时器timer添加到链表中*/
    void add_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        if( !head )
        {
            head = tail = timer;
            return; 
        }
        /*如果目标定时器的超时时间小于当前链表中所有定时器的超时时间的最小值
则把该定时器添加到链表头部，作为链表新的头结点，否则就需要调用重载函数
add_timer(util_timer*timer,util_timer*lst_head),把它插入到链表中合适的位置，以保证
链表的升序特性。*/
        if( timer->expire < head->expire )
        {
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        add_timer( timer, head );
    }
    /*当某个定时任务发生变化时，调整对应的定时器在链表中的位置。
这个函数只考虑被调整定时器的超时时间延长的情况，即该定时器需要往链表
的尾部移动。*/
    void adjust_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        util_timer* tmp = timer->next;
        /*如果该定时器在链表的尾部，或者该定时器新的超时时间仍然
小于其下一个定时器的超时时间，则不移动。*/
        if( !tmp || ( timer->expire < tmp->expire ) )
        {
            return;
        }
        /*如果该定时器是链表的头结点，则将该定时器从链表中取出并
重新插入到链表中*/
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            timer->next = NULL;
            add_timer( timer, head );
        }
        /*如果该定时器不是链表的头结点，且新的超时时间不小于下一个定时器的超时时间，
则将该定时器取出，重新插入到该结点之后的链表中。*/
        else
        {
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer( timer, timer->next );
        }
    }
    /*将目标定时器从链表中删除*/
    void del_timer( util_timer* timer )
    {
        if( !timer )
        {
            return;
        }
        /*当链表中只有一个定时器，即目标定时器*/
        if( ( timer == head ) && ( timer == tail ) )
        {
            delete timer;
            head = NULL;
            tail = NULL;
            return;
        }
        /*如果链表中至少有两个定时器，且目标定时器即链表的头结点时*/
        if( timer == head )
        {
            head = head->next;
            head->prev = NULL;
            delete timer;
            return;
        }
        /*如果链表中至少有两个定时器，且目标定时器即链表的尾结点时*/
        if( timer == tail )
        {
            tail = tail->prev;
            tail->next = NULL;
            delete timer;
            return;
        }
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }
    /*SIGALRM信号每次被触发就在其信号处理函数（如果使用统一事件源，
即主函数）中执行一次tick函数，以处理链表上到期的任务。*/
    void tick()
    {
        if( !head )
        {
            return;
        }
        printf( "timer tick\n" );
        time_t cur = time( NULL );//获得当前时间
        util_timer* tmp = head;
        /*从头结点开始依次处理每个定时器，直到遇到一个尚未到期的定时器，
这就是定时器的核心逻辑。*/
        while( tmp )
        {
            /*因为定时器使用绝对时间作为超时值，把当前时间同定时器超时时间
相比较，就能知道定时器是否超时。*/
            if( cur < tmp->expire )
            {
                break;
            }
            /*调用定时器的回调函数，以执行定时任务*/
            tmp->cb_func( tmp->user_data );
            /*执行完定时器中的定时任务后，就将它从链表中删除，并重置链表头结点。 */
            head = tmp->next;
            if( head )
            {
                head->prev = NULL;
            }
            delete tmp;
            tmp = head;
        }
    }
private:
    /*一个重载的辅助函数，它被公有的add_timer函数和adjust_timer函数调用，
该函数将目标定时器timer添加到指定结点lst_head之后的链表中*/
    void add_timer( util_timer* timer, util_timer* lst_head )
    {
        util_timer* prev = lst_head;
        util_timer* tmp = prev->next;
        while( tmp )
        {
            if( timer->expire < tmp->expire )
            {
                prev->next = timer;
                timer->next = tmp;
                tmp->prev = timer;
                timer->prev = prev;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if( !tmp )
        {
            prev->next = timer;
            timer->prev = prev;
            timer->next = NULL;
            tail = timer;
        }
        
    }

private:
    util_timer* head;
    util_timer* tail;
};

#endif
