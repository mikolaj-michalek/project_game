TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:\SFML\SFML-2.5.1\include"

SOURCES += \
        assetmanager.cpp \
        game.cpp \
        gameplay.cpp \
        main.cpp \
        mainmenu.cpp \
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
    game.h \
    gameplay.h \
    mainmenu.h \
    statemanager.h
