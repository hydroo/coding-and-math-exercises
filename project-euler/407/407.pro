TARGET = 407

TEMPLATE = app

CONFIG += debug

QMAKE_CXX  = clang++
QMAKE_LINK = clang++

QMAKE_CXXFLAGS +=-O3 -g -std=c++14 -Wall -Wextra

SOURCES += main.cpp

LIBS += -lgmp -lgmpxx
