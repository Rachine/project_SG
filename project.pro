TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp \
    tools.cpp

LIBS += -L"/usr/include/gsl/" -lgsl -lgslcblas
INCLUDEPATH += -I"/usr/include"
HEADERS += \
    tools.h \
    #/usr/include/gsl
