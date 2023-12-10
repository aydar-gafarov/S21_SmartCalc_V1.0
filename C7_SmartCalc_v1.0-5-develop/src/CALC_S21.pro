QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    main.cpp \
    qcustomplot.cpp \
    s21_calc.c \
    s21_calculator.cpp

HEADERS += \
    credit.h \
    s21_calc.h \
    qcustomplot.h \
    s21_calculator.h

FORMS += \
    credit.ui \
    s21_calculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/100.webp \
    images/4.png \
    images/png_for_credit_calc.jpeg

RESOURCES += \
    images/img.qrc
