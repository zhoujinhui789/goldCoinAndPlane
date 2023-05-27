
QT       += core gui
QT       += multimedia




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../PlaneWar/bomb.cpp \
    ../PlaneWar/bullet.cpp \
    ../PlaneWar/enemyplane.cpp \
    ../PlaneWar/heroplane.cpp \
    ../PlaneWar/mainscene.cpp \
    ../PlaneWar/map.cpp \
    chooselevelscreen.cpp \
    dataconfig.cpp \
    main.cpp \
    mainwindow.cpp \
    mycoin.cpp \
    mypushbutton.cpp \
    playscreen.cpp \

HEADERS += \
    ../PlaneWar/bomb.h \
    ../PlaneWar/bullet.h \
    ../PlaneWar/config.h \
    ../PlaneWar/enemyplane.h \
    ../PlaneWar/heroplane.h \
    ../PlaneWar/mainscene.h \
    ../PlaneWar/map.h \
    chooselevelscreen.h \
    dataconfig.h \
    mainwindow.h \
    mycoin.h \
    mypushbutton.h \
    playscreen.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    test.qrc

DISTFILES += \
    ../PlaneWar/PlaneWar.pro.user \
    ../PlaneWar/PlaneWar.pro.user.eeeeb9d.4.8-pre1 \
    ../PlaneWar/plane.rcc \
    ../PlaneWar/res/app.ico \
    ../PlaneWar/res/bg.wav \
    ../PlaneWar/res/bomb-1.png \
    ../PlaneWar/res/bomb-2.png \
    ../PlaneWar/res/bomb-3.png \
    ../PlaneWar/res/bomb-4.png \
    ../PlaneWar/res/bomb-5.png \
    ../PlaneWar/res/bomb-6.png \
    ../PlaneWar/res/bomb-7.png \
    ../PlaneWar/res/bomb.wav \
    ../PlaneWar/res/bullet_1.png \
    ../PlaneWar/res/bullet_10.png \
    ../PlaneWar/res/bullet_11.png \
    ../PlaneWar/res/bullet_12.png \
    ../PlaneWar/res/bullet_13.png \
    ../PlaneWar/res/bullet_14.png \
    ../PlaneWar/res/bullet_2.png \
    ../PlaneWar/res/bullet_3.png \
    ../PlaneWar/res/bullet_4.png \
    ../PlaneWar/res/bullet_5.png \
    ../PlaneWar/res/bullet_6.png \
    ../PlaneWar/res/bullet_7.png \
    ../PlaneWar/res/bullet_8.png \
    ../PlaneWar/res/bullet_9.png \
    ../PlaneWar/res/game.ico \
    ../PlaneWar/res/hero.png \
    ../PlaneWar/res/hero2.png \
    ../PlaneWar/res/hero_bullet_7.png \
    ../PlaneWar/res/img-plane_1.png \
    ../PlaneWar/res/img-plane_2.png \
    ../PlaneWar/res/img-plane_3.png \
    ../PlaneWar/res/img-plane_4.png \
    ../PlaneWar/res/img-plane_5.png \
    ../PlaneWar/res/img-plane_6.png \
    ../PlaneWar/res/img-plane_7.png \
    ../PlaneWar/res/img_bg_level_1.jpg \
    ../PlaneWar/res/img_bg_level_2.jpg \
    ../PlaneWar/res/img_bg_level_3.jpg \
    ../PlaneWar/res/img_bg_level_4.jpg \
    ../PlaneWar/res/img_bg_level_5.jpg

SUBDIRS += \
    ../PlaneWar/PlaneWar.pro
