#QT       += core gui opengl
QT       += core gui
LIBS += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    GtWidget.cpp \
    gtrendering/QtShader.cpp \
    gtrendering/QtRender.cpp \
    gtrendering/QtSpriteRenderDelegate.cpp \
    $$files(gtengine/*.cpp, true) \
    $$files(gtpatform/*.cpp, true)

HEADERS += \
    GtWidget.h \
    gtrendering/QtShader.h \
    gtrendering/QtRender.h \
    gtrendering/QtSpriteRenderDelegate.h \
    $$files(gtengine/*.h, true) \
    $$files(gtpatform/*.h, true)

RESOURCES += \
    shaders.qrc \
    textures.qrc

INCLUDEPATH += gtengine

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
