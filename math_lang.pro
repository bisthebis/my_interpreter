QT += core
Qt += concurrent
QT -= gui

CONFIG += c++11

TARGET = math_lang
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    myexception.h
