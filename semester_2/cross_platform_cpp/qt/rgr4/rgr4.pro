QT       += core gui widgets

CONFIG += c++17

# Здесь каждый файл .cpp упомянут ровно ОДИН раз
SOURCES += main.cpp \
           flightcontroller.cpp \
           flightmodel.cpp \
           mainwindow.cpp \
           requestdialog.cpp

# Здесь каждый файл .h упомянут ровно ОДИН раз
HEADERS += flightmodel.h \
           flightcontroller.h \
           mainwindow.h \
           requestdialog.h