QT       += core gui sql
QT += widgets multimedia
QT += multimedia
QT += core gui
QT += core gui charts

QT += core gui serialport
CONFIG += console
QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abonnement.cpp \
    arduino.cpp \
    client.cpp \
    connexion.cpp \
    dialog.cpp \
    employe.cpp \
    film.cpp \
    main.cpp \
    mainwindow.cpp \
    poste.cpp \
    projection.cpp \
    qcustomplot.cpp \
    statistique.cpp \
    stats.cpp

HEADERS += \
    abonnement.h \
    arduino.h \
    client.h \
    connexion.h \
    dialog.h \
    employe.h \
    film.h \
    mainwindow.h \
    poste.h \
    projection.h \
    qcustomplot.h \
    statistique.h \
    stats.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    stats.ui

TRANSLATIONS += \
    cine_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
