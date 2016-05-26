TARGET = 203

TEMPLATE = app

CONFIG += debug

QMAKE_CXX  = clang++
QMAKE_LINK = clang++

QMAKE_CXXFLAGS += -g -Wall -Wextra -std=c++14 -O3 -march=native -mtune=native

SOURCES += main.cpp
