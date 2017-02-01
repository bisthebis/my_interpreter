QT += core
Qt += concurrent
QT -= gui

CONFIG += c++14

TARGET = math_lang
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    token.cpp \
    scanning.cpp \
    recursivedescentparser.cpp \
    astprinter.cpp \
    ast_c_transpiler.cpp

HEADERS += \
    myexception.h \
    token.h \
    scanning.h \
    recursivedescentparser.h \
    astvisitor.h \
    astnode.h \
    astprinter.h \
    ast_c_transpiler.h
