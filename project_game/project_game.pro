TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:\SFML\SFML-2.5.1\include"

SOURCES += \
        assetmanager.cpp \
        bird.cpp \
        coin.cpp \
        game.cpp \
        gameover.cpp \
        gameplay.cpp \
        main.cpp \
        mainmenu.cpp \
        pausegame.cpp \
        spikes.cpp \
        statemanager.cpp

LIBS += -L"C:\SFML\SFML-2.5.1\lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    State.h \
    assetmanager.h \
    bird.h \
    coin.h \
    game.h \
    gameover.h \
    gameplay.h \
    mainmenu.h \
    pausegame.h \
    spikes.h \
    statemanager.h
