//#include "stdio.h"
//#include "libevent_test.h"
//#include <sys/signal.h>
//#include "event.h"

//void libevent_test_manager()
//{
//    printf("%s\n",__func__);
//    libevent_test();
//}

//void signal_cb( int fd, short event, void* argc )
//{
//    struct event_base* base = ( event_base* )argc;
//    struct timeval delay = { 2, 0 };
//    printf( "Caught an interrupt signal; exiting cleanly in two seconds...\n" );
//    event_base_loopexit( base, &delay );
//}

//void timeout_cb( int fd, short event, void* argc )
//{
//    printf( "timeout\n" );
//}
//void libevent_test(){
//    //创建base实例，reactor实例
//    struct event_base* base = event_init();
//    //创建具体的事件处理器，设置他们从属的reactor实例。
//    //    evsignal_new 创建信号事件处理器
//    struct event* signal_event = evsignal_new( base, SIGINT, signal_cb, base );
//    event_add( signal_event, NULL );

//    timeval tv = { 1, 0 };
//    //evtimer_new 创建定时器事件处理器
//    struct event* timeout_event = evtimer_new( base, timeout_cb, NULL );
//    event_add( timeout_event, &tv );

//    event_base_dispatch( base );

//    event_free( timeout_event );
//    event_free( signal_event );
//    event_base_free( base );
//}
