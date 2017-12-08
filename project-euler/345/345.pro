TARGET = 345

TEMPLATE = app

CONFIG += debug

QMAKE_CXX      = g++
QMAKE_LINK     = g++

#QMAKE_CXXFLAGS += -O2 -Wall -Wextra -g -std=c++14
QMAKE_CXXFLAGS += -mtune=native -O2 -Wall -Wextra -g -std=c++14

SOURCES += main.cpp

LIBS += -lgmp -lgmpxx
