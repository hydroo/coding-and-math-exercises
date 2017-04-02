TARGET = 146

TEMPLATE = app

CONFIG += release

LIBS += -lgmp -lgmpxx

QMAKE_CXX  = g++
QMAKE_LINK = g++

QMAKE_CXXFLAGS += -fopenmp -g -Wall -Wextra -std=c++17 -O3 -march=native -mtune=native -fno-omit-frame-pointer
QMAKE_LFLAGS  += -fopenmp

SOURCES += main.cpp
