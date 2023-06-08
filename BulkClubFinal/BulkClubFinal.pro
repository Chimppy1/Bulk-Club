QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    displayBoard.cpp \
    item.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    memberList.cpp \
    purchase.cpp \
    purchaseList.cpp

HEADERS += \
    QDateTableWidgetItem.h \
    displayBoard.h \
    item.h \
    inventoryTable.h \
    loginwindow.h \
    mainwindow.h \
    member.h \
    memberList.h \
    mytable.h \
    mytable2.h \
    purchase.h \
    purchaseList.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui

OTHER_FILES += \
    warehouse shoppers.txt
    day1.txt
    day2.txt
    day3.txt
    day4.txt
    day5.txt
    day6.txt
    day7.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
