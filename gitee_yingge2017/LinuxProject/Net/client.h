#ifndef CLIENT_H
#define CLIENT_H

/*accept客户端*/

//测试函数
void clientTest();

//客户端连接函数
void clientConnect(const char *ip,const unsigned int port);

//获取当前线程id
void fun();
//多线程客户端
void threadClient();



#endif // CLIENT_H
