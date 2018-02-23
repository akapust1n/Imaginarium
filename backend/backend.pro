QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle


DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
CONFIG += conan_basic_setup
include(conanbuildinfo.pri)

INCLUDEPATH += ./../crow/include
LIBS += \
       -lboost_system\
       -lboost_chrono \
       -lboost_thread\
       -lboost_timer\
       -lboost_regex\
       -lboost_coroutine \
       -lboost_filesystem \

SOURCES +=  main.cpp \
    Matchmaking.cpp \
    Match.cpp \
    Player.cpp \
    ../3rd_part/md5/md5.cpp \
    Parser.cpp \
    MatchLogic.cpp \
    CardHolder.cpp

HEADERS += \
    Player.h \
    Matchmaking.h \
    Match.h \
    Player.h \
    ../3rd_part/md5/md5.h \
    Parser.h \
    MatchLogic.h \
    CardHolder.h

DISTFILES += \
    ../3rd_part/md5/README.md
