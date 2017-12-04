# Files
SOURCES += main.cpp \
    tilemap.cpp \
    game_state.cpp \
    helper.cpp \
    home_screen.cpp \
    program.cpp \
    sprites_sfml.cpp \
    game.cpp \
    game_won_by_rrh_screen.cpp \
    game_won_by_wolf_screen.cpp \
    dead_grandmother_wolf_wins_screen.cpp \
    program_state.cpp

# C++14
CONFIG += c++14
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -std=c++14

# High warning levels
QMAKE_CXXFLAGS += -Wall -Wextra -Werror

# Debug and release mode
CONFIG += debug_and_release
# Release mode
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # gprof
  QMAKE_CXXFLAGS += -pg
  QMAKE_LFLAGS += -pg

  # ?Why this?
  QMAKE_CXXFLAGS += -Wno-unused-parameter
}
# Debug mode
CONFIG(debug, debug|release) {

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov

  # UBSAN
  QMAKE_CXXFLAGS += -fsanitize=undefined
  QMAKE_LFLAGS += -fsanitize=undefined
  LIBS += -lubsan
}

# QT
QT += core

# SFML
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

HEADERS += \
    tilemap.h \
    game_state.h \
    helper.h \
    home_screen.h \
    program.h \
    sprites_sfml.h \
    game.h \
    game_won_by_rrh_screen.h \
    game_won_by_wolf_screen.h \
    dead_grandmother_wolf_wins_screen.h \
    program_state.h

RESOURCES += \
    resources.qrc

