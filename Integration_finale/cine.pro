QT       += core gui sql
QT += widgets multimedia
QT += multimedia
QT += core gui


QT += core gui serialport
CONFIG += console
QT += printsupport
QT += core gui charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abonnement.cpp \
    add_class.cpp \
    add_offre.cpp \
    arduino.cpp \
    billet.cpp \
    client.cpp \
    connexion.cpp \
    dialog.cpp \
    employe.cpp \
    exportexcelobject.cpp \
    film.cpp \
    main.cpp \
    mainwindow.cpp \
    my_class.cpp \
    offre.cpp \
    pointdevente.cpp \
    poste.cpp \
    projection.cpp \
    qcustomplot.cpp \
    smtp.cpp \
    statistique.cpp \
    stats.cpp

HEADERS += \
    ../../../Desktop/Gestion de Reservation (2)/Gestion de Reservation/add_class.h \
    ../../../Desktop/Gestion de Reservation (2)/Gestion de Reservation/add_offre.h \
    abonnement.h \
    add_class.h \
    add_offre.h \
    arduino.h \
    billet.h \
    client.h \
    connexion.h \
    dialog.h \
    employe.h \
    exportexcelobject.h \
    film.h \
    mainwindow.h \
    my_class.h \
    offre.h \
    pointdevente.h \
    poste.h \
    projection.h \
    qcustomplot.h \
    smtp.h \
    statistique.h \
    stats.h

FORMS += \
    add_class.ui \
    add_offre.ui \
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
