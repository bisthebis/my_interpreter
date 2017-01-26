QT += core
Qt += concurrent
QT -= gui

CONFIG += c++11

TARGET = math_lang
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    token.cpp \
    scanning.cpp \
    symbols.cpp

HEADERS += \
    myexception.h \
    token.h \
    scanning.h \
    symbols.h
