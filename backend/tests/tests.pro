QT+=testlib
QT -= gui

CONFIG += c++14 console
INCLUDEPATH += ../
INCLUDEPATH +=./../../crow/include
CONFIG += conan_basic_setup
include(conanbuildinfo.pri)

LIBS += \
       -lboost_system\
       -lboost_chrono \
       -lboost_thread\
       -lboost_timer\
       -lboost_regex\
       -lboost_coroutine \
       -lboost_filesystem \
       -lboost_iostreams \

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    TestParser.cpp \
    ./../Parser.cpp \
    ./../Match.cpp \
    ./../Player.cpp \
    ./../../3rd_part/md5/md5.cpp \
    ./../CardHolder.cpp \
    ./../MatchLogic.cpp



