TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    parser.cpp \
    automata.cpp \
    node.cpp \
    sisctrl.cpp

HEADERS += \
    parser.h \
    automata.h \
    node.h

LIBS += -L/usr/local/lib -lyaml-cpp
