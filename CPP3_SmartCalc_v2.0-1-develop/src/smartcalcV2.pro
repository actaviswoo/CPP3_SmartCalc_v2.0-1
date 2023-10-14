QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/calculatorwindow.cc \
    View/creditwindow.cc \
    View/depositwindow.cc \
    main.cpp \
    View/mainwindow.cc \
    View/QCustomPlot/qcustomplot.cpp \
    Controller/calculatorcontroller.cc \
    Controller/creditcontroller.cc \
    Controller/depositcontroller.cc \
    Model/calculatormodel.cc \
    Model/creditmodel.cc \
    Model/depositmodel.cc \

HEADERS += \
    View/mainwindow.h \
    View/calculatorwindow.h \
    View/creditwindow.h \
    View/depositwindow.h \
    View/QCustomPlot/qcustomplot.h \
    Controller/calculatorcontroller.h \
    Controller/creditcontroller.h \
    Controller/depositcontroller.h \
    Model/calculatormodel.h \
    Model/creditmodel.h \
    Model/depositmodel.h \

FORMS += \
    View/mainwindow.ui \
    View/calculatorwindow.ui \
    View/creditwindow.ui \
    View/depositwindow.ui \

INCLUDEPATH += \
    $$PWD/View/QCustomPlot

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resources.qrc

TRANSLATIONS += \
    smartcalc_en_US.ts
