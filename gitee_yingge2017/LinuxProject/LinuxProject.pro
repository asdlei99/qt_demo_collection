TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Cpp11/cpp11.cpp \
    Net/net.cpp \
    Net/client.cpp \
    Net/server.cpp \
    Net/epoll.cpp \
    Lab/lab.cpp \
    Lab/signaltest.cpp \
    Net/timer.cpp \
    Lab/forktest.cpp \
    Net/libevent_test.cpp \
    process/fork_test.cpp \
    process/process_test.cpp \
    process/pipe_test.cpp \
    process/fifo_test.cpp \
    process/messagequeue.cpp \
    process/sharedmemory.cpp

HEADERS += \
    Cpp11/cpp11.h \
    Net/net.h \
    Net/client.h \
    Net/server.h \
    Net/epoll.h \
    Lab/lab.h \
    Lab/signaltest.h \
    Net/timer.h \
    Lab/forktest.h \
    Net/lst_timer.h \
    Net/time_heap.h \
    Net/tw_timer.h \
    Net/libevent_test.h \
    process/fork_test.h \
    process/process_test.h \
    process/pipe_test.h \
    process/fifo_test.h \
    process/messagequeue.h \
    process/sharedmemory.h

INCLUDEPATH += \
Net/libevent-2.0.20-stable

LIBS += -lpthread -lrt

DISTFILES += \
    Makefile \
    README.md

