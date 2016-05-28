TARGET = 243

TEMPLATE = app

CONFIG += debug

QMAKE_CXX  = g++
QMAKE_LINK = g++

QMAKE_CXXFLAGS += -pg -g -Wall -Wextra -std=c++14 -O3 -march=native -mtune=native
QMAKE_LFLAGS  += -pg

SOURCES += main.cpp
