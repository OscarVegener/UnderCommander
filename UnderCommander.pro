QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32-msvc* {
    INCLUDEPATH += C:\boost
    LIBS += -LC:\boost\stage\lib
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calcsize.cpp \
    copyfolder.cpp \
    copyingstatuswindow.cpp \
    copyworker.cpp \
    fsview.cpp \
    info.cpp \
    main.cpp \
    newfile.cpp \
    newfolder.cpp \
    tabs.cpp \
    undercommander.cpp

HEADERS += \
    calcsize.h \
    copyfolder.h \
    copyingstatuswindow.h \
    copyworker.h \
    fsview.h \
    info.h \
    newfile.h \
    newfolder.h \
    tabs.h \
    undercommander.h

FORMS += \
    copyfolder.ui \
    copyingstatuswindow.ui \
    info.ui \
    newfile.ui \
    newfolder.ui \
    undercommander.ui

TRANSLATIONS += \
    UnderCommander_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    warning.png

RESOURCES += \
    icons.qrc
