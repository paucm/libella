TEMPLATE = app
CONFIG += warn_on thread qt 

TARGET = demo

QT = core \
     xml \
     gui \
     network 

DESTDIR = ../build

SOURCES = main.cpp

HEADERS = artistlist.h

INCLUDEPATH += ../include

LIBS += -L../build -lella
