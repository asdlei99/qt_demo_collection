QT += core
QT -= gui

CONFIG += c++11

TARGET = CardRuleDemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    card.cpp \
    cardrule.cpp

HEADERS += \
    card.h \
    cardrule.h
