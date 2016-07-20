TARGET = 144

TEMPLATE = app

CONFIG += debug

LIBS += -lgmp -lgmpxx

QMAKE_CXX  = g++
QMAKE_LINK = g++

QMAKE_CXXFLAGS += -g -Wall -Wextra -std=c++14 -O3 -march=native -mtune=native
QMAKE_LFLAGS  +=

SOURCES += main.cpp
