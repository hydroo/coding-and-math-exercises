TARGET = lib_test

TEMPLATE = app

CONFIG += debug

QMAKE_CXX  = clang++
QMAKE_LINK = clang++

QMAKE_CXXFLAGS += -Wall -Wextra -std=c++14

SOURCES += lib_test.cpp
