TARGET = 138

TEMPLATE = app

CONFIG += debug

QMAKE_CXX      = clang++
QMAKE_LINK     = clang++

QMAKE_CXXFLAGS += -g -std=c++14

SOURCES += main.cpp

LIBS += -lgmp
