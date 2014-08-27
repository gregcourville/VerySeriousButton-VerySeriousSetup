CONFIG += qt resources release
QT += svg xml

HEADERS += VerySeriousSetup.h
HEADERS += BigGoButton.h
HEADERS += DeviceListDialog.h
HEADERS += KeyseqOptionsBox.h
HEADERS += VsbDeviceSelector.h
HEADERS += VsbModeSelector.h
HEADERS += SingleKeyOptionsBox.h

SOURCES += VerySeriousSetup.cpp
SOURCES += BigGoButton.cpp
SOURCES += DeviceListDialog.cpp
SOURCES += KeyseqOptionsBox.cpp
SOURCES += VsbDeviceSelector.cpp
SOURCES += VsbModeSelector.cpp 
SOURCES += SingleKeyOptionsBox.cpp
SOURCES += keyseq.cpp
SOURCES += vsbprog.cpp
SOURCES += main.cpp

LIBS += -lboost_locale-mt
LIBS += -lboost_regex

RESOURCES += rc/images.qrc

INCLUDEPATH += /usr/include/hidapi

QMAKE_CXXFLAGS += -std=c++11

win32 {
  CONFIG += static
  QTPLUGIN += qsvg
  LIBS += -lQtSvg4
  LIBS += -lhidapi
  LIBS += -lsetupapi
  QMAKE_CXXFLAGS += -static-libstdc++ -static-libgcc
  DEFINES += STATIC
  }

unix:LIBS += -lhidapi-hidraw

TARGET = VerySeriousSetup