QT += opengl

INCLUDEPATH += $$PWD
DEPENDPATH +=  $$PWD

SOURCES += $$files($$PWD/*.cpp, true)
HEADERS += $$files($$PWD/*.h, true)
