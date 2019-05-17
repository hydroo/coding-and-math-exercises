TARGET = 500

TEMPLATE = app

CONFIG += debug

QMAKE_CXX      = clang++-8
QMAKE_LINK     = clang++-8

QMAKE_CXXFLAGS += -g -O2 -std=c++17

SOURCES += main.cpp

LIBS += -lgmpxx -lgmp
