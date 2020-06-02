#-------------------------------------------------
#
# Project created by QtCreator 2019-02-28T19:10:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UART_Demo
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui


# 添加串口支持

QT += serialport
# 添加图标
RC_ICONS = icon.ico

#windeployqt UART_Demo.exe 自动添加程序运行所需的库
