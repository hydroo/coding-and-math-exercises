TARGET = 231

TEMPLATE = app

CONFIG += release

LIBS += -lgmp -lgmpxx

QMAKE_CXX  = g++
QMAKE_LINK = g++

QMAKE_CXXFLAGS += -g -Wall -Wextra -std=c++14 -O3 -march=native -mtune=native -fno-omit-frame-pointer
QMAKE_LFLAGS  +=

SOURCES += main.cpp
