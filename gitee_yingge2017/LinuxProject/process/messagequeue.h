/*消息队列
 *
 * 1、mq_open来创建非默认个数大小消息队列：
函数原型
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
 第4个参数为 mq_attr 指针
 struct mq_attr{
   long mq_flags;
   long mq_maxmsg;
   long mq_msgsize;
   long mq_curmsgs; };
 当第四个参数为空指针时，就使用默认属性。
当指向mq_attr结构的指针作为参数时，允许我们在该函数的实际操作时创建一个新队列时，给它指定mq_maxmsg和mq_msgsize属性.mq_open忽略该结构的另外两个成员.
（1）attr.mq_maxmsg 不能超过文件 /proc/sys/fs/mqueue/msg_max 中的数值；
（2）attr.mq_msgsize不能超过 /proc/sys/fs/mqueue/msgsize_max 的数值；
（3）消息队列名称前面必须加上斜杆。
在POSIX消息队列中 msg_max 默认为 10 ，msgsize_max 默认为8192 ，否则会报错！！！
可以在 /proc/sys/fs/mqueue# cat msg_max        /proc/sys/fs/mqueue# cat msgsize_max 查看
修改的话，要使用：echo 1000 > /proc/sys/fs/mqueue/msg_max往里面写。

2、获取消息队列的属性
一个进程在发送和接收消息之前，需要了解消息对象的属性，如消息的最大长度。以便
设定接收和发送的buffer大小。 mqd_t mq_getattr(mqd_t mqdes, struct mq_attr *attr);参数：
Mqdes：打开消息队列时获取的描述符。
Attr：指向结构struct mq_attr的指针，用来获取消息队列的四个属性
struct mq_attr {
    long mq_flags;    // 0或者O_NONBLOCK
    long mq_maxmsg; //队列中包含的消息数的最大限制数
    long mq_msgsize; //每个消息大小的最大限制数
    long mq_curmsgs;  //当前队列中的消息数
}

3、设置消息队列属性
我们可以设置消息队列的属性，实际只能设置flag标志，说明队列中没有消息时，接收消息的进程是否在队列上继续等待。
mqd_t mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
参数：
Mqdes：打开消息队列时获取的描述符。
Attr：指向结构struct mq_attr的指针，用来获取消息队列的最大消息个数和最大消息长
度。放到数据结构的mq_maxmsg和mq_msgsize中。

 struct mq_attr {
    long mq_flags;    // 0或者O_NONBLOCK，只能设置这个
    long mq_maxmsg; //队列中包含的消息数的最大限制数
    long mq_msgsize; //每个消息大小的最大限制数
    long mq_curmsgs;  //当前队列中的消息数
 }
oldattr：用来保存设置之前的attr值，可以为NULL.

4、发送消息
进程在打开消息队列后，可以使用下面的函数发送消息
int mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);
参数：
mqdes: 打开消息队列时获得的描述符。
ptr: 指向发送缓冲区的指针，发送缓冲区存放了要发送的数据。
Len: 要发送的数据的长度。 prio ：消息的优先级；它是一个小于 MQ_PRIO_MAX 的数，数值越大，优先级越高。
POSIX 消息队列在调用 mq_receive 时总是返回队列中 最高优先级的最早消息 。如果消息不需要设定优先级，那么可以在 mq_send 是置 prio 为 0 ， mq_receive 的 prio 置为 NULL 。  返回值：发送成功，返回0，失败，返回-1.

5、接收消息
进程在打开消息队列后，可以使用下面的函数接收消息。
ssize_t mq_receive(mqd_t mqdes, char *ptr, size_t len, unsigned int *prio);
参数：
mqdes: 打开消息队列时获得的描述符。
ptr: 指向接收缓冲区的指针。接收缓冲区用来存放收到的消息。
Len: 接收缓冲区的长度。 len不能小于mq_msgsize，否则会返回EMSGSIZE prio ：消息的优先级；它是一个小于 MQ_PRIO_MAX 的数，数值越大，优先级越高。 POSIX 消息队列在调用 mq_receive 时总是返回队列中 最高优先级的最早消息 。如果消息不需要设定优先级，那么可以在 mq_send 是置 prio 为 0 ， mq_receive 的 prio 置为 NULL 。 返回值：  接收成功，返回0，失败，返回-1.

6、消息队列的关闭
mqd_t mq_close(mqd_t mqdes); 关闭消息队列，但不能删除它 成功返回0，失败返回-1

7、删除消息队列
 mqd_t mq_unlink(const char *name); 成功返回0，失败返回-1
当某个进程还没有关闭此消息队列时，调用mq_unlink时，不会马上删除队列，当最后一个进程关闭队列时，该队列被删除
 *
 */
#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

void my_perror(const char *funstr,const char *str);

void messagequeue_test();
void mq_customer();//消费者
void mq_producer();//生产者

#endif // MESSAGEQUEUE_H
